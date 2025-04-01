#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/fs.h>

#define LED_PIN 17
#define BUTTON_PIN 18

#define DEVICE_NAME "gpiodev"

int button_value = 0;

static int major_num;
static struct class *gpio_char_class;
static struct device *gpio_char_device;



static ssize_t gpiodev_read(struct file *file, char __user *buf, size_t len, loff_t *offset)
{
    int value;
    value = gpio_get_value(BUTTON_PIN);
    char out[2];

    snprintf(out, sizeof(out), "%d\n", value);

    if (*offset > 0) return 0; // prevent repeated reads
    if (copy_to_user(buf, out, strlen(out))) return -EFAULT;

    *offset = strlen(out);
    return strlen(out);

}

static ssize_t gpiodev_write(struct file *file, const char __user *buf, size_t len, loff_t *offset)
{
    char kbuf[4];
    int value;

    if (len > sizeof(kbuf) - 1)
        return -EINVAL;

    if (copy_from_user(kbuf, buf, len))
        return -EFAULT;

    kbuf[len] = '\0';  // Null-terminate
    if (kstrtoint(kbuf, 10, &value) == 0) {
        gpio_set_value(LED_PIN, value ? 1 : 0);
    }

    return len;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = gpiodev_read,
    .write = gpiodev_write
};

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

    major_num = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_num < 0) {
        pr_err("Failed to register char device\n");
        return major_num;
    }
    
    gpio_char_class = class_create(THIS_MODULE, "gpio_class");
    if (IS_ERR(gpio_char_class)) {
        unregister_chrdev(major_num, DEVICE_NAME);
        pr_err("Failed to create device class\n");
        return PTR_ERR(gpio_char_class);
    }
    
    gpio_char_device = device_create(gpio_char_class, NULL, MKDEV(major_num, 0), NULL, DEVICE_NAME);
    if (IS_ERR(gpio_char_device)) {
        class_destroy(gpio_char_class);
        unregister_chrdev(major_num, DEVICE_NAME);
        pr_err("Failed to create device\n");
        return PTR_ERR(gpio_char_device);
    }

    return 0;

}

static void __exit my_exit(void) {

    pr_info("Turning GPIO %d OFF\n", LED_PIN);
    gpio_set_value(LED_PIN, 0);
    gpio_free(BUTTON_PIN);
    gpio_free(LED_PIN);

    device_destroy(gpio_char_class, MKDEV(major_num, 0));
    class_destroy(gpio_char_class);
    unregister_chrdev(major_num, DEVICE_NAME);


}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("0xChunks");
MODULE_DESCRIPTION("My first char devicve driver");