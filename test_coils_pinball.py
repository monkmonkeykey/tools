import time
while True: 
    for i in range(1, 6):
        hostname = f"pinball{i}game"
        role_module.main.hosts.hostnames[hostname].cmd_lefttube_launch()
        time.sleep(2)
        role_module.main.hosts.hostnames[hostname].cmd_righttube_launch()
        time.sleep(2)
        role_module.main.hosts.hostnames[hostname].cmd_kicker_launch()
        time.sleep(2)
