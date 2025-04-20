#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>

#define UDP_SERVER_PORT 5001
#define IP "127.0.0.1"
#define MSG_SIZE 100

void touppercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

int main()
{
    char msg[MSG_SIZE];

    int UDP_server_sock;
    UDP_server_sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in UDP_serveraddr,client_addr;
    socklen_t clientaddr_len = sizeof(client_addr);
    UDP_serveraddr.sin_family = AF_INET;
    UDP_serveraddr.sin_port = htons(UDP_SERVER_PORT);
    UDP_serveraddr.sin_addr.s_addr = inet_addr(IP);

    bind(UDP_server_sock,(struct sockaddr*) &UDP_serveraddr,sizeof(UDP_serveraddr));

    printf("UDP Server is running on IP: %s, PORT: %d.\n",IP,UDP_SERVER_PORT);

    for(;;)
    {   
        char ip_serv2_to_client[MSG_SIZE];
        int port_serv2_to_client;

        recvfrom(UDP_server_sock, (char*)msg,MSG_SIZE,0,(struct sockaddr*) &client_addr, &clientaddr_len);
        if(strcmp(msg, "exit") == 0)
        {
            printf("exiting, PID: %d\n",getpid());
            sendto(UDP_server_sock, msg, sizeof(msg), 0, (struct sockaddr*)&UDP_serveraddr, sizeof(UDP_serveraddr));
            kill(getpid(),SIGKILL);
        }

        recvfrom(UDP_server_sock, (char*)ip_serv2_to_client,MSG_SIZE,0,(struct sockaddr*) &client_addr, &clientaddr_len);
        recvfrom(UDP_server_sock, &port_serv2_to_client,MSG_SIZE,0,(struct sockaddr*) &client_addr, &clientaddr_len);

        int TCP_client_sock;
        TCP_client_sock = socket(AF_INET, SOCK_STREAM,0);
        
        struct sockaddr_in TCP_clientaddr;
        TCP_clientaddr.sin_family = AF_INET;
        TCP_clientaddr.sin_port = htons(port_serv2_to_client);
        TCP_clientaddr.sin_addr.s_addr = inet_addr(ip_serv2_to_client);

        pid_t childid;
        if((childid = fork()) == 0)
        {   
            touppercase(msg);

            printf("Received data: %s, from server1 with IP: %s, PORT: %d\n", msg ,inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));            

            connect(TCP_client_sock, (struct sockaddr*) &TCP_clientaddr, sizeof(TCP_clientaddr));
            printf("Sending data to client with IP: %s, PORT: %d\n",ip_serv2_to_client,port_serv2_to_client);
            write(TCP_client_sock, msg, sizeof(msg));
            close(TCP_client_sock);
            return 0;
        }
        int status;
        waitpid(-1,&status,WNOHANG);
    }
    
    close(UDP_server_sock);
    return 0;

}