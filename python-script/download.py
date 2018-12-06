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
    SEND_CMD("cd /bin")
    SEND_CMD("lcd Y:/file-to-board")
    SEND_CMD("put Y:/file-to-board/myled.ko")
    SEND_CMD("put Y:/file-to-board/test")
    SEND_CMD("put Y:/file-to-board/hello")

        
def run():
    SEND_CMD("cd /")
    SEND_CMD("cd /bin")
    SEND_CMD("chmod a+x /bin/myled.ko ")
    SEND_CMD("insmod myled.ko")
    
    SEND_CMD("chmod a+x /bin/hello")
    SEND_CMD("/bin/hello")

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



    #SEND_CMD("./tmp/instrument.elf -gem 2 1 -f /mnt/eni_dmars_2_inst_2.xml -v 0 -t 0 -dcmmode busshift -sp")
    #crt.Screen.Clear()
    #crt.Dialog.MessageBox(str(result))
    #fileWrite = open ( 'test.txt', 'w')
    #fileWrite.write("GetTabCount"+str(crt.GetTabCount()))
    #object = crt.GetActiveTab()
    #sftpTab = object.ConnectSftp()
    #sleep(5000)
    #sftpTab.Close()
