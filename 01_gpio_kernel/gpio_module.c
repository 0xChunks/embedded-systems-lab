#include <linux/module.h>
#include <linux/init.h>

static int __init my_init(void) {

    printk("Hello World!");
    return 0;

}

static void __exit my_exit(void) {
    printk("Goodbye World!");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("0xChunks");
MODULE_DESCRIPTION("My first gpio kernel module");