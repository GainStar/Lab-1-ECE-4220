#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/uaccess.h>  
#include <linux/gpio.h>     
#include <linux/interrupt.h>
#include <linux/err.h>




MODULE_LICENSE("GPL");

static int __init lkm_example_init(void) {
    printk(KERN_INFO "Module installed! -- New style\n");
     

for(int j=2;j<6;j++)                        // Go through LED Red 2, Yellow 3, Green 4, amd Blue 5
{

   if(!gpio_is_valid(j))                    // Checks if the gpio pins are valid
		{
			 printk(KERN_ERR "Failed to valid GPIO %d\n", j);
        	return -1;
		}

    if (gpio_request(j, "LED")) {           // Reserves the gpio pins 
        printk(KERN_ERR "Failed to request GPIO %d\n", j);
        return -1;
    }

    
    if (gpio_direction_output(j, 0)) {      // Sets gpio pins as output
        printk(KERN_ERR "Failed to set GPIO %d as output\n", j);
         return -1;

    }
    

    for (int i = 0; i < 5; i++) {           // Makes the LED blink 5 times before turning off
        gpio_set_value(j, 1); 
        printk(KERN_INFO "LED ON\n");
        msleep(1000);                        // Sleeps for 1 sec

        gpio_set_value(j, 0); 
        printk(KERN_INFO "LED OFF\n");
        msleep(1000);                         // Sleep for 1 sec
    }
}   
    return 0;
}

static void __exit lkm_example_exit(void) {
    printk(KERN_INFO "Module removed! -- New style\n");
    for(int j=2;j<6;j++)                        // This loop free the gpio pins turning them back on
    {
        gpio_set_value(j, 0);
        gpio_free(j);         
    }
}


module_init(lkm_example_init);

module_exit(lkm_example_exit);

