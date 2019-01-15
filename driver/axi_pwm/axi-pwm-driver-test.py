# $language = "Python"

# $interface = "1.0"

import os
import random

def message(str):
    crt.Screen.Print(str)
    pass
    
def SEND_CMD_NO_DELAY(str):
    crt.Screen.Send(str)
    crt.Screen.Send("\r")

def SEND_CMD(str):
    crt.Screen.Send(str)
    crt.Screen.Send("\r")
    sleep(50)
    
def sleep(ms):
    crt.Sleep(ms)
    
    
def download():
    SEND_CMD("cd /mnt/")
    SEND_CMD("lcd Z:/zynq/zynq_develop/file-gen/common/")
    #SEND_CMD("put devicetree.dtb")
    #SEND_CMD("put uImage")

    SEND_CMD("cd /mnt/app")
    SEND_CMD("cd /tmp/")
    
    SEND_CMD("lcd Z:/zynq/zynq_develop/driver/axi_pwm")
    SEND_CMD("put axi_pwm.ko")

    SEND_CMD("lcd Z:/zynq/zynq_develop/driver/axi_pwm/test")
    SEND_CMD("put axi_pwm_drv_test.elf")
        
def run():
    SEND_CMD_NO_DELAY("lsmod")
    result = crt.Screen.WaitForString("axi_pwm", 1)
    if (result == 1):
        SEND_CMD("rmmod axi_pwm")
        return
    SEND_CMD("mkdir -p /lib/modules/$(uname -r)")
    #SEND_CMD("cd /mnt/app")
    SEND_CMD("cd /tmp/")

    SEND_CMD("mknod /dev/axi_pwm-0 c 99 0")
    SEND_CMD("mknod /dev/axi_pwm-1 c 99 1")
    SEND_CMD("insmod axi_pwm.ko")
    SEND_CMD("chmod 777 axi_pwm_drv_test.elf")

    #SEND_CMD("./axi_pwm_drv_test.elf")

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

