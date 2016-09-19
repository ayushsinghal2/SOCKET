/*   Refer to the link below for more info...
http://www.linuxhowtos.org/C_C++/socket.htm */
//socket programming tcp server ...
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
	int sockerror , newsockerror; ///file descriptors....
	struct sockaddr_in serveradd , clientadd; // server and client address
	socklen_t clilen;
	/*create socket connection...
	3 parameter ... 
	1. address domain ... AF_UNIX (UNIX)  or  AF_INET (LINUX)...
	2. SOCK_STREAM  TCP .....   SOCK_DGRAM for UDP
	3. 0 os for protocol ...... still not sure if changing it to 1 would force TCP....
	if return is -1 it indicates error in opening socket*/
	sockerror = socket(AF_INET, SOCK_STREAM, 0);
	if(sockerror<0)
	{
		cout<<"Error opening socket "<<endl;
		exit(0);
	}	
	serveradd.sin_family=AF_INET; // should be same as the socket call ...
	//assigning the port number .... read network and host byte order for usage of htons....
	serveradd.sin_port = htons(port); 
	//assigning ip address
	serveradd.sin_addr.s_addr = inet_addr(ipaddr);
	/* binding the ip adderess to the server ...
	takes 3 argument 
	1. file descriptor 
	2. sockaddr (socket address) type variable since we r passing sock_addr_in we have to typecast..
	3. size of server address
	returns 0 on success and -1 on failure...*/
	int bv = bind(sockerror,(struct sockaddr *) &serveradd,sizeof(serveradd));
	if(bv<0)
	{
		cout<<"Error binding IP address "<<endl;
	}
	/*
	listen for socket connection 
	takes 2 parameter 
	1. filedescriptor
	2. Number of backlog connection ie connection waiting in the queue 
	most os will have it 5 so it is a constant .. (read about it more .........)
	dont use it for UDP .... only for SOCK_STREAM packets...
	*/
	cout<<"Binding successfull server listening on IP "<<ipaddr<<" : "<<port<<endl;
	listen(sockerror,5);
	/*
	if you want to create multiple connection use a while loop here ..
	and have accept as the first statement ....
	*/
	/*accept function
	takes 3 argument 
	1. file descriptor of server..
	2. client address variable (client ip address would be stored in this variable...)
	3. size of client address ..... 
	returns 0 on success -1 on failure....
	*/
	clilen = sizeof(clientadd);
	newsockerror = accept(sockerror,(struct sockaddr*) &clientadd,&clilen);
	if(newsockerror < 1)
	{
		cout<<"Error on ACCEPT "<<endl;
	}
	char buffer[256];//buffer variable for reading and writing ....
	char nu [2];
	int n =0 ; ///number of bytes read...
	n = write(newsockerror,"Server : Enter the number of Integers ",MAX_BYTES);
	n = read (newsockerror,nu,MAX_BYTES);
	if(n<0)
	{
		cout<<"ERROR reading from socket ..... "<<endl;
	}
	int array[55];
	for (int i = 0; i < atoi(nu); ++i)
	{
		char nop [15];
		n = read(newsockerror,nop,254);
		array[i] = atoi(nop);
		cout<<array[i]<<endl;
	}
	for (int i = 0; i < atoi(nu)-1; ++i)
	{
		for (int j = 0; j < atoi(nu)-i-1; ++j)
		{
			if(array[j]<array[j+1])
			{
				int temp = array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
			}
		}
	}
	for (int i = 0; i < atoi(nu); ++i)
	{
		int temp = htonl(array[i]);
		n = write (newsockerror,&temp,sizeof(int));
	}
	close(sockerror);
	close(newsockerror);
	return 0 ;
}