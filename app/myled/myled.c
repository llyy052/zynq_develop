#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/device.h>

volatile unsigned int *  led_reg=NULL;
static struct class *myled_class;
static struct device *myled_class_dev;
int major;

static int myled_open(struct inode *inode, struct file *file)
{
	printk("Open LED_DRV\n");
	return 0;
}

int myled_release(struct inode *inode, struct file *filp)
{
  return 0;
}

static ssize_t myled_write(struct file *file, const char __user *buf, size_t count, loff_t * ppos)
{       
    int val;
	//printk("Open MY_LED_write\n");
	copy_from_user(&val,buf,count);
	*led_reg=val;
	return 0;
}

static ssize_t myled_read (struct file *file,  char __user *buf, size_t count, loff_t * ppos)
{       
	int val = *led_reg;
	//printk("Open MY_LED_read\n");
	copy_to_user(buf,&val,count);	
	return 0;
}

static loff_t myled_llseek(struct file *filp, loff_t offset, int whence)
{ 
    loff_t newpos=0;   
#if 0
    switch(whence) {
      case 0: /* SEEK_SET */       /*相对文件开始位置偏移*/ 
        newpos = offset;           /*更新文件指针位置*/
        break;
      case 1: /* SEEK_CUR */
        newpos = filp->f_pos + offset;    
        break;
      case 2: /* SEEK_END */
        newpos = MEMDEV_SIZE -1 + offset;
        break;
      default: /* can't happen */
        return -EINVAL;
    }

    if ((newpos<0) || (newpos>MEMDEV_SIZE))
        return -EINVAL;
#endif 
    filp->f_pos = newpos;
    return newpos;
}

static struct file_operations myled_fops = {
        .owner    =   THIS_MODULE,   
        .open     =   myled_open,       //open 
        .write    =   myled_write,   //write 
        .read     =   myled_read,  //read 

	.llseek   =   myled_llseek, //seek
	.release  =   myled_release,//close 
};

static int  /*__init*/  myled_init(void)
{
	major=register_chrdev(0, "myled", &myled_fops);
        myled_class = class_create(THIS_MODULE, "myled");
        myled_class_dev = device_create(myled_class, NULL, MKDEV(major, 0), NULL, "myled");

	//    /dev/myled 	
	led_reg=(volatile unsigned int  *)ioremap(0x43c00000  ,32);
	*led_reg = 0x55;// 0101 0101	
	printk("Open LED_init\n");	
	return 0;
}

static void /*__exit n*/  myled_exit(void)
{
	*led_reg = 0x00;
	unregister_chrdev(major, "myled"); 
        device_unregister(myled_class_dev);
        class_destroy(myled_class);		

	iounmap(led_reg);    
	printk(" MY_LED_exit\n");
	//return 0;

}

module_init(myled_init); // insmod
module_exit(myled_exit); // rmmod

MODULE_LICENSE("GPL");




