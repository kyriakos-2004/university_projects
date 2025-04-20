#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <stdio.h>
#include <string.h>
#include <signal.h>

#define TCP_SERVER_PORT 5000
#define UDP_SERVER_PORT 5001
#define IP "127.0.0.1"
#define MSG_SIZE 100

void rvrs(char *str) {
    int left = 0, right = strlen(str) - 1;
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}


int main()
{
    char msg[MSG_SIZE];

    int TCP_server_sock, UDP_server_sock;

    TCP_server_sock = socket(AF_INET, SOCK_STREAM, 0);
    UDP_server_sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in TCP_serveraddr,UDP_serveraddr;
    TCP_serveraddr.sin_family = AF_INET;
    TCP_serveraddr.sin_port = htons(TCP_SERVER_PORT);
    TCP_serveraddr.sin_addr.s_addr = inet_addr(IP);

    UDP_serveraddr.sin_family = AF_INET;
    UDP_serveraddr.sin_port = htons(UDP_SERVER_PORT);
    UDP_serveraddr.sin_addr.s_addr = inet_addr(IP);

    bind(TCP_server_sock,(struct sockaddr*) &TCP_serveraddr,sizeof(TCP_serveraddr));
    listen(TCP_server_sock,50);

    printf("TCP Server is running on IP: %s, PORT: %d.\n",IP,TCP_SERVER_PORT);

    for(;;)
    {   
        struct sockaddr_in clientaddr;
        socklen_t clientaddr_len = sizeof(clientaddr);
        int client_sock = accept(TCP_server_sock,(struct sockaddr*) &clientaddr, &clientaddr_len);
        printf("Connection established, with client IP: %s, PORT: %d\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));

        pid_t childid;
        if((childid = fork()) == 0)
        {   
            for(;;)
            {
                if(read(client_sock, msg, sizeof(msg)) == 0)
                {
                    printf("client with IP: %s, PORT: %d closed connection\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
                    close(client_sock);
                    return 0;
                }

                if(strcmp(msg, "exit") == 0)
                {
                    printf("exiting, PID: %d\n",getppid());
                    sendto(UDP_server_sock, msg, sizeof(msg), 0, (struct sockaddr*)&UDP_serveraddr, sizeof(UDP_serveraddr));
                    kill(getppid(),SIGKILL);
                    return 0;
                }

                char ip_serv2_to_client[MSG_SIZE];
                int port_serv2_to_client;
                read(client_sock,&ip_serv2_to_client,sizeof(ip_serv2_to_client));
                read(client_sock,&port_serv2_to_client,sizeof(port_serv2_to_client));
                rvrs(msg);
                printf("Received data: %s, from client with IP: %s, PORT: %d\n", msg ,inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));

                printf("Sending data to server2 with IP: %s, PORT: %d\n", IP, UDP_SERVER_PORT);
                sendto(UDP_server_sock, msg, sizeof(msg), 0, (struct sockaddr*)&UDP_serveraddr, sizeof(UDP_serveraddr));
                sendto(UDP_server_sock, ip_serv2_to_client, sizeof(ip_serv2_to_client), 0, (struct sockaddr*)&UDP_serveraddr, sizeof(UDP_serveraddr));
                sendto(UDP_server_sock, &port_serv2_to_client, sizeof(port_serv2_to_client), 0, (struct sockaddr*)&UDP_serveraddr, sizeof(UDP_serveraddr));
            }
        }
    }

    close(TCP_server_sock);
    close(UDP_server_sock);

    return 0;
}