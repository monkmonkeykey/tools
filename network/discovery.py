# network/discovery.py
import json, socket, threading, time

class Discovery:
    def __init__(self, hostname, ip, target_hostname, update_cb, period=2):
        self.hostname = hostname
        self.ip = ip
        self.target_hostname = target_hostname
        self.update_cb = update_cb
        self.period = period

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        self.sock.bind(("", 0))

        self.listen_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.listen_sock.bind(("", 50000))

        threading.Thread(target=self._listen, daemon=True).start()
        threading.Thread(target=self._broadcast, daemon=True).start()

    def _broadcast(self):
        msg = json.dumps({"hostname": self.hostname, "ip": self.ip}).encode()
        while True:
            self.sock.sendto(msg, ("255.255.255.255", 50000))
            time.sleep(self.period)

    def _listen(self):
        while True:
            data, addr = self.listen_sock.recvfrom(1024)
            info = json.loads(data.decode())
            self.update_cb(info, addr)
