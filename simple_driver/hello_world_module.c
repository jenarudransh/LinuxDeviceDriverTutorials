#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

static int __init hello_world_init(void)      /*ENTRY  POINT  FOR THE  MODULE */
{
	printk("<1>Hello, world\n");
	return 0;
}


static void __exit hello_world_exit(void)      /*EXIT POINT FOR THE MODULE */
{
	printk("<1>Goodbye world\n");
}


module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE(" GPL");
MODULE_AUTHOR(" Rudransh");
MODULE_DESCRIPTION("A simple Hello world Driver");
MODULE_VERSION("1.0.0");
