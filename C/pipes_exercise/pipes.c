#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

#define str_size 100

int comparestr(char s1[],char s2[])
{
    int lens1=0;
    int lens2=0;
    for (int i = 0; s1[i] != '\0'; i++) 
    {
        lens1++;    
    }
    for (int i = 0; s2[i] != '\0'; i++) 
    {
        lens2++;    
    }

    if(lens1==lens2)
    {
        for (int i = 0; s1[i] != '\0'; i++) 
        {
            if(s1[i]!=s2[i])
            {
                return 0;
            }    
        }   
    }
    else
    {
        return 0;
    }

    return 1;
}

void to_uppercase(char str[]) {
    
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper(str[i]);
    }
}

void rev(char str[]) {
    int length = 0;
    
    while (str[length] != '\0')
    {
        length++;
    }

    int start = 0, end = length - 1;
    while (start < end) 
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}


int main()
{
    pid_t pid;

    int c1_to_c2[2],c2_to_c3[2],control[2],c3_to_parent[2],c3_to_c1[2];
    int control1[2];

    pipe(c1_to_c2);
    pipe(c2_to_c3);
    pipe(control);
    pipe(control1);
    pipe(c3_to_parent);
    pipe(c3_to_c1);
    pid = fork();

    if(pid==0)//child 1
    {
        close(c1_to_c2[0]);
        close(c2_to_c3[1]);
        close(c2_to_c3[0]);
        close(control[1]);
        close(c3_to_parent[0]);
        close(c3_to_parent[1]);
        close(c3_to_c1[1]);
        close(control1[1]);
        
        int cntrl;
        read(control[0],&cntrl,sizeof(cntrl));
        while (1)
        {
            
            char input[str_size];
            printf("Please enter a string: ");
            scanf(" %[^\n]s",input);
            if(comparestr(input,"exit"))
            {
                printf("Process with PID %d exiting\n", getpid());
                write(c1_to_c2[1],input,str_size);
                return 0;
            }
            printf("Process with PID %d: %s\n",getpid(),input);
            write(c1_to_c2[1],input,str_size);
            read(c3_to_c1[0],&cntrl,sizeof(cntrl));
            read(control1[0],&cntrl,sizeof(cntrl));

        }
    }
    
    else//parent
    {
        int child1=pid;
        pid = fork();

        if(pid == 0)//child 2
        {
            close(c1_to_c2[1]);
            close(c2_to_c3[0]);
            close(control[1]);
            close(c3_to_parent[0]);
            close(c3_to_parent[1]);
            close(c3_to_c1[1]);
            close(c3_to_c1[0]);
            close(control1[1]);
            close(control1[0]);
            
            while(1)
            {
                char input[str_size];
                int cntrl;
                read(c1_to_c2[0],&input,str_size);
                if(comparestr(input,"exit"))
                {
                    printf("Process with PID %d exiting\n", getpid());
                    write(c2_to_c3[1],input,str_size);
                    return 0;
                }
                rev(input);
                printf("Process with PID %d: %s\n",getpid(),input);
                write(c2_to_c3[1],&input,str_size);
            }

            
        }
        else//parent
        {
            int child2=pid;
            pid = fork();
            
            if(pid == 0)//child 3
            {
                close(c1_to_c2[0]);
                close(c1_to_c2[1]);
                close(c2_to_c3[1]);
                close(c3_to_c1[0]);
                close(control[1]);
                close(control[0]);
                close(c3_to_parent[0]);
                close(control1[0]);
                while(1)
                {
                    int cntrl;
                    char input[str_size];
                    read(c2_to_c3[0],&input,str_size);
                    if(comparestr(input,"exit"))
                    {
                        printf("Process with PID %d exiting\n", getpid());
                        write(c3_to_parent[1],input,str_size);
                        return 0;
                    }
                    to_uppercase(input);
                    printf("Process with PID %d: %s\n\n",getpid(),input);
                    write(c3_to_c1[1],&cntrl,sizeof(cntrl));
                    write(control1[1],&cntrl,sizeof(cntrl));
                }


            }
            else//parent
            {
                close(c1_to_c2[0]);
                close(c1_to_c2[1]);
                close(c2_to_c3[1]);
                close(c2_to_c3[0]);
                close(c3_to_c1[0]);
                close(c3_to_c1[0]);
                close(control[0]);
                close(c3_to_parent[1]);
                close(control1[0]);
                close(control1[1]);

                int cntrl;
                char input[str_size];
                int child3=pid;
                printf("Parent process has PID = %d. The PIDs of the children are %d, %d, %d.\n",getpid(),child1,child2,child3);
                write(control[1],&cntrl,sizeof(cntrl));
                read(c3_to_parent[0],input,str_size);
                
                if(comparestr(input,"exit"))
                {
                    printf("Parent process with PID %d exiting\n", getpid());
                }
            
            }
        }
        
    }

    return 0;
}