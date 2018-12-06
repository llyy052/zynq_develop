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
    #sleep(100)
    
def sleep(ms):
    crt.Sleep(ms)
    
    
def download():
    SEND_CMD("cd /mnt")
    SEND_CMD("lcd Z:/zynq/zynq_develop/file-gen/sd_image")
    #SEND_CMD("put uramdisk.image.gz")
    SEND_CMD("put devicetree.dtb")
    SEND_CMD("put uImage")
    SEND_CMD("put zImage")
    SEND_CMD("put BOOT.BIN")
    SEND_CMD("put init.sh")
    
    SEND_CMD("lcd Z:/zynq/zynq_develop/file-to-send")

        
def run():
    pass

def main():
    crt.Screen.Send("\r")
    #result = crt.Screen.WaitForStrings(["sftp> ", "root"], 1)
    result = crt.Screen.WaitForStrings(["sftp> ", "zynq"], 1)
    if (result == 1):
        download()
    elif (result == 2):
        run()
    else:
        message("error")
        crt.Dialog.MessageBox("error")
    
    
main()

