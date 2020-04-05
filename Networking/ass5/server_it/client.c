/*				THE CLIENT PROCESS

	Please read the file server.c before you read this file. To run this,
	you must first change the IP address specified in the line:

		serv_addr.sin_addr.s_addr = inet_addr("144.16.202.221");

	to the IP-address of the machine where you are running the server.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	int sockfd ;
	struct sockaddr_in serv_addr;

	int i;
	int numbers[5];
	clock_t time;
	/* Opening a socket is exactly similar to the server process */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Unable to create socket\n");
		exit(0);
	}

	/* Recall that we specified INADDR_ANY when we specified the server
	   address in the server. Since the client can run on a different
	   machine, we must specify the IP address of the server.

	   TO RUN THIS CLIENT, YOU MUST CHANGE THE IP ADDRESS SPECIFIED
	   BELOW TO THE IP ADDRESS OF THE MACHINE WHERE YOU ARE RUNNING
	   THE SERVER.
	*/
	serv_addr.sin_family		= AF_INET;
	serv_addr.sin_addr.s_addr	= INADDR_ANY;;
	serv_addr.sin_port		= htons(6000);

	/* With the information specified in serv_addr, the connect()
	   system call establishes a connection with the server process.
	*/
	if ((connect(sockfd, (struct sockaddr *) &serv_addr,
						sizeof(serv_addr))) < 0) {
		printf("Unable to connect to server\n");
		exit(0);
	}

	/* After connection, the client can send or receive messages.
	   However, please note that recv() will block when the
	   server is not sending and vice versa. Similarly send() will
	   block when the server is not receiving and vice versa. For
	   non-blocking modes, refer to the online man pages.
	*/

	printf("Enter 5 numbers : \n");
	for (i = 0; i<5; i++)
	{
		scanf("%d", &numbers[i]);
	}

	time = clock();

	send(sockfd, &numbers, 5*sizeof(int), 0);
	recv(sockfd, &numbers, 5*sizeof(int), 0);

	time = clock() - time;

	printf("Sorted numbers as received from server: ");
	for (i = 0; i<5; i++)
	{
		printf("%d ", numbers[i]);
	}

	printf("\nTotal time elapsed : %f seconds.\n---------------------------------------------------------\n", (double)time/CLOCKS_PER_SEC);

	close(sockfd);

	return 0;
}
