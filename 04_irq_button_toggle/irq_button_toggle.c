#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/jiffies.h>

#define DEBOUNCE_DELAY_MS 100
static unsigned long last_press_time = 0;

#define LED_PIN 17
#define BUTTON_PIN 18

static int irq_number;

static irqreturn_t button_irq_handler(int irq, void *dev_id) {

    unsigned long current_time = jiffies;

    if (time_before(current_time, last_press_time + msecs_to_jiffies(DEBOUNCE_DELAY_MS))) return IRQ_HANDLED;

    last_press_time = current_time;

    static bool led_on = false;
    led_on = !led_on;
    gpio_set_value(LED_PIN, led_on);
    pr_info("Interrupt: Button press detected. LED is now %s\n", led_on ? "ON" : "OFF");
    return IRQ_HANDLED;

}

static int __init irq_init(void)
{

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

    gpio_direction_input(BUTTON_PIN);
    gpio_direction_output(LED_PIN, 0);

    irq_number = gpio_to_irq(BUTTON_PIN);
    if(irq_number < 0) {
        pr_err("Failed to map GPIO to IRQ\n");
        return irq_number;
    }

    if (request_irq(irq_number, button_irq_handler, IRQF_TRIGGER_FALLING, "gpio_button_irq", NULL)) {
        pr_err("IRQ request failed\n");
        return -EIO;
    }

    pr_info("IRQ module initialized\n");
    return 0;
}

static void __exit irq_module_exit(void)
{
    gpio_free(BUTTON_PIN);
    gpio_free(LED_PIN);

    free_irq(irq_number, NULL);

    pr_info("IRQ module exited\n");
}

module_init(irq_init);
module_exit(irq_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("0xChunks");
MODULE_DESCRIPTION("GPIO Interrupt Example");
