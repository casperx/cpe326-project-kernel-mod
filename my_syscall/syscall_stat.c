#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE3(syscall_stat, int, pid, int __user *, _total, int __user *, _counts)
{
    struct task_struct *t;
    int total;
/*
    int i;
*/
    total = NR_syscalls;
    t = find_task_by_vpid(pid);

    if (t == NULL) {
        printk("process %d not found\n", pid);
        return -1;
    }
    printk("Get syscall stat of process %s\n", t->comm);

/*
    printk("Total syscall: %d\n", total);
    for (i = 0; i < total; ++i)
        printk("Syscall #%d count: %d\n", i, t->syscallstat[i]);
*/
    if (copy_to_user(_total, &total, sizeof(int)) ||
        copy_to_user(_counts, &t->syscall_stat_data, sizeof(int) * total)) return -1;

    return 0;
}
