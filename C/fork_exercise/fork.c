#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int total_p;
    
    printf("Enter number of processes to be created: ");
    scanf("%d",&total_p);

    if(total_p <= 1 )
    {
        for(int i = 0;i < 5;i++)
        {
            printf("PID = %d, POS = 1, RAND_NUM = %f\n",getpid(),((double)rand())/RAND_MAX);
            sleep(3);
        }
        
        return 0;
    }

    int cnt = 2;
    int pid = fork();
    
    while(cnt<=total_p)
    {
        if(pid==0)
        {
            if(cnt!=total_p)
            {
                pid = fork();
            }

            if(pid == 0)
            {
                if(cnt==total_p)
                {
                    if(cnt%2==0)
                    {
                        for(int i = 0;i < 5;i++)
                        {
                            printf("PID = %d, PPID = %d, POS = %d, RAND_NUM = %f\n",getpid(),getppid(),cnt,((double)rand())/RAND_MAX);
                            sleep(3);
                        }

                        return 0;
                    }

                    else
                    {
                        for(int i = 0;i < 5;i++)
                        {
                            printf("PID = %d, POS = %d, RAND_NUM = %f\n",getpid(),cnt,((double)rand())/RAND_MAX);
                            sleep(3);
                        }

                        return 0;
                    }
                }

                else
                {
                    cnt++;
                }

                continue;
            }

            else
            {    
                if(cnt%2==0)
                {
                    for(int i = 0;i < 5;i++)
                    {
                        printf("PID = %d, PPID = %d, POS = %d, RAND_NUM = %f\n",getpid(),getppid(),cnt,((double)rand())/RAND_MAX);
                        sleep(3);
                    }
                }

                else
                {
                        for(int i = 0; i < 5;i++ )
                        {
                            printf("PID = %d, CPID = %d, POS = %d, RAND_NUM = %f\n",getpid(),pid,cnt,((double)rand())/RAND_MAX);
                            sleep(3);
                        }
                }

                wait(NULL);
                printf("Parent process terminated, PID = %d, POS = %d\n",getpid(),cnt);

                return 0;
                
            }
        }

        else
        {
            for(int i = 0;i < 5;i++ )
            {
                printf("PID = %d, CPID = %d, POS = 1, RAND_NUM = %f\n",getpid(),pid,((double)rand())/RAND_MAX);
                sleep(3);
            }

            wait(NULL);
            printf("Parent process terminated, PID = %d, POS = 1\n",getpid());

            return 0;
        }
        
    }
    
    return 0;
}