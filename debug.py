import socket
import time
import webbrowser,sys,subprocess
import math
import os

print("Welcome to MamiesMod Client debugger !")

ip="192.168.1.48"

address=0x04CC0000
code=""
offset=0

popen = subprocess.Popen('assemble\\build.bat',shell=True)
popen.wait()

with open("assemble\\asm",'rb') as f:
    tmp=f.read()
    f.close()
tmp=tmp.hex().upper()
time.sleep(0.1)

s=[]
for x in range(math.floor(len(tmp)/8)):
    s.append(tmp[x*8:x*8+8])
    
for x in range(len(s)):
    code=code+(format(address+offset,'08X')+" "+s[x][0:8])+"\n"
    offset=offset+4

code=code[:-1]

with open("scripts\\main",'w') as f:
    f.write(code)
    f.close()

ip_temp = input("What is your IP (default is 192.168.1.48): 192.168.")
if ip_temp != "":
    ip = "192.168." + ip_temp
address_temp = input("Where the customer will be stored (default 0x04CC0000): 0x")
if address_temp != "":
    address = hex(int(str, 16))
print("connecting...")
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect((ip,7331))
print("Connected !")

sends=[]
with open("scripts\\api-CodeEnablesSetter") as f:
    sends=f.readlines()
    f.close
with open("scripts\\api-Resetter") as f:
    sends=sends+f.readlines()
    f.close
'''
with open("scripts\\api-GetHackItems") as f:
    sends=sends+f.readlines()
    f.close
with open("scripts\\api-GetHackItems2") as f:
    sends=sends+f.readlines()
    f.close
with open("scripts\\api-RainbowArmor") as f:
    sends=sends+f.readlines()
    f.close
with open("scripts\\api-Nuker") as f:
    sends=sends+f.readlines()
    f.close
'''
with open("scripts\\main") as f:
    sends=sends+f.readlines()
    f.close
with open("scripts\\api-ArgSetter") as f:
    sends=sends+f.readlines()
    f.close
with open("scripts\\Run") as f:
    sends=sends+f.readlines()
    f.close

for x in range(len(sends)):
    if(("#" in sends[x])==False):
        s.send(bytes.fromhex('03'))
        s.send(bytes.fromhex(sends[x].replace("\n","")))
        print("send " + sends[x])
s.close()
print("Disconnected !")
time.sleep(3)
