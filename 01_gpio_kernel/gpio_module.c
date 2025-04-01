#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>

#define LED_PIN 17


static int __init my_init(void) {

    if(!gpio_is_valid(LED_PIN)) {
        pr_err("GPIO %d is not valid\n", LED_PIN);
        return -ENODEV;
    }

    if(gpio_request(LED_PIN, "gpio17_led") < 0) {
        pr_err("Failed to request GPIO %d\n", LED_PIN);
        return -EBUSY;
    }

    gpio_direction_output(LED_PIN, 1);
    pr_info("GPIO %d is now ON\n", LED_PIN);

    return 0;

}

static void __exit my_exit(void) {

    pr_info("Turning GPIO %d OFF\n", LED_PIN);
    gpio_set_value(LED_PIN, 0);
    gpio_free(LED_PIN);

}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("0xChunks");
MODULE_DESCRIPTION("My first gpio kernel module");