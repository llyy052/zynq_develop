# $language = "Python"

# $interface = "1.0"

import os
import random

def message(str):
    crt.Screen.Print(str)
    pass
    
def SEND_CMD(str):
    crt.Screen.Send(str)
    crt.Screen.Send("\r")
    sleep(10)
    
def sleep(ms):
    crt.Sleep(ms)
    
    
def download():
    SEND_CMD("cd /mnt/")
    SEND_CMD("lcd Z:/zynq/zynq_develop/file-gen/common/")
    SEND_CMD("put devicetree.dtb")

    SEND_CMD("cd /mnt/app")
    SEND_CMD("cd /lib/modules/3.6.0/")
    
    SEND_CMD("lcd Z:/zynq/zynq_develop/driver/cat9555")
    SEND_CMD("put cat9555.ko")

        
def run():
    SEND_CMD("cd /mnt/app")
    SEND_CMD("cd /lib/modules/3.6.0")
    SEND_CMD("depmod")
    SEND_CMD("modprobe cat9555")
    #SEND_CMD("insmod cat9555.ko")


def main():
    crt.Screen.Send("\r")
    result = crt.Screen.WaitForStrings(["sftp> ", "zynq"], 1)
    if (result == 1):
        download()
    elif (result == 2):
        run()
    else:
        message("error")
        crt.Dialog.MessageBox("error")
    
    
main()

