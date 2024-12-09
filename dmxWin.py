import usb.core
from pyudmx import pyudmx
from pythonosc import dispatcher, osc_server
from threading import Thread
import time

class DMXController:
    def __init__(self):
        self.cv = [0] * 512
        self.cv_updated = [False] * 512  # Track updated channels
        self.dev = pyudmx.uDMXDevice()
        self.restart_device()
        self.running = True
        self.batch_sender_thread = Thread(target=self.batch_send_dmx)
        self.batch_sender_thread.start()

    def restart_device(self):
        try:
            self.dev.open()
            print("DMX Controller initialized. Ready to receive channel values from OSC.")
        except usb.core.USBError as e:
            print(f"Error opening DMX device: {e}")
            self.retry_connection()

    def retry_connection(self, attempts=5):
        for attempt in range(attempts):
            print(f"Retrying connection, attempt {attempt+1}/{attempts}...")
            time.sleep(2)
            try:
                self.dev.open()
                return
            except usb.core.USBError:
                continue
        raise usb.core.USBError("Failed to reconnect after several attempts.")

    def set_channel_value(self, channel, value):
        if 0 <= channel < 512:
            self.cv[channel] = max(0, min(255, value))
            self.cv_updated[channel] = True  # Mark channel as updated

    def batch_send_dmx(self):
        while self.running:
            if any(self.cv_updated):  # Check if there are any updated channels
                try:
                    self.dev.send_multi_value(1, self.cv)
                    self.cv_updated = [False] * 512  # Reset update flags
                except usb.core.USBError as e:
                    print(f"USB Error while sending DMX data: {e}")
                    self.retry_connection()
            time.sleep(0.1)  # Adjust the interval as needed

    def update_from_osc(self, unused_addr, *args):
        osc_address = unused_addr.split('/')[-1]
        if osc_address.startswith('dmx') and osc_address[3:].isdigit():
            channel = int(osc_address[3:]) - 1
            value = int(args[0])
            self.set_channel_value(channel, value)

    def reset(self):
        self.running = False
        self.cv = [0] * 512
        self.send_dmx()
        self.dev.close()
        print("All channels reset and DMX closed.")

def start_osc_server(dmx_controller, ip='127.0.0.1', port=8000):
    disp = dispatcher.Dispatcher()
    disp.map("/dmx*", dmx_controller.update_from_osc)
    
    server = osc_server.BlockingOSCUDPServer((ip, port), disp)
    print(f"OSC server running on {ip}:{port}")
    server.serve_forever()

if __name__ == "__main__":
    dmx = DMXController()

    try:
        start_osc_server(dmx)
    except KeyboardInterrupt:
        pass
    finally:
        dmx.reset()
        print("Exiting...")
