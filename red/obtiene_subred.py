import psutil
import ipaddress

def obtener_subred_real():
    for iface, addrs in psutil.net_if_addrs().items():
        for addr in addrs:
            if addr.family.name == 'AF_INET' and not addr.address.startswith('127.'):
                ip = addr.address
                mascara = addr.netmask
                red = ipaddress.IPv4Network(f"{ip}/{mascara}", strict=False)
                print(f"Interfaz: {iface}")
                print(f"IP local: {ip}")
                print(f"Máscara: {mascara}")
                print(f"Subred real: {red}")
                return str(red)

if __name__ == "__main__":
    obtener_subred_real()
