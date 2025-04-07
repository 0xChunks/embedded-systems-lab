#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>

static int __init uart_init(void){

    pr_info("UART module initialized\n");
    return 0;
}

static void __exit uart_exit(void){

    pr_info("UART module exited\n");

}

module_init(uart_init);
module_exit(uart_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("0xChunks");
MODULE_DESCRIPTION("Bidirectional UART messaging with Arduino/ESP32");