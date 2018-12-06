# $language = "Python"

# $interface = "1.0"

import os
import random

def sleep(ms):
    crt.Sleep(ms)

def message(str):
    #crt.Screen.Print(str)
    pass
    
def SEND_CMD(str):
    crt.Screen.Send(str)
    crt.Screen.Send("\r")
    #sleep(100)
    

def zynq_linux_init():
    SEND_CMD("ifconfig eth0 192.168.68.100")
    #SEND_CMD("ln -s /lib/ld-2.19-2014.08.so /lib/ld-linux.so.3")
    SEND_CMD("mkdir /mnt/mmc")
    SEND_CMD("mount /dev/mmcblk0p1 /mnt/mmc")
    
    

def main():
    zynq_linux_init()
    
main()

