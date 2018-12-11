# $language = "Python"

# $interface = "1.0"

import os
import random

def message(str):
    crt.Screen.Print(str)
    pass
    
def wait_string(str,timeout_s):
    if (crt.Screen.WaitForString(str, timeout_s) != True):
        crt.Dialog.MessageBox("wait string timeout!!")
        return 0
    sleep(500)
    return 1

    
def SEND_CMD(str):
    crt.Screen.Send(str)
    crt.Screen.Send("\r")
    #sleep(100)
    
def sleep(ms):
    crt.Sleep(ms)
    
    
def sd_boot():
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
    SEND_CMD("load mmc 0 ${kernel_load_address} ${kernel_image} && ")
    sleep(1000)
    SEND_CMD("load mmc 0 ${devicetree_load_address} ${devicetree_image} && ")
    sleep(1000)
    SEND_CMD("load mmc 0 0x4000000 uramdisk.image.gz && ")
    sleep(1000)
    SEND_CMD("bootm 0x2080000 0x4000000 0x2000000")

    
    
def tftp_boot():
    SEND_CMD("setenv ipaddr 192.168.68.100")#zynq board ip
    SEND_CMD("setenv serverip 192.168.68.200") #pc ip
    
    SEND_CMD("tftpboot ${devicetree_load_address} ${devicetree_image}")
    wait_string("Zynq>",5)
    
    SEND_CMD("tftpboot ${kernel_load_address} ${kernel_image}")
    wait_string("Zynq>",20)
    
    SEND_CMD("tftpboot ${ramdisk_load_address} ${ramdisk_image}")
    wait_string("Zynq>",30)
    SEND_CMD("bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}")

    #SEND_CMD("aaaaaa")
    
def nfs_boot():
    SEND_CMD("setenv ipaddr 192.168.68.100")#zynq board ip
    SEND_CMD("setenv serverip 192.168.68.200") #pc ip
    #SEND_CMD("setenv ipaddr 172.16.100.100")#zynq board ip
    #SEND_CMD("setenv serverip 172.16.100.10") #pc ip
    
    
    SEND_CMD("nfs ${devicetree_load_address} 192.168.68.200:/nfs/${devicetree_image}")
    wait_string("Zynq>",20)
    
    sleep(500)

    SEND_CMD("nfs ${kernel_load_address} 192.168.68.200:/nfs/${kernel_image}")
    wait_string("Zynq>",20)
    sleep(500)
    
    SEND_CMD("nfs ${ramdisk_load_address} 192.168.68.200:/nfs/${ramdisk_image}")
    wait_string("Zynq>",20)
    #SEND_CMD("bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}")
    

        
def run():
    pass

def main():
    #sd_boot()
    #tftp_boot()
    nfs_boot()    
    
main()

