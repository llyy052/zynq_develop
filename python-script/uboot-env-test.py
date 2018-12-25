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
    
    
def set_env():
    SEND_CMD("setenv loadmmckernel load mmc 0 ${kernel_load_address} ${kernel_image} &&")
    SEND_CMD("setenv iftest if run loadmmckernel;then echo fafafdfdadfafd;  fi; ")


        
def run():
    pass


def main():
    crt.Screen.Send("\r")
    result = crt.Screen.WaitForStrings(["sftp> ", "Zynq>"], 1)
    if (result == 1):
        run()
    elif (result == 2):
        set_env()
    else:
        message("error")
        crt.Dialog.MessageBox("error")
    
    
main()


