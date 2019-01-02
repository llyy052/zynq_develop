
#if 0
struct i2c_msg { //i2c消息结构体，每个i2c消息对应一个结构体
     __u16 addr; /* 从设备地址，此处就是eeprom地址，即0x50 */
     __u16 flags;    /* 一些标志，比如i2c读等*/
     __u16 len;      /* i2c消息的长度 */
     __u8 *buf;      /* 指向i2c消息中的数据 */
 };

 struct i2c_rdwr_ioctl_data {
     struct i2c_msg __user *msgs;    /* 指向一个i2c消息 */
     __u32 nmsgs;            /* i2c消息的数量 */
 };
#endif


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

#define DEVICE_PATH_NAME "/dev/i2c-0"
//#define DEVICE_PATH_NAME "/dev/i2c-1"
#define CAT9555_DEVICE_ADDR 0x27

typedef enum{
	INPUT_PORT0=0,
	INPUT_PORT1,
	OUTPUT_PORT0,
	OUTPUT_PORT1,
	POLARITY_INVERSION_POART0,
	POLARITY_INVERSION_POART1,
	CONFIGURATION_PORT0,
	CONFIGURATION_PORT1,
}CAT9555_CMD_e;

int cat9555_init(const char *pathname)
{
    int fd;
    fd=open(pathname,O_RDWR);//打开eeprom设备文件结点 
    if(fd<0){
        perror("open error");
		return -1;
    }
    
    ioctl(fd,I2C_TIMEOUT,1);/*超时时间*/
    ioctl(fd,I2C_RETRIES,2);/*重复次数*/
	printf("open %s sucess.\r\n",pathname);
	return fd;
}

int cat9555_write_reg(int fd,unsigned char devAddr,CAT9555_CMD_e cmd,unsigned char data)
{
    int ret;
    struct i2c_rdwr_ioctl_data e2prom_data;
    e2prom_data.nmsgs=1;
    e2prom_data.msgs=(struct i2c_msg*)malloc(e2prom_data.nmsgs*sizeof(struct i2c_msg));//分配空间 
    if(!e2prom_data.msgs){
        perror("malloc error");
        exit(1);
    }
    e2prom_data.nmsgs=1;//由前面eeprom读写分析可知，写eeprom需要一条消息 
    (e2prom_data.msgs[0]).len=2; //此消息的长度为2个字节，第一个字节是要写入数据的地址，第二个字节是要写入的数据 
    (e2prom_data.msgs[0]).addr=devAddr;//e2prom 设备地址 
    (e2prom_data.msgs[0]).flags=0; //写 
    (e2prom_data.msgs[0]).buf=(unsigned char*)malloc(2); 
    (e2prom_data.msgs[0]).buf[0]=cmd;// e2prom 写入目标的地址 
    (e2prom_data.msgs[0]).buf[1]=data;//写入的数据
	
    ret=ioctl(fd,I2C_RDWR,(unsigned long)&e2prom_data);//通过ioctl进行实际写入操作，后面会详细分析 
    if(ret<0) {
        perror("ioctl error1");
    }
	free((e2prom_data.msgs[0]).buf);
	free(e2prom_data.msgs);
	return ret;
}

unsigned char cat9555_read_reg(int fd,unsigned char devAddr,CAT9555_CMD_e cmd,unsigned char *pdata)
{
	int ret=0;
    unsigned char cmd_data;
    struct i2c_rdwr_ioctl_data e2prom_data;
	
    e2prom_data.nmsgs = 2;//读eeprom需要两条消息 
    e2prom_data.msgs = (struct i2c_msg*)malloc(e2prom_data.nmsgs*sizeof(struct i2c_msg));//分配空间 
    (e2prom_data.msgs[0]).len=1; //第一条消息实际是写eeprom，需要告诉eeprom需要读数据的地址，因此长度为1个字节 
    (e2prom_data.msgs[0]).addr=devAddr; // e2prom 设备地址 
    (e2prom_data.msgs[0]).flags=0;//先是写 
	(e2prom_data.msgs[0]).buf = &cmd_data;
    (e2prom_data.msgs[0]).buf[0] = cmd;//e2prom上需要读的数据的地址 
	
    (e2prom_data.msgs[1]).len=1;//第二条消息才是读eeprom， 
    (e2prom_data.msgs[1]).addr=devAddr;// e2prom 设备地址 
    (e2prom_data.msgs[1]).flags=I2C_M_RD;//然后是读 
    (e2prom_data.msgs[1]).buf = pdata;//存放返回值的地址。 

    ret=ioctl(fd,I2C_RDWR,(unsigned long)&e2prom_data);//通过ioctl进行实际的读操作 
    if(ret<0){ 
        perror("ioctl cat9555_read_reg error");
		ret = -1;
    }
	free(e2prom_data.msgs);
	return ret;
}

int main()
{
	int fd;
	
	printf("cat9555 test\r\n");
	sleep(1);
#if 1
	unsigned char data=0,readData;
	fd = cat9555_init(DEVICE_PATH_NAME);
	if(fd<0)
		return 0;
	sleep(1);
	
	cat9555_write_reg(fd,CAT9555_DEVICE_ADDR,CONFIGURATION_PORT0,0x00);//config port0 output
	sleep(1);
	cat9555_write_reg(fd,CAT9555_DEVICE_ADDR,CONFIGURATION_PORT1,0x00);//config port1 output
	sleep(1);
	cat9555_write_reg(fd,CAT9555_DEVICE_ADDR,POLARITY_INVERSION_POART1,0xff);//inversion port1
	
	while(1){
		sleep(1);
		cat9555_write_reg(fd,CAT9555_DEVICE_ADDR,OUTPUT_PORT0,data);
		sleep(1);
		cat9555_write_reg(fd,CAT9555_DEVICE_ADDR,OUTPUT_PORT1,data);
		sleep(1);
		data++;
		sleep(1);
		cat9555_read_reg(fd,CAT9555_DEVICE_ADDR,INPUT_PORT0,&readData);
		printf("%d,",readData);
	}
	
	close(fd);
#endif
	return 0;
}

#if 0
int main()
{
    int fd,ret;
    struct i2c_rdwr_ioctl_data e2prom_data;
    //fd=open("/dev/i2c/0",O_RDWR);//打开eeprom设备文件结点 
    fd=open("/dev/i2c-0",O_RDWR);//打开eeprom设备文件结点 
    if(fd<0){
        perror("open error");
    }
    e2prom_data.nmsgs=2;
    e2prom_data.msgs=(struct i2c_msg*)malloc(e2prom_data.nmsgs*sizeof(struct i2c_msg));//分配空间 
    if(!e2prom_data.msgs){
        perror("malloc error");
        exit(1);
    }
    
    ioctl(fd,I2C_TIMEOUT,1);/*超时时间*/
    ioctl(fd,I2C_RETRIES,2);/*重复次数*/
    
    /*写eeprom*/
    e2prom_data.nmsgs=1;//由前面eeprom读写分析可知，写eeprom需要一条消息 
    (e2prom_data.msgs[0]).len=2; //此消息的长度为2个字节，第一个字节是要写入数据的地址，第二个字节是要写入的数据 
    (e2prom_data.msgs[0]).addr=CAT9555_DEVICE_ADDR;//e2prom 设备地址 
    (e2prom_data.msgs[0]).flags=0; //写 
    (e2prom_data.msgs[0]).buf=(unsigned char*)malloc(2); 
    (e2prom_data.msgs[0]).buf[0]=0x10;// e2prom 写入目标的地址 
    (e2prom_data.msgs[0]).buf[1]=0x58;//写入的数据

    ret=ioctl(fd,I2C_RDWR,(unsigned long)&e2prom_data);//通过ioctl进行实际写入操作，后面会详细分析 
    if(ret<0) {
        perror("ioctl error1");
    }
    
    sleep(1); /*读eeprom*/
    
    e2prom_data.nmsgs=2;//读eeprom需要两条消息 
    (e2prom_data.msgs[0]).len=1; //第一条消息实际是写eeprom，需要告诉eeprom需要读数据的地址，因此长度为1个字节 
    (e2prom_data.msgs[0]).addr=CAT9555_DEVICE_ADDR; // e2prom 设备地址 
    (e2prom_data.msgs[0]).flags=0;//先是写 
    (e2prom_data.msgs[0]).buf[0]=0x10;//e2prom上需要读的数据的地址 
	
    (e2prom_data.msgs[1]).len=1;//第二条消息才是读eeprom， 
    (e2prom_data.msgs[1]).addr=CAT9555_DEVICE_ADDR;// e2prom 设备地址 
    (e2prom_data.msgs[1]).flags=I2C_M_RD;//然后是读 
    (e2prom_data.msgs[1]).buf=(unsigned char*)malloc(1);//存放返回值的地址。 
    (e2prom_data.msgs[1]).buf[0]=0;//初始化读缓冲，读到的数据放到此缓冲区 

    ret=ioctl(fd,I2C_RDWR,(unsigned long)&e2prom_data);//通过ioctl进行实际的读操作 
    if(ret<0){ 
        perror("ioctl error2");
    }
    
    printf("buff[0]=%x\n",(e2prom_data.msgs[1]).buf[0]); /***打印读出的值，没错的话，就应该是前面写的0x58了***/ 
    close(fd);
    return 0;
}
#endif


