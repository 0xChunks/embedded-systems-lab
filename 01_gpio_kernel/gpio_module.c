#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>

#define LED_PIN 17
#define BUTTON_PIN 18

int button_value = 0;

static int __init my_init(void) {

    
    gpio_direction_input(BUTTON_PIN);
    gpio_direction_output(LED_PIN, 0);

    if(!gpio_is_valid(LED_PIN)) {
        pr_err("GPIO %d is not valid\n", LED_PIN);
        return -ENODEV;
    }

    if(gpio_request(LED_PIN, "gpio17_led") < 0) {
        pr_err("Failed to request GPIO %d\n", LED_PIN);
        return -EBUSY;
    }

    if(!gpio_is_valid(BUTTON_PIN)) {
	    pr_err("GPIO %d is not valid\n", BUTTON_PIN);
	    return -ENODEV;
    }

    if(gpio_request(BUTTON_PIN, "gpio18_button") < 0) {
	    pr_err("Failed to request GPIO %d\n", BUTTON_PIN);
	    return -EBUSY;
    }

    button_value = gpio_get_value(BUTTON_PIN);
    pr_info("Button value is: %d\n", button_value);

    if(button_value) {
        gpio_set_value(LED_PIN, 1);
        pr_info("Button pressed -> LED ON\n");
    } else {
        gpio_set_value(LED_PIN, 0);
        pr_info("Button not pressed -> LED OFF\n");
    }

    return 0;

}

static void __exit my_exit(void) {

    pr_info("Turning GPIO %d OFF\n", LED_PIN);
    gpio_set_value(LED_PIN, 0);
    gpio_free(BUTTON_PIN);
    gpio_free(LED_PIN);

}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("0xChunks");
MODULE_DESCRIPTION("My first gpio kernel module");
