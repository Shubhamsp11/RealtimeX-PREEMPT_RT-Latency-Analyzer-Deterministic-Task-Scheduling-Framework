#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DRIVER_NAME "realtimex"
#define TIMER_TIMEOUT 1000 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RealtimeX Author");
MODULE_DESCRIPTION("RealtimeX Kernel Module with Timer and Char Device");
MODULE_VERSION("1.0");

static struct timer_list rt_timer;
static int timer_event_count = 0;
static int major_number;

static void timer_callback(struct timer_list *t)
{
    timer_event_count++;
    printk(KERN_INFO "RealtimeX: Timer event #%d\n", timer_event_count);
    
    if (timer_event_count < 5) {
        mod_timer(&rt_timer, jiffies + msecs_to_jiffies(TIMER_TIMEOUT));
    } else {
        printk(KERN_INFO "RealtimeX: Timer finished.\n");
    }
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
    char msg[256];
    int bytes_read;
    
    snprintf(msg, sizeof(msg), "Timer events recorded: %d\n", timer_event_count);
    bytes_read = strlen(msg);
    
    if (*offset >= bytes_read) return 0;
    
    if (copy_to_user(buffer, msg, bytes_read)) {
        return -EFAULT;
    }
    
    *offset += bytes_read;
    return bytes_read;
}

static struct file_operations fops = {
    .read = dev_read,
};

static int __init rt_module_init(void)
{
    printk(KERN_INFO "RealtimeX kernel module started\n");
    
    major_number = register_chrdev(0, DRIVER_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "RealtimeX: failed to register a major number\n");
        return major_number;
    }
    printk(KERN_INFO "RealtimeX: registered correctly with major number %d\n", major_number);
    
    timer_setup(&rt_timer, timer_callback, 0);
    mod_timer(&rt_timer, jiffies + msecs_to_jiffies(TIMER_TIMEOUT));
    
    return 0;
}

static void __exit rt_module_exit(void)
{
    del_timer(&rt_timer);
    unregister_chrdev(major_number, DRIVER_NAME);
    printk(KERN_INFO "RealtimeX kernel module unloaded\n");
}

module_init(rt_module_init);
module_exit(rt_module_exit);
