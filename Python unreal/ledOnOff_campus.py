import uwebsockets.client
import sys,time
import network
from machine import Pin
from time import sleep
import _thread
import upip
from ujson import dumps
import machine, time
from machine import Timer
import uasyncio
TIMEOUT_MS = 8000 #soft-reset will happen around 8 sec

def timeout_callback(t):
    try:
        #print("I am in Call back")
        #websocket.send("Ws send \r")
        if(p0.value()==0):
            websocket.send("{ \"action\":\"sendmessage\",\"message\":\"Light is OFF\"}")
        elif(p0.value()==1):
            websocket.send("{ \"action\":\"sendmessage\",\"message\":\"Light is ON\"}")
    finally:
        #print("I am in Call back finally")
        pass
        #print("out of rescieve")
        #print(resp)

    

        
      

def wlan_connect(ssid,pwd):
    wlan = network.WLAN(network.STA_IF)
    if not wlan.active() or not wlan.isconnected():
        wlan.active(True)
        wlan.connect(ssid,pwd)
        while not wlan.isconnected():
            pass
    print('network config:', wlan.ifconfig())
    #upip.install("uasyncio")
    
    
wlan_connect('samad', 'samad123')
p0 = Pin(15, Pin.OUT)
p0.off()
uri = "wss://vurzcp9ti8.execute-api.ap-south-1.amazonaws.com/production"
websocket = uwebsockets.client.connect(uri)
#print(websocket)

s=""
flag=0

while True:

    #print("Enter Command:\r")
    #mesg=input()
    #websocket.send(mesg + "\r")
    
    #******************************************************************
    time.sleep(5)
    resp = websocket.recv()
    
    print(resp)
    
   
    if "Pressed E Key"==resp:
        if p0.value()==1 :
            s="off"
            p0.off() #this glows led in iot
            
        elif p0.value()==0:
            s="on"
            p0.on()       # this will off led in iot
    """
    else:
        print("Waiting for input from unreal")
        resp = websocket.recv()
        if "off1"==resp:
            if p0.value()==1 and flag==1:
                flag=0
                s="off"
                p0.off() #this glows led in iot
                
            elif p0.value()==0 and flag==0:
                flag=1
                s="on"
                p0.on()
    """        
    dic = {"action": "sendmessage", "message": "{}".format(s)}
    websocket.send(dumps(dic))
    
    #time.sleep(5)
    
   
    #**************************************************************
    timer = Timer(0)
    timer.init(period=TIMEOUT_MS, callback=timeout_callback)
    mesg=input("Enter msg : ").lower()
   
    dic = {"action": "sendmessage", "message": "{}".format(mesg)}
    websocket.send(dumps(dic))
    if mesg=="on" :
        p0.on()
        print("Led is on")
    elif mesg=="off": 
        p0.off()
        print("Led is off")
    else:
        print("No data recieved")
    
    
    sleep(1)

test()