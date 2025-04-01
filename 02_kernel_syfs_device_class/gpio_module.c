#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/device.h>


#define LED_PIN 17
#define BUTTON_PIN 18

static struct class *gpio_class;
static struct device *gpio_device;

int button_value = 0;


static ssize_t button_state_show(struct device *dev, struct device_attribute *attr, char *buf){
    int val;
    val = gpio_get_value(BUTTON_PIN);
    return sprintf(buf, "%d\n", val);
}

static ssize_t led_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    int val = gpio_get_value(LED_PIN);
    return sprintf(buf, "%d\n", val);
}

static ssize_t led_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t cnt){
    
    int input;
    kstrtoint(buf, 10, &input);
    gpio_set_value(LED_PIN, input);
    return cnt;

}

static DEVICE_ATTR_RO(button_state);
static DEVICE_ATTR_RW(led);

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

    gpio_class = class_create(THIS_MODULE, "gpio_driver");
    if (IS_ERR(gpio_class)) {
        pr_err("failed to create class\n");
        return PTR_ERR(gpio_class);
    }

    gpio_device = device_create(gpio_class, NULL, 0, NULL, "gpio_device");
    if(IS_ERR(gpio_device)) {
        class_destroy(gpio_class);
        pr_err("failed to create device\n");
        return PTR_ERR(gpio_device);
    }

    device_create_file(gpio_device, &dev_attr_button_state);
    device_create_file(gpio_device, &dev_attr_led);

    return 0;

}

static void __exit my_exit(void) {

    pr_info("Turning GPIO %d OFF\n", LED_PIN);
    gpio_set_value(LED_PIN, 0);
    gpio_free(BUTTON_PIN);
    gpio_free(LED_PIN);

    device_remove_file(gpio_device, &dev_attr_button_state);
    device_remove_file(gpio_device, &dev_attr_led);
    device_destroy(gpio_class, 0);
    class_destroy(gpio_class);

}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("0xChunks");
MODULE_DESCRIPTION("My first gpio kernel module");
