#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

// Declare semaphore and mutex variables
sem_t wrt;
pthread_mutex_t mutex;

// Declare global variables
int cnt = 1;
int numreader = 0;

// Writer function
void *writer(void *wno)
{
  // Acquire the semaphore
  sem_wait(&wrt);

  // Modify the shared variable
  cnt = cnt * 2;

  // Print the new value of the shared variable
  printf("Writer %d modified cnt to %d\n", *((int *)wno), cnt);

  // Release the semaphore
  sem_post(&wrt);
}


  // Acquire the mutex
  pthread_mutex_lock(&mutex);

  // Decrement the number of readers
  numreader--;

  // If this is the last reader, then wake up the writer
  if (numreader == 0) {
    sem_post(&wrt);
  }

  // Release the mutex
  pthread_mutex_unlock(&mutex);
}
void *reader(void *rno)
{
  // Acquire the mutex
  pthread_mutex_lock(&mutex);

  // Increment the number of readers
  numreader++;

  // If this is the first reader, then block the writer
  if (numreader == 1) {
    sem_wait(&wrt);
  }

  // Release the mutex
  pthread_mutex_unlock(&mutex);

  // Read the shared variable
  printf("Reader %d: read cnt as %d\n", *((int *)rno), cnt);

  // Acquire the mutex
  pthread_mutex_lock(&mutex);
  
  // Decrement the number of readers
  numreader--;

  // If this is the last reader, then wake up the writer
  if (numreader == 0) {
    sem_post(&wrt);
  }

  // Release the mutex
  pthread_mutex_unlock(&mutex);
}
// Main function
int main()
{
  // Create 10 reader threads and 5 writer threads
  pthread_t read[10], write[5];

  // Initialize the mutex and semaphore
  pthread_mutex_init(&mutex, NULL);
  sem_init(&wrt, 0, 1);

  // Create an array of integers to store the thread IDs
  int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // Create the reader threads
  for (int i = 0; i < 10; i++) {
    pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
  }

  // Create the writer threads
  for (int i = 0; i < 5; i++) {
    pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
  }

  // Join the reader and writer threads.
  for (int i = 0; i < 10; i++) {
    pthread_join(read[i], NULL);
  }

  for (int i = 0; i < 5; i++) {
    pthread_join(write[i], NULL);
  }

  // Destroy the mutex and semaphore
  pthread_mutex_destroy(&mutex);
  sem_destroy(&wrt);

  // Return 0
  return 0;
}
