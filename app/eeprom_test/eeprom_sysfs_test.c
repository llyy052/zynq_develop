#include<stdio.h> 
#include<stdlib.h> 
#include<sys/types.h> 
#include<sys/stat.h> 
#include<fcntl.h> 
#include<string.h> 

int main(void)
{ 
    int fd, size, len, i; 
    char buf[50]= {0}; 
    char *bufw="Hi,this is an eepromtest!";//要写入的数据 
    len=strlen(bufw);//数据长度 
    
    fd= open("/sys/bus/i2c/devices/0-0050/eeprom",O_RDWR);//打开文件 
    if(fd< 0) {
        printf("####i2c test device open failed####/n");
        return(-1); 
    } //写操作 
    lseek(fd,0x40,SEEK_SET); //定位地址，地址是0x40 
    if((size=write(fd,bufw, len))<0)//写入数据 
    { 
        printf("write error\n"); 
        return 1; 
    } 
    printf("writeok\n"); 
    //读操作 
    lseek(fd,0x40, SEEK_SET);//准备读，首先定位地址，因为前面写入的时候更新了当前文件偏移量，所以这边需要重新定位到0x40. 
    if((size=read(fd,buf,len))<0)//读数据 
    { 
        printf("readerror\n"); 
        return 1; 
    } 
    printf("readok\n"); 
    for(i=0; i< len; i++) 
    printf("buff[%d]=%x\n",i, buf[i]);//打印数据 
    close(fd); 
    return 0; 
 }

