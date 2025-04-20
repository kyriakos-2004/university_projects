#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 1000000

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

pthread_cond_t cond_for_main = PTHREAD_COND_INITIALIZER;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

pthread_t threads[MAX_THREADS];


int done = 0;
int n = 0;
int thread_term=0;
int running = 1;
int counter = 0;

pthread_t thread_to_start = -1;

void sigint_main_handler(int sig)
{      
    running = 0;
    pthread_cond_signal(&cond_for_main);

}

void* thread_function(void* arg) 
{
    pthread_t id = pthread_self();
    for(;;)    
    {
        if(running)
        {
            pthread_mutex_lock(&mutex);
            if(!running)
            {
                pthread_mutex_unlock(&mutex);
                continue;
            }
            while(thread_to_start!= id)
            {
                pthread_cond_wait(&cond,&mutex);
                if(!running)
                {
                    pthread_mutex_unlock(&mutex);
                    break;
                }

            }
            if(!running)
            {
                pthread_mutex_unlock(&mutex);
                continue;
            }

            counter++;
            sleep(1);
            if(running)
            {
                printf("Thread %lu is running %d\n",id,counter);
                fflush(stdout);
            }

            done = 1;
            pthread_cond_signal(&cond_for_main);

            pthread_cond_wait(&cond_for_main,&mutex);
            if(!running)
            {
                pthread_mutex_unlock(&mutex);
                continue;
            }
            pthread_mutex_unlock(&mutex);
        }
        else if(!running)
        {
            if(threads[thread_term]==id)
            {
                printf("Thread %lu is terminating\n",id);
                thread_term++;
                if(thread_term-1==n-1)
                {
                    done = 1;
                    pthread_cond_broadcast(&cond_for_main);
                    pthread_cond_broadcast(&cond);
                }

                return NULL;
            }
            
            
        }
      
    }
    
    return NULL;
}

int main() 
{
    signal(SIGINT,sigint_main_handler);

    printf("Enter number of threads to create: ");
    scanf("%d",&n);
    if(n==0)
    {
        printf("Main process is terminating\n");
        return 0;
    }
    for(int i =0;i<n;i++)
    {
        pthread_create(&threads[i],NULL,thread_function,NULL);
    }
    
    printf("Main process created %d threads with IDs: ",n);
    fflush(stdout);
    for(int i =0;i<n;i++)
    {
        if(i==n-1)
        {
            printf("%lu.\n",threads[i]);    
            fflush(stdout);
        }
        else
        {
            printf("%lu, ",threads[i]);
            fflush(stdout);
        }
    }

    
    for(;;) 
    {
        for (int i = 0; i < n; i++) 
        { 
            pthread_mutex_lock(&mutex2);
            if(thread_term-1==n-1)
            {
                printf("Main process is terminating\n");
                return 0;
            }
            thread_to_start = threads[i];
            
            pthread_cond_signal(&cond_for_main);
            pthread_cond_broadcast(&cond);
            while(!done)
            {
                pthread_cond_wait(&cond_for_main,&mutex2);
            }
            done = 0;
            pthread_mutex_unlock(&mutex2);

        }
    }

    return 0;
}
