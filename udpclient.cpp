#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
using namespace std;
int main()
{
	unsigned int length = sizeof(struct sockaddr_in);
	int sockfd,n;
	struct sockaddr_in servadd;
	struct hostent *server;
	int port = 5001;
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if (sockfd<0)
    {
    	cout<<"ERROR creating socket .... "<<endl;
    	exit(0);
    }
    cout<<"Socket created successfully   "<<endl;
    server = gethostbyname("127.0.0.1"); ///enter ip addresss .......
    if(server==0)
    {
    	cout<<"UNKNOWN SERVER  "<<endl;
    	exit(0);
    }
    servadd.sin_family = AF_INET;
    bcopy((char*)server->h_addr,(char *)&servadd.sin_addr.s_addr,server->h_length);
    servadd.sin_port = htons(port);
    char buffer [100] = "agcml" ;
    n=sendto(sockfd,buffer,99,0,(struct sockaddr *)&servadd,length);
    bzero(buffer,99);
    n=recvfrom(sockfd,buffer,99,0,(struct sockaddr *)&servadd,&length);
    write(1,buffer,n);
    cout<<endl;
    close(sockfd);
}