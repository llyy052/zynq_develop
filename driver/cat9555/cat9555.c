#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/device.h>

#include <linux/i2c.h>
#include <linux/mutex.h>


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

struct cat9555_data {
    struct mutex device_lock;	/* for "atomic" device accesses */
    struct mutex update_lock;
    unsigned long next_update;
    int vref_cached;
    struct i2c_client *client;
};
static const unsigned short normal_i2c[] = { 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    I2C_CLIENT_END };
#if 0
static int cat9555_read_byte(struct i2c_client *client, u8 command)
{
    struct cat9555_data *data = i2c_get_clientdata(client);
    int ret;
    mutex_lock(&data->device_lock);
    ret = i2c_smbus_read_byte_data(client, command);
    mutex_unlock(&data->device_lock);
    return ret;
}

static int cat9555_write_byte(struct i2c_client *client, u8 command, u8 val)
{
    struct cat9555_data *data = i2c_get_clientdata(client);
    int ret;
    mutex_lock(&data->device_lock);
    ret = i2c_smbus_write_byte_data(client, command, val);
    mutex_unlock(&data->device_lock);
    return ret;
}

static int cat9555_read_word(struct i2c_client *client, u8 command)
{
    struct cat9555_data *data = i2c_get_clientdata(client);
    int ret;
    mutex_lock(&data->device_lock);
    ret = i2c_smbus_read_word_data(client, command);
    mutex_unlock(&data->device_lock);
    return ret;
}
static int transfer(struct i2c_adapter *adap, struct i2c_msg *msgs, int num)
{
    return i2c_transfer(adap,msgs,num);
}
#endif
static int cat9555_write_word(struct i2c_client *client, u8 command, u16 val)
{
    struct cat9555_data *data = i2c_get_clientdata(client);
    int ret;
    mutex_lock(&data->device_lock);
    ret = i2c_smbus_write_word_data(client,command,val);
    mutex_unlock(&data->device_lock);
    return ret;
}

static int cat9555_detect(struct i2c_client *client,
            struct i2c_board_info *info)
{
    printk("cat9555_detect\r\n");
    if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
        return -ENODEV;

    strlcpy(info->type, "cat9555_2", I2C_NAME_SIZE);

    return 0;
}


static int cat9555_probe(struct i2c_client *client,
            const struct i2c_device_id *id)
{
    struct device *dev = &client->dev;
    struct cat9555_data *data;
    int ret;
    
    printk("cat9555_probe/r/n");
    data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
    if (!data)
        return -ENOMEM;

    i2c_set_clientdata(client, data);
    data->client = client;
    mutex_init(&data->device_lock);
    mutex_init(&data->update_lock);

    ret = cat9555_write_word(client,CONFIGURATION_PORT0,0x00);
    printk("%d,",ret);
    ret = cat9555_write_word(client,POLARITY_INVERSION_POART0,0xff00);
    printk("%d,",ret);
    ret = cat9555_write_word(client,OUTPUT_PORT0,0x5555);
    printk("%d,",ret);
    
    //ret = cat9555_read_word(client,OUTPUT_PORT0);
    //printk("cat9555_probe,read port0:%d",ret);
    
    data->next_update = jiffies;

    return 0;
}
static int cat9555_ioctl(struct i2c_client *client, unsigned int cmd, void *arg)
{
    printk("cat9555_ioctl cmd=%d",cmd);
    return 0;
}

static const struct i2c_device_id cat9555_id[] = {
    { "cat,9555", 0 },
    { "cat,9555"},
    { }
};
MODULE_DEVICE_TABLE(i2c, cat9555_id);

static struct i2c_driver cat9555_driver = {
    .driver = {
        .name = "cat9555",
    },
    .probe  = cat9555_probe,
    .id_table = cat9555_id,
    .detect = cat9555_detect,
    .command = cat9555_ioctl,//module_i2c_driver(tuner_driver);
    .address_list = normal_i2c,
    //.class = I2C_CLASS_HWMON,
};

module_i2c_driver(cat9555_driver);

MODULE_AUTHOR("gang-gang");
MODULE_DESCRIPTION("cat9555 driver");
MODULE_LICENSE("GPL v2");

