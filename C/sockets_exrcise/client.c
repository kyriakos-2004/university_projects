#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define PORT 5000
#define IP "127.0.0.1"
#define MSG_SIZE 100

int main()
{
    int TCP_server_sock,TCP_server2_to_client_sock;
    
    TCP_server_sock = socket(AF_INET, SOCK_STREAM,0);
    TCP_server2_to_client_sock = socket(AF_INET, SOCK_STREAM,0);

    struct sockaddr_in TCP_serveraddr;
    TCP_serveraddr.sin_family = AF_INET;
    TCP_serveraddr.sin_port = htons(PORT);
    TCP_serveraddr.sin_addr.s_addr = inet_addr(IP);

    struct sockaddr_in TCP_server2_to_client_addr;
    TCP_server2_to_client_addr.sin_family = AF_INET;
    TCP_server2_to_client_addr.sin_port = 0;
    TCP_server2_to_client_addr.sin_addr.s_addr = inet_addr(IP);

    bind(TCP_server2_to_client_sock, (const struct sockaddr*)&TCP_server2_to_client_addr, sizeof(TCP_server2_to_client_addr));
    listen(TCP_server2_to_client_sock,50);

    socklen_t len = sizeof(TCP_server2_to_client_addr);
    getsockname(TCP_server2_to_client_sock, (struct sockaddr*)&TCP_server2_to_client_addr, &len);

    connect(TCP_server_sock, (struct sockaddr*) &TCP_serveraddr, sizeof(TCP_serveraddr));
    printf("Connected to server1, with IP: %s, PORT: %d\n",IP,PORT);

    for(;;)
    {
        char msg[MSG_SIZE],ip[MSG_SIZE],buffer[MSG_SIZE];
        int port = ntohs(TCP_server2_to_client_addr.sin_port);
        
        printf("Enter string or enter 'exit' to exit the program: ");
        scanf(" %[^\n]s", msg);

        if(strcmp(msg, "exit") == 0)
        {
            printf("exiting, PID: %d\n",getpid());
            write(TCP_server_sock, msg, sizeof(msg));
            return 0;
        }

        printf("String entered: %s\n",msg);
        
        printf("Sending data to server1 with IP: %s, PORT: %d\n",IP,PORT);
        write(TCP_server_sock, msg, sizeof(msg));
        
        strcpy(ip, inet_ntoa(TCP_server2_to_client_addr.sin_addr)); 
        write(TCP_server_sock, ip, sizeof(ip));
        
        write(TCP_server_sock,&port, sizeof(port));
        
        struct sockaddr_in serv2_to_clientaddr;
        socklen_t serv2_to_clientaddr_len = sizeof(serv2_to_clientaddr);
        int serv2_to_client_sock = accept(TCP_server2_to_client_sock,(struct sockaddr*) &serv2_to_clientaddr, &serv2_to_clientaddr_len);
        
        read(serv2_to_client_sock, buffer, sizeof(buffer));
        printf("Received data: %s, from server2 with IP: %s, PORT: %d\n", buffer ,inet_ntoa(serv2_to_clientaddr.sin_addr),ntohs(serv2_to_clientaddr.sin_port));
    }

    close(TCP_server_sock);
    close(TCP_server2_to_client_sock);

    return 0;
}