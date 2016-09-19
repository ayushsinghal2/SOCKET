//UDP sockets programming .....
//refer to tcp program for more info about functions ......
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define MAX_BYTES 255
using namespace std;
int main(int argc , char* argv[])
{
	int port = 5001 ;
	char ipaddr[100] = "127.0.0.1";
	int sockerror; ///file descriptors....
	struct sockaddr_in serveradd , clientadd; // server and client address
	socklen_t clilen;
	sockerror = socket(AF_INET, SOCK_DGRAM, 0);////////UDP .....
	if(sockerror<0)
	{
		cout<<"Error opening socket "<<endl;
		exit(0);
	}	
	serveradd.sin_family=AF_INET;
	serveradd.sin_port = htons(port); 
	serveradd.sin_addr.s_addr = inet_addr(ipaddr);
	int bv = bind(sockerror,(struct sockaddr *) &serveradd,sizeof(serveradd));
	if(bv<0)
	{
		cout<<"Error binding IP address "<<endl;
	}
	cout<<"Binding successfull server listening on IP "<<ipaddr<<" : "<<port<<endl;
	listen(sockerror,5);
	clilen = sizeof(clientadd);
	int n;
	char buffer[100];
	/*
	recvfrom
	6 arguments ....
	1 , 2 , 3 same as tcp read 
	4th is flag IDK but set it to 0
	5th is clientadd and 6th is client address length (IPV4 and IPV6)
	*/
	n = recvfrom(sockerror,buffer,99,0,(struct sockaddr * )&clientadd,&clilen);
	write(1,buffer,n);
	for(int i = 0; i<strlen(buffer);i++)
	{
		for (int j = 0;j<strlen(buffer)-i-1 ; ++j)
		{
			if(buffer[i]>buffer[i+1])
			{
				char temp = buffer[i];
				buffer[i] = buffer[i+1];
				buffer[i+1]=temp;
			}
		}
	}
	n = sendto(sockerror,buffer,99,0,(struct sockaddr * )&clientadd,clilen);
}