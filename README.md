# Reader-Writer Problem
This is an implementation of the Operating system classical synchronization problem using semaphores(with system call).
## Problem Description
The reader-writer problem is a classic synchronization problem in operating systems that involves managing concurrent access to a shared resource. The shared resource is typically a data structure, such as a file, database, or memory segment, which can be read from or written to by multiple threads or processes simultaneously.

The problem arises when there are multiple readers and writers, and the following constraints must be satisfied:
  1. Multiple readers can access the shared resource simultaneously without causing any conflicts or inconsistencies among themselves. In other words, multiple readers can read the resource concurrently without any issues.

  2. Writers, on the other hand, must have exclusive access to the shared resource. When a writer is writing to the resource, no other reader or writer should be  able to access it. This exclusive access ensures that writes do not interfere with each other or with ongoing reads.

The main challenge in the reader-writer problem is to find a synchronization mechanism that allows efficient and fair access to the shared resource while maintaining data integrity and avoiding issues like race conditions or deadlocks.

## Objectives
The objectives of the reader-writer problem can be summarized as follows:

1. Read Concurrently: Allow multiple readers to access the shared resource simultaneously. Readers do not modify the data and can safely access it concurrently without causing conflicts or inconsistencies.

2. Write Exclusively: Ensure exclusive access to the shared resource when a writer wants to modify or update it. This means that only one writer can access the resource at a time to prevent data corruption or race conditions.

3. No Reader-Writer Starvation: Avoid situations where either readers or writers are indefinitely delayed or starved from accessing the resource. Balancing the access of readers and writers is essential to maintain fairness and prevent situations where one group is constantly favored over the other.
## References

1. Gate Smasher's YouTube Video https://www.youtube.com/watch?v=Zdzp5k3eSYg&pp=ygUWcmVhZGVyIHdyaXRlciBwcm9ibGVtIA%3D%3D
2. Knowledge Gate Youtube Video https://www.youtube.com/watch?v=kn2Okc2cAaQ&pp=ygUWcmVhZGVyIHdyaXRlciBwcm9ibGVtIA%3D%3D
3. Love Babbar's Youtube Video https://www.youtube.com/watch?v=TyJ3as7haIU&pp=ygUWcmVhZGVyIHdyaXRlciBwcm9ibGVtIA%3D%3D
4. Chatgpt was used for Debugging
## Requirements
To compile and run this program, you need to have the following:

* C compiler (e.g., gcc)
* pthreads library (for thread management)
* semaphores library (for synchronization)
## Compilation
Use the following command to compile the program:

`gcc -o reader_writer reader_writer.c -lpthread`

## Execution
After compilation, execute the program using the following command:

`./reader_writer`

## Output
![image](https://github.com/MustafaHashmani/ReaderWriter-Problem/assets/63756923/aaf6e243-16ef-4404-acdd-cb5702c0cb78)


## Students
* Mustafa Hashmani (21k-3080)
* Areeb Nadeem (21k-3007)
