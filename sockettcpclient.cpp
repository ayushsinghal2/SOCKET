//TCP client .....
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
	int sockfd,n;
	struct sockaddr_in servadd;
	struct hostent *server;
	/*
	struct hostent description....
	h_name       Official name of the host.
	h_aliases    A zero  terminated  array  of  alternate names for the host.
	h_addrtype   The  type  of  address  being  returned currently always AF_INET.
	h_length     The length, in bytes, of the address.
	h_addr_list  A pointer to a list of network addresses for the named host.  
	Host addresses are returned in network byte order.
    */
    int port = 5001;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd<0)
    {
    	cout<<"ERROR creating socket .... "<<endl;
    	exit(0);
    }
    cout<<"Socket created successfully   "<<endl;
    server = gethostbyname("127.0.0.1"); ///enter ip addresss .......
    servadd.sin_family = AF_INET;
    bcopy((char*)server->h_addr,(char *)&servadd.sin_addr.s_addr,server->h_length);
    servadd.sin_port = htons(port);
    //connecting to the server.....
    int connection ;
    char  buff[255];
    connection = connect(sockfd,(struct sockaddr *)&servadd,(socklen_t)sizeof(servadd));
    if(connection<0)
    {
    	cout<<"ERROr connecting  "<<endl;
    }
    cout<<"Connection successfull "<<endl;
    n = read (sockfd,buff,254);
    cout<<buff<<endl; 
    cin>>buff;
    n = write(sockfd,buff,strlen(buff));
    int number = atoi(buff);
    for (int i = 0; i<number ; ++i)
    {
    	cin>>buff;
    	n = write(sockfd,buff,strlen(buff));
    }
    int array [100];
    cout<<"Numbers are ::::     "; 
    for (int i = 0; i <= number; ++i)
    {
    	int temp;
    	n = read(sockfd,&temp,sizeof(int));
        if(i>0)
    	cout<<ntohl(temp)<<"     ";
    }
   	close(sockfd);
}