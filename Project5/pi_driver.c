/*
 * Joseph Reidell <jmr240@pitt.edu>
 * Project 5: /dev/pi
 * CS 0449
 */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <asm/uaccess.h>

// This has the pi function
#include "pi.h"

/*
 * pi_read is the function called when a process calls read() on
 * /dev/pi.
 */

static ssize_t pi_read(struct file * file, char * buf, 
			  size_t count, loff_t *ppos)
{
	/*
	   This variable uses an equation to round up 
	   to the next multiple of 4.
	*/
	unsigned int pi_memory = (4 - (*ppos + count) % 4) + *ppos + count;

	/*
	   This variable uses the value from pi_memory 
	   to help allocate more space.
	*/
	char *pi_result = kmalloc(pi_memory, GFP_KERNEL);
	
	/*
	   This function generates a stream that goes up to the 
	   the desired index
	*/
	pi(pi_result, pi_memory);

	/*
	   This function copy's the string to the buffer
	   Before it displays it to the screen, it has to have
	   permission to write to the buffer.
	*/
	if (copy_to_user(buf, pi_result + *ppos, count)){
		kfree(pi_result);
		return -EINVAL;
	}

	/*
	   Free's the buffer first, then
	   Tell the user how much data we wrote.
	*/

	kfree(pi_result);
	
	*ppos += count;

	return count;
}

/*
 * The only file operation we care about is read.
 */

static const struct file_operations pi_fops = {
	.owner		= THIS_MODULE,
	.read		= pi_read,
};

static struct miscdevice pi_driver = {
	/*
	 * We don't care what minor number we end up with, so tell the
	 * kernel to just pick one.
	 */
	MISC_DYNAMIC_MINOR,
	/*
	 * Name ourselves /dev/pi_driver.
	 */
	"pi_driver",
	/*
	 * What functions to call when a program performs file
	 * operations on the device.
	 */
	&pi_fops
};

static int __init
pi_init(void)
{
	int ret;

	/*
	 * Create the "pi" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/hello device using
	 * the default rules.
	 */
	ret = misc_register(&pi_driver);
	if (ret)
		printk(KERN_ERR
		       "Unable to register \"pi digits\" misc device\n");

	return ret;
}

module_init(pi_init);

static void __exit
pi_exit(void)
{
	misc_deregister(&pi_driver);
}

module_exit(pi_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joseph Reidell <jmr240@pitt.edu>");
MODULE_DESCRIPTION("\"pi driver\" minimal module");
MODULE_VERSION("dev");
