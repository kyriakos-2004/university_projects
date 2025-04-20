#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_CHILDREN 1000000

int cpids[MAX_CHILDREN];
float r;

void sigcont_handler(int sig){}

void sigcont_child_handler(int sig)
{
    srand(time(NULL));
    r = (float) rand() / RAND_MAX;
}

void sigint_parent_handler(int sig)
{   
    int i=0;
    while(cpids[i]!=-1)
    {
        printf("Child with process id %d is terminating.\n",cpids[i]);
        kill(cpids[i],SIGKILL);
        i++;
    }
    printf("Parent process is terminating.");
    exit(0);
}

void sigint_child_handler(int sig)
{
    pause();
}

int main()
{   
    int num;
    pid_t cpid;
    int status;

    printf("Enter number of children to create: ");
    scanf("%d",&num);

    if(num==0)
    {
        printf("Parent process is terminating.");
        return 0;
    }

    if(num!=MAX_CHILDREN)
    {
        cpids[num] = -1;
    }

    signal(SIGCONT,sigcont_handler);
    
    for(int i =0;i<num;i++)
    {
        cpid = fork();
        if(cpid==0)
        {
            pause();
            signal(SIGCONT,sigcont_child_handler);
            signal(SIGINT,sigint_child_handler);

            srand(time(NULL));
            r = (float) rand() / RAND_MAX;

            while(1)
            {
                printf("Child %d is running %f\n",getpid(),r);
            }    
        }

        else
        {
            signal(SIGINT,sigint_parent_handler);
            cpids[i] = cpid;
        }
    }

    printf("Parent process created %d children with PIDs: ",num);
    fflush(stdout);
    for(int i =0;i<num;i++)
    {
        if(i == num-1)
        {
            printf("%d.\n",cpids[i]);
            fflush(stdout);
        }
        else
        {
            printf("%d, ",cpids[i]);
            fflush(stdout);
        }
    }
    
    while(1)
    {
        for(int i =0;i<num;i++)
        {
            kill(cpids[i],SIGCONT);
            sleep(2);
            kill(cpids[i],SIGSTOP);
        }
    }

    return 0;
}