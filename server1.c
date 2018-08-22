/*
 *  server.h
 *  
 *
 *  Created by Ankush Mittal on 01/03/15.
 *  Copyright 2015 IIT. All rights reserved.
 *
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h> 

int y=0;
pthread_t threads1, threads2;
int arr[10]={0};
static int i=0;
void typecast(int n, char a[])
{
	int tmp;
	int i = 0;
	while(n>0)
	{
		tmp = n%10;
		a[i++] = (char)(tmp+48);
		n = n/10; 
	}
	a[i] = ':';
	a[i+1] ='\0';
}

void *receives(void *arg)
{
	int j, n;
	char s[500],a[500];
	char b;
	int *connfd = (int *)(arg);
	arr[i++] = *connfd;
	while(1)
	{
		/*if(n=recv(connfd,s,500,0)<0)
			break;*/
		//k = i;
		read(*connfd, s, 500);
		typecast(*connfd, a);
		strcat(a,s);
		printf("server recieved form %d: %s\n",*connfd,s);
		for(j=0;j<y;j++)
		{
			if(arr[j]!=(*connfd) && arr[j]!=0)
			{
				write(arr[j], a, 500);
			}
				//send(arr[j], s,n,0);
		}
	}
	return (NULL);
}

int main(int argc, char *argv[])
{
    int listenfd = 0,connfd = 0;
    struct sockaddr_in serv_addr; 
    char s[100];
    char sendBuff[1025];
    int temp;

    time_t ticks; 
	pthread_attr_t pthread_custom_attr1, pthread_custom_attr2;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 
	
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(1998); 
	
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
	
    listen(listenfd, 10); 
	printf("HELLO");
    while(1)
    {
        arr[y++] = accept(listenfd, (struct sockaddr*)NULL, NULL); 
	printf("Connected to client :%d \n",arr[y-1]);
	pthread_attr_init(&pthread_custom_attr1);
	pthread_create(&threads1, &pthread_custom_attr1, &receives, (void *)(&arr[y-1]));
	//pthread_attr_init(&pthread_custom_attr2);
	//pthread_create(&threads2, &pthread_custom_attr2, &sends, (void *)(&connfd));
    }
	//while(--i){
		close(connfd);
        	sleep(1);
//		pthread_join(threads1,NULL);
//		pthread_join(threads2,NULL);
	//}
}
