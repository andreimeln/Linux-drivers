#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");

#define LIMIT 20

static short count = 5;
module_param(count, short, 0644); 
MODULE_PARM_DESC(count, "Quantity of philosophers");

static short food = 10;
module_param(food, short, 0644); 
MODULE_PARM_DESC(food, "Quantity of food");

static unsigned int Food[LIMIT];
static struct semaphore Stick[LIMIT]; // sticks for eating rice
static struct task_struct *People[LIMIT];

static int Numbers[LIMIT];

int dinner_process(void *data)
{
  // one philosopher is eating here
  int n = *(int *)data;

  while (Food[n] > 0)
    {
      if (down_trylock(Stick + n))
	{
	  schedule();
	  continue;
	}

      if (down_trylock(Stick + (n+1)%count))
	{
	  up(Stick + n);
	  schedule();
	  continue;
	}

      // useful work starts here
      //send_request_for(Food+n);// the cell where the answer goes
      //wait_event
      Food[n] -= 1;
      
      // useful work finished here
      up(Stick + (n+1) % count); // give the stick to another
      up(Stick + n);

      schedule_timeout(n);
      
      printk(KERN_ALERT "Rest of %d is %d\n", n, Food[n]);
    }

  return 0;
}

int __init init_module()
{

  int RetCode = 0;
  int k;
  
  if (count < 0 || count > LIMIT)
    {
      RetCode = -EINVAL;
      goto END;
    }

  // preparing the sticks
  for (k = 0; k < count; k++)
    {
      sema_init(Stick+k, 1);
    }

  // doling rice to dishes
  for (k = 0; k < count; k++)
    {
      Food[k] = food;
      Numbers[k] = k;
    }

  // dinner starting
  for (k = 0; k < count; k++)
    {
      People[k] = kthread_run(dinner_process,
			      (void *)(Numbers+k),
			      "dinner%d", k);
    }  
  
  printk(KERN_ALERT "Dinner started\n");
  return 0;

END:
  return RetCode;
}

void __exit cleanup_module()
{
  printk(KERN_ALERT "Dinner finished\n");
}
