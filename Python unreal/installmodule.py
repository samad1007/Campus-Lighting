import network


def wlan_connect(ssid,pwd):
    wlan = network.WLAN(network.STA_IF)
    if not wlan.active() or not wlan.isconnected():
        wlan.active(True)
        wlan.connect(ssid,pwd)
        while not wlan.isconnected():
            pass
    print('network config:', wlan.ifconfig())
    upip.install("micropython-logging")
    
    
wlan_connect('Samad', 'samad123567')
