#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/mutex.h>
#include <linux/semaphore.h>
#include <linux/slab.h> // Required for kmalloc and kfree
#include <linux/random.h> // Required for get_random_bytes

#define BUFFER_SIZE 4

static struct semaphore mutex;  // Controls access to the reader_count variable
static struct semaphore wrt;    // Controls access to the critical section for writers
static int reader_count = 0;    // Number of readers currently accessing the critical section
static int *data_buffer = NULL; // Data buffer for the writer to write and the reader to read

asmlinkage long sys_<syscall_name>(void)
{
    if (data_buffer == NULL) {
        // Allocate memory for the data buffer
        data_buffer = kmalloc(BUFFER_SIZE * sizeof(int), GFP_KERNEL);
        if (data_buffer == NULL) {
            printk("Failed to allocate memory for the data buffer\n");
            return -ENOMEM; // Out of memory error
        }
    }

    int i; // Variable declaration moved outside the for loop

    if (down_interruptible(&wrt))
        return -ERESTARTSYS; // Interrupted by a signal, restart syscall

    // Generate random integers and store them in the data buffer
    for (i = 0; i < BUFFER_SIZE; i++) {
        get_random_bytes(&data_buffer[i], sizeof(int));
    }

    // Perform writing
    printk("Writer: Writing data: %d, %d, %d, %d\n", data_buffer[0], data_buffer[1], data_buffer[2], data_buffer[3]);

    up(&wrt);

    if (down_interruptible(&mutex))
        return -ERESTARTSYS; // Interrupted by a signal, restart syscall

    reader_count++;
    if (reader_count == 1) {
        // First reader, acquire the write lock to block writers
        if (down_interruptible(&wrt)) {
            up(&mutex);
            return -ERESTARTSYS; // Interrupted by a signal, restart syscall
        }
    }

    up(&mutex);

    // Perform reading
    printk("Reader: Reading data: %d, %d, %d, %d\n", data_buffer[0], data_buffer[1], data_buffer[2], data_buffer[3]);

    if (down_interruptible(&mutex))
        return -ERESTARTSYS; // Interrupted by a signal, restart syscall

    reader_count--;
    if (reader_count == 0) {
        // Last reader, release the write lock to allow writers
        up(&wrt);
    }

    up(&mutex);

    return 0;
}
