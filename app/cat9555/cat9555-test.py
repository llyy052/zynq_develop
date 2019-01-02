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
    SEND_CMD("cd /mnt/app")
    SEND_CMD("lcd Z:/zynq/zynq_develop/app/cat9555")
    SEND_CMD("put cat9555_test.elf")

        
def run():
    SEND_CMD("cd /mnt/app")
    SEND_CMD("./cat9555_test.elf")


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

