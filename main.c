#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <time.h>
#include "readerwriter.c"

#define SIZE 100

int main()
{
    char ptr;               // Gets the reader/writer from the file
    int counter = 0;        // Total # of readers & writers in file
    int read = 0;           // Number of readers in the file
    int write = 0;          // Number of writers in the file
    int i;

    rwlock_init(&mutex);    // Initialize semaphores
    pthread_t tid[SIZE];    // Array of threads
    int ids[SIZE];          // Array of thread IDs to pass
    
    // Open the file to be read
    FILE *file;
    file = fopen("scenarios.txt", "r");

    if (file == NULL)
    {
        printf ("Error opening file\n");
        return 1;
    }
    else if (file)
    {
        // Scan the file and create the threads
        while (fscanf(file, "%c", &ptr) != EOF)
        {
            if (ptr == 'r')  // Reader thread
            {
                ids[counter] = counter;
                pthread_create(&tid[counter], NULL, reader, &ids[counter]);
                counter++;
                read++;
            }
            else if (ptr == 'w')  // Writer thread
            {
                ids[counter] = counter;
                pthread_create(&tid[counter], NULL, writer, &ids[counter]);
                counter++;
                write++;
            }
        }
        fclose(file);  // Close the read file
    }

    // Join the threads
    for (i = 0; i < counter; i++)
    {
        pthread_join(tid[i], NULL);
    }

    // Adjust the totals for averaging
    rtotals = rtotals * 1000000 / CLOCKS_PER_SEC;
    wtotals = wtotals * 1000000 / CLOCKS_PER_SEC;

    // Print the reader/writer averages
    printf("The average Reader time was %.4f\n", (rtotals / read));
    printf("The average Writer time was %.4f\n", (wtotals / write));

    printf("\nProgram completed.\n");

    return 0;
}
