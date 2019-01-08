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
    SEND_CMD("lcd F:/zynq/strongZynq/strongZynq.runs/impl_1")
    SEND_CMD("put top7z020.bit")

        
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

