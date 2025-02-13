import usb.core
from pyudmx import pyudmx
from pythonosc import dispatcher, osc_server
from time import sleep

class DMXController:
    def __init__(self):
        """
        Initialize the DMX controller.
        No channel mapping is predefined; all channels are open for control via OSC.
        """
        self.cv = [0 for _ in range(512)]  # List of 512 DMX channels
        self.dev = pyudmx.uDMXDevice()
        self.restart_device()

    def restart_device(self):
        """Open and reset the DMX device."""
        try:
            self.dev.open()
            print(f"DMX Controller initialized. Ready to receive channel values from OSC.")
        except usb.core.USBError as e:
            print(f"Error opening DMX device: {e}")
            self.retry_connection()

    def retry_connection(self):
        """Attempt to reconnect after a delay."""
        print("Retrying connection in 5 seconds...")
        sleep(5)
        self.restart_device()

    def set_channel_value(self, channel, value):
        """
        Set the value of a specific DMX channel.
        Ensures the value is within the allowed range (0-255).
        """
        if 0 <= channel < 512:
            # Ensure value is between 0 and 255
            value = max(0, min(255, value))
            self.cv[channel] = value
            #print(f"Set channel {channel+1} to {value}.")
        else:
            print(f"Channel {channel+1} out of range (0-511).")

    def send_dmx(self):
        """
        Send the current DMX values to the lights with a slight delay.
        """
        try:
            self.dev.send_multi_value(1, self.cv)
            sleep(0.05)  # Adding a 50ms delay between each message to reduce data traffic issues
        except usb.core.USBError as e:
            print(f"USB Error while sending DMX data: {e}")
            self.retry_connection()
        except ValueError as e:
            print(f"Value error: {e}. Resetting DMX values and restarting...")
            self.reset()
            self.retry_connection()

    def update_from_osc(self, unused_addr, *args):
        """
        OSC callback to update DMX channels.
        This function extracts the DMX channel from the OSC address.
        """
        osc_address = unused_addr.split('/')[-1]  # Extract the last part of the OSC address, e.g., "dmx1"
        if osc_address.startswith('dmx') and osc_address[3:].isdigit():
            channel = int(osc_address[3:]) - 1  # Extract the number from the address and convert to zero-indexed
            value = int(args[0])  # The value should be the first argument
            #print(f"Received OSC message: Address: {unused_addr}, Value: {value}")
            self.set_channel_value(channel, value)
            self.send_dmx()
        else:
            print(f"Invalid OSC address: {unused_addr}")

    def reset(self):
        """
        Reset all channels (turn off the lights).
        """
        self.cv = [0 for _ in range(512)]
        try:
            self.send_dmx()
        except usb.core.USBError as e:
            print(f"USB Error while resetting DMX: {e}")
        finally:
            self.dev.close()
            print("All channels reset and DMX closed.")

def start_osc_server(dmx_controller, ip='127.0.0.1', port=8000):
    """
    Start an OSC server to receive DMX channel updates.
    """
    disp = dispatcher.Dispatcher()
    disp.map("/dmx*", dmx_controller.update_from_osc)  # Map all addresses starting with "/dmx"
    
    server = osc_server.BlockingOSCUDPServer((ip, port), disp)
    print(f"OSC server running on {ip}:{port}")
    server.serve_forever()

if __name__ == "__main__":
    dmx = DMXController()

    try:
        # Start OSC server to receive DMX data
        start_osc_server(dmx)
    except KeyboardInterrupt:
        pass
    finally:
        dmx.reset()
        print("Exiting...")
