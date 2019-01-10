
#include <stdio.h> 
#include <linux/types.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/ioctl.h> 
#include <errno.h> 
#include <linux/i2c.h> 
#include <linux/i2c-dev.h> 

#define DEVICE_PATH_NAME "/dev/axi_pwm-1"

#define REG_CONTROL_OFFSET 0x00
#define REG_PRESCALE_OFFSET     0x04
#define REG_RESOLUTION_OFFSET   0x08
#define REG_DUTY_OFFSET         0x0C


int init(const char *pathname)
{
    int fd;
    fd=open(pathname,O_RDWR);//打开eeprom设备文件结点 
    if(fd<0){
        perror("open error");
        return -1;
    }
    printf("open %s sucess.\r\n",pathname);
    return fd;
    }

int write_reg(int fd,int reg,int val)
{
    int ret;
    int data;
    data = val;
    ret=ioctl(fd,reg,(unsigned long)data);//通过ioctl进行实际写入操作，后面会详细分析 
    if(ret<0) {
        perror("ioctl error");
    }
    return ret;
}


int main()
{
    int fd;

    printf("cat9555 test\r\n");

    unsigned char data=0;
    fd = init(DEVICE_PATH_NAME);
    if(fd<0)
        return 0;

    write_reg(fd,REG_PRESCALE_OFFSET,100*1000*1000);
    write_reg(fd,REG_RESOLUTION_OFFSET,4);
    write_reg(fd,REG_DUTY_OFFSET,2);
    sleep(10);
    
    while(1){
        sleep(10);
        write_reg(fd,REG_DUTY_OFFSET,data);
        sleep(10);
        data++;
        if(data==4)
            data = 0;
    }

    close(fd);

    sleep(1);
    return 0;
}



