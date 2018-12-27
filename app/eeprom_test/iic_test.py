import os, time

def file_use_os():
    try:
        fd = os.open('/sys/bus/i2c/devices/0-0050/eeprom', os.O_RDWR);
    except Exception:
        print("open faild!!!")
        return
        
    print("open i2c-0 sucess.")
    
    val=0
    while(True):
        os.write(fd, bytes([val]));
        time.sleep(1);
        if val==255:
            val=0
        else:
            val+=1
        print(os.read(fd,4))
    
    os.close (fd) ;

def iic_test():
    try:
        fileHandle = open('/sys/bus/i2c/devices/0-0050/eeprom','rb+')
    except Exception:
        print("open faild!!!")
        return
        
    print("open eeprom sucess.")
    
    line = fileHandle.read(60)
    print(line)

    fileHandle.seek(8,0)
    fileHandle.write(b'eeprom test!!!\r\n')
    
    fileHandle.seek(8,0)
    pos =  fileHandle.tell()
    print(pos)
    
    fileHandle.seek(2,0)
    line = fileHandle.read(60)
    print(line)
    
    #fileHandle.seek(10)
    
    #print( fileHandle.read(6) )

    fileHandle.close()
    

def main():
    #file_use_os();
    iic_test()
    
if __name__ == "__main__":
    main()    
