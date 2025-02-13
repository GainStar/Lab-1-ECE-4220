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
#include <linux/jiffies.h>



MODULE_LICENSE("GPL");



int InputPin=16, OutPin=3;
int GPIO_irqNumber;




// Interrupt handler function. Tha name "button_isr" can be different.
// You may use printk statements for debugging purposes.

//Interrupt handler for InputPin. This will be called whenever there is a raising edge detected. 
static irqreturn_t gpio_irq_handler(int irq,void *dev_id) 
{
 
	disable_irq(InputPin);
    
  

   // Stuff you want the module do when the interrupt handler is called 
  



	
  
  
	//enable_irq(InputPin);
	printk("Interrupt handled\n");

	return IRQ_HANDLED;
}



/*
** Module Init function
*/ 
int init_module()   // Call the default name
{




	// Configure the output and the input pins	





	
	


	//Get the IRQ number for our GPIO
	GPIO_irqNumber = gpio_to_irq(InputPin);
 	

 	// Request the interrupt / attach handler
 	//Enable (Async) Rising Edge detection
	
	//The Fourth argument string can be different (you give the name)
	//The last argument is a variable needed to identify the handler, but can be set to NULL
	if (request_irq(GPIO_irqNumber,(void *)gpio_irq_handler, IRQF_TRIGGER_RISING,"Button Interrupt", NULL)) {                    //device id for shared IRQ
	pr_err("Cannot register the IRQ ");
	gpio_free(InputPin);
	}





	pr_info("Module Inserted!!!\n");
	return 0;

}

/*
** Module exit function
*/
void cleanup_module() 
{

	// ------
	// Remove the interrupt handler; you need to provide the same identifier

	free_irq(GPIO_irqNumber,NULL);
	
	// Free the Pins
	gpio_free(InputPin);
	gpio_free(OutPin);


	printk("*************Module Removed**********\n");
}
 

 

