/*
 *  untitled.h
 *  
 *
 *  Created by Ankush Mittal on 01/03/15.
 *  Copyright 2015 IIT. All rights reserved.
 *
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <arpa/inet.h> 
pthread_t threads1, threads2;
int sockfd=0;
void *sends(void *arg)
{
	while(1)
	{
		char s[500];
		gets(s);
		write(sockfd, s, 500);
		printf("Client sending : %s\n",s);
	}

}

void *receives(void* arg)
{
	char s[500];
	while(1)
	{
		read(sockfd,s,500);
		printf("%s\n",s);
	}

}


int main(int argc, char *argv[])
{
    int  n = 0;
    char recvBuff[1024];int temp;
    struct sockaddr_in serv_addr; 
	char s[100];
	pthread_attr_t pthread_custom_attr1, pthread_custom_attr2;
    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    } 
	
    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 
	
    memset(&serv_addr, '0', sizeof(serv_addr)); 
	
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(1998); 
	printf("Server address used is: %s\n", argv[1]);
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 
	
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
		printf("\n Error : Connect Failed \n");
		return 1;
    } 
	printf("Connected to server :%d \n",sockfd);
	pthread_attr_init(&pthread_custom_attr1);
	pthread_create(&threads1,&pthread_custom_attr1, &sends, NULL);
	pthread_attr_init(&pthread_custom_attr2);
	pthread_create(&threads2, &pthread_custom_attr2, &receives, NULL);

	pthread_join(threads1,NULL);
	pthread_join(threads2,NULL);
    return 0;
}
