/*
** client.c -- a mastermind client
** uses the stream socket client demo as base
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define MAXDATASIZE 100 // max number of bytes a message can be

// Send to server function definition, sends data to server
int send_to_server(int sockfd, void * buffer, int length);

// Receive from server function definition, receives from server
int receive_from_server(int sockfd, void * buffer, int bufsize);

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    int sockfd;  
    char buf[MAXDATASIZE];  // Receive buffer with size 100
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    int i;
    char guess[80];      // Input buffer from user

    // Check if enough arguments are given
    if (argc != 3)
    {
        fprintf(stderr,"usage: client hostname port\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1)
        {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
              s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    // Receive and display welcome message
    buf[receive_from_server(sockfd, (void*) buf, sizeof(buf))] = '\0';
    printf("%s\n",buf);

    // Loop through process of 8 guesses
    // For each guess 1 indication message is received
    // 1 guess is sent, and 1 guess response is received
    for (i = 0; i < 8; i++)
    {
        // Print indication from server to send a guess
	buf[receive_from_server(sockfd, (void*) buf, sizeof(buf))] = '\0';
	printf("%s",buf);

        // Read up to 1kB from stdin, assume user doesn't enter in more
        // If user does the overflow will count as a guess
        fgets(guess, sizeof(guess), stdin);
        guess[5] = '\0';
        send_to_server(sockfd, (void*) guess, 5);

        // Get the response from the server
	buf[receive_from_server(sockfd, (void*) buf, sizeof(buf))] = '\0';
	printf("%s",buf);

        // Check for win
        if (strcmp(buf, "You Win\n") == 0)
        {
            close(sockfd);
            return 0;
        }

    }

    close(sockfd);
    return 0;
}

/*
* Sends a message to the server
* @param sockfd the socket file descriptor
* @param buffer the message to send
* @param length length of message
* @return number of bytes sent, -1 if error
*/
int send_to_server(int sockfd, void * buffer, int length)
{
    if (send(sockfd, buffer, length, 0) == -1) 
    {   
        perror("send");
        return -1; 
    }   
    return length;
}

/*
* Receives a message from the server
* @param sockfd the socket file descriptor
* @param buffer holds received message
* @param bufsize the size of passed in buffer
* @return number of bytes received
*/
int receive_from_server(int sockfd, void * buffer, int bufsize)
{
    int numbytes;
    if ((numbytes = read(sockfd, buffer, bufsize)) < 0)
    {   
        perror("recv");
        exit(0);
    }   
    return numbytes;
}
