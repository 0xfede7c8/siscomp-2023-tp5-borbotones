/***************************************************************************//**
*  \file       driver.c
*
*  \details    Simple GPIO driver explanation
*
*  \Tested with Linux raspberrypi 5.4.51-v7l+
*
*******************************************************************************/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/uaccess.h>  //copy_to/from_user()
#include <linux/gpio.h>     //GPIO
#include <linux/err.h>


//Definiciones de los gpio donde estan los sensores
#define DIST_BIT_0 (2)
#define DIST_BIT_1 (3)
#define DIST_BIT_2 (4)
#define DIST_BIT_3 (17)
#define DIST_BIT_4 (27)
#define DIST_BIT_5 (22)
#define DIST_BIT_6 (10)
#define DIST_BIT_7 (9)

#define POTE_BIT_0 (14)
#define POTE_BIT_1 (15)
#define POTE_BIT_2 (18)
#define POTE_BIT_3 (23)
#define POTE_BIT_4 (24)
#define POTE_BIT_5 (25)
#define POTE_BIT_6 (8)
#define POTE_BIT_7 (7)

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;
 
static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);
 
 
/*************** Driver functions **********************/
static int etx_open(struct inode *inode, struct file *file);
static int etx_release(struct inode *inode, struct file *file);
static ssize_t etx_read(struct file *filp, 
                char __user *buf, size_t len,loff_t * off);
static ssize_t etx_write(struct file *filp, 
                const char *buf, size_t len, loff_t * off);
/******************************************************/
 
//File operation structure 
static struct file_operations fops =
{
  .owner          = THIS_MODULE,
  .read           = etx_read,
  .write          = etx_write,
  .open           = etx_open,
  .release        = etx_release,
};
/*
** This function will be called when we open the Device file
*/ 
static int etx_open(struct inode *inode, struct file *file)
{
  pr_info("Device File Opened...!!!\n");
  return 0;
}
/*
** This function will be called when we close the Device file
*/
static int etx_release(struct inode *inode, struct file *file)
{
  pr_info("Device File Closed...!!!\n");
  return 0;
}
/*
** This function will be called when we read the Device file
*/ 
static ssize_t etx_read(struct file *filp, 
                char __user *buf, size_t len, loff_t *off)
{
  return 0;
}
/*
** This function will be called when we write the Device file
*/ 
static ssize_t etx_write(struct file *filp, 
                const char __user *buf, size_t len, loff_t *off)
{
  return 0;
}
/*
** Module Init function
*/ 
static int __init etx_driver_init(void)
{
  /*Allocating Major number*/
  if((alloc_chrdev_region(&dev, 0, 1, "etx_Dev")) <0){
    pr_err("Cannot allocate major number\n");
    goto r_unreg;
  }
  pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
  /*Creating cdev structure*/
  cdev_init(&etx_cdev,&fops);
 
  /*Adding character device to the system*/
  if((cdev_add(&etx_cdev,dev,1)) < 0){
    pr_err("Cannot add the device to the system\n");
    goto r_del;
  }
 
  /*Creating struct class*/
  if(IS_ERR(dev_class = class_create(THIS_MODULE,"etx_class"))){
    pr_err("Cannot create the struct class\n");
    goto r_class;
  }
 
  /*Creating device*/
  if(IS_ERR(device_create(dev_class,NULL,dev,NULL,"etx_device"))){
    pr_err( "Cannot create the Device \n");
    goto r_device;
  }
  
  int gpios_valid = gpio_is_valid(DIST_BIT_0) && 
                    gpio_is_valid(DIST_BIT_1) && 
                    gpio_is_valid(DIST_BIT_2) && 
                    gpio_is_valid(DIST_BIT_3) && 
                    gpio_is_valid(DIST_BIT_4) && 
                    gpio_is_valid(DIST_BIT_5) && 
                    gpio_is_valid(DIST_BIT_6) && 
                    gpio_is_valid(DIST_BIT_7) && 
                    gpio_is_valid(POTE_BIT_0) && 
                    gpio_is_valid(POTE_BIT_1) && 
                    gpio_is_valid(POTE_BIT_2) && 
                    gpio_is_valid(POTE_BIT_3) && 
                    gpio_is_valid(POTE_BIT_4) && 
                    gpio_is_valid(POTE_BIT_5) && 
                    gpio_is_valid(POTE_BIT_6) && 
                    gpio_is_valid(POTE_BIT_7);

  if(gpios_valid == false){
    pr_err("ERROR: some GPIO is not valid\n");
    goto r_device;
  }
  
  //Requesting the GPIO
  int gpios_request = gpio_request(DIST_BIT_0, "DIST_BIT_0") && 
                    gpio_request(DIST_BIT_1, "DIST_BIT_1") && 
                    gpio_request(DIST_BIT_2, "DIST_BIT_2") && 
                    gpio_request(DIST_BIT_3, "DIST_BIT_3") && 
                    gpio_request(DIST_BIT_4, "DIST_BIT_4") && 
                    gpio_request(DIST_BIT_5, "DIST_BIT_5") && 
                    gpio_request(DIST_BIT_6, "DIST_BIT_6") && 
                    gpio_request(DIST_BIT_7, "DIST_BIT_7") && 
                    gpio_request(POTE_BIT_0, "POTE_BIT_0") && 
                    gpio_request(POTE_BIT_1, "POTE_BIT_1") && 
                    gpio_request(POTE_BIT_2, "POTE_BIT_2") && 
                    gpio_request(POTE_BIT_3, "POTE_BIT_3") && 
                    gpio_request(POTE_BIT_4, "POTE_BIT_4") && 
                    gpio_request(POTE_BIT_5, "POTE_BIT_5") && 
                    gpio_request(POTE_BIT_6, "POTE_BIT_6") && 
                    gpio_request(POTE_BIT_7, "POTE_BIT_7");

  if(gpios_request < 0){
    pr_err("ERROR: couldn't request GPIO\n");
    goto r_gpio;
  }
  
  // Configuramos como input
  gpio_direction_input(DIST_BIT_0);
  gpio_direction_input(DIST_BIT_1);
  gpio_direction_input(DIST_BIT_2);
  gpio_direction_input(DIST_BIT_3);
  gpio_direction_input(DIST_BIT_4);
  gpio_direction_input(DIST_BIT_5);
  gpio_direction_input(DIST_BIT_6);
  gpio_direction_input(DIST_BIT_7);

  gpio_direction_input(POTE_BIT_0);
  gpio_direction_input(POTE_BIT_1);
  gpio_direction_input(POTE_BIT_2);
  gpio_direction_input(POTE_BIT_3);
  gpio_direction_input(POTE_BIT_4);
  gpio_direction_input(POTE_BIT_5);
  gpio_direction_input(POTE_BIT_6);
  gpio_direction_input(POTE_BIT_7);
  
  /* 
    Exportamos los archivos de gpio
  */
  gpio_export(DIST_BIT_0, false);
  gpio_export(DIST_BIT_1, false);
  gpio_export(DIST_BIT_2, false);
  gpio_export(DIST_BIT_3, false);
  gpio_export(DIST_BIT_4, false);
  gpio_export(DIST_BIT_5, false);
  gpio_export(DIST_BIT_6, false);
  gpio_export(DIST_BIT_7, false);

  gpio_export(POTE_BIT_0, false);
  gpio_export(POTE_BIT_1, false);
  gpio_export(POTE_BIT_2, false);
  gpio_export(POTE_BIT_3, false);
  gpio_export(POTE_BIT_4, false);
  gpio_export(POTE_BIT_5, false);
  gpio_export(POTE_BIT_6, false);
  gpio_export(POTE_BIT_7, false);

  pr_info("Device Driver Insert...Done!!!\n");
  return 0;
 
r_gpio:
  gpio_free(DIST_BIT_0);
  gpio_free(DIST_BIT_1);
  gpio_free(DIST_BIT_2);
  gpio_free(DIST_BIT_3);
  gpio_free(DIST_BIT_4);
  gpio_free(DIST_BIT_5);
  gpio_free(DIST_BIT_6);
  gpio_free(DIST_BIT_7);

  gpio_free(POTE_BIT_0);
  gpio_free(POTE_BIT_1);
  gpio_free(POTE_BIT_2);
  gpio_free(POTE_BIT_3);
  gpio_free(POTE_BIT_4);
  gpio_free(POTE_BIT_5);
  gpio_free(POTE_BIT_6);
  gpio_free(POTE_BIT_7);
r_device:
  device_destroy(dev_class,dev);
r_class:
  class_destroy(dev_class);
r_del:
  cdev_del(&etx_cdev);
r_unreg:
  unregister_chrdev_region(dev,1);
  
  return -1;
}
/*
** Module exit function
*/ 
static void __exit etx_driver_exit(void)
{
  gpio_unexport(DIST_BIT_0);
  gpio_unexport(DIST_BIT_1);
  gpio_unexport(DIST_BIT_2);
  gpio_unexport(DIST_BIT_3);
  gpio_unexport(DIST_BIT_4);
  gpio_unexport(DIST_BIT_5);
  gpio_unexport(DIST_BIT_6);
  gpio_unexport(DIST_BIT_7);

  gpio_unexport(POTE_BIT_0);
  gpio_unexport(POTE_BIT_1);
  gpio_unexport(POTE_BIT_2);
  gpio_unexport(POTE_BIT_3);
  gpio_unexport(POTE_BIT_4);
  gpio_unexport(POTE_BIT_5);
  gpio_unexport(POTE_BIT_6);
  gpio_unexport(POTE_BIT_7);

  gpio_free(DIST_BIT_0);
  gpio_free(DIST_BIT_1);
  gpio_free(DIST_BIT_2);
  gpio_free(DIST_BIT_3);
  gpio_free(DIST_BIT_4);
  gpio_free(DIST_BIT_5);
  gpio_free(DIST_BIT_6);
  gpio_free(DIST_BIT_7);

  gpio_free(POTE_BIT_0);
  gpio_free(POTE_BIT_1);
  gpio_free(POTE_BIT_2);
  gpio_free(POTE_BIT_3);
  gpio_free(POTE_BIT_4);
  gpio_free(POTE_BIT_5);
  gpio_free(POTE_BIT_6);
  gpio_free(POTE_BIT_7);

  device_destroy(dev_class,dev);
  class_destroy(dev_class);
  cdev_del(&etx_cdev);
  unregister_chrdev_region(dev, 1);
  pr_info("Device Driver Remove...Done!!\n");
}
 
module_init(etx_driver_init);
module_exit(etx_driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Borbotones");
MODULE_DESCRIPTION("Driver que lee sensores por GPIO");
MODULE_VERSION("1.00");