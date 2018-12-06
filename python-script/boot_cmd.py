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
    
    
def boot():
    """
    "sdboot=if mmcinfo; then " \
            "run uenvboot; " \
            "echo Copying Linux from SD to RAM... && " \
            "load mmc 0 ${kernel_load_address} ${kernel_image} && " \
            "load mmc 0 ${devicetree_load_address} ${devicetree_image} && " \
            "load mmc 0 ${ramdisk_load_address} ${ramdisk_image} && " \
            "bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}; " \
    """
    SEND_CMD("mmcinfo")
    #SEND_CMD("run uenvboot")
    SEND_CMD("load mmc 0 0x2080000 uImage && ")
    sleep(1000)
    SEND_CMD("load mmc 0 0x2000000 devicetree.dtb && ")
    sleep(1000)
    SEND_CMD("load mmc 0 0x4000000 uramdisk.image.gz && ")
    sleep(1000)
    SEND_CMD("bootm 0x2080000 0x4000000 0x2000000")
    #SEND_CMD("aaaaaa")


        
def run():
    pass

def main():
    boot()
    
    
main()

