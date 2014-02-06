/*
** server.c -- a stream socket server demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#define PORT "3490"  // the port users will be connecting to

#define BACKLOG 10	 // how many pending connections queue will hold

int useRand = 1;
int digits[] = {0, 0, 0, 0};

void * listen_and_accept();
void * play_game(int * new_fd);
int send_to_client(int sockfd, void * buffer, int length);
int receive_from_client(int sockfd, void * buffer, int bufsize);

void sigchld_handler()
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
    pthread_t listener;

    pthread_create(&listener, NULL, listen_and_accept, NULL);
    pthread_join(listener, NULL);
    return 0;
}

void * listen_and_accept()
{
	int sockfd;  // listen on sock_fd, new connection on new_fd
        int * new_fd;
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	struct sigaction sa;
	int yes=1;
	char s[INET6_ADDRSTRLEN];
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		//return 1;
	}

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
				sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}

		break;
	}

	if (p == NULL)  {
		fprintf(stderr, "server: failed to bind\n");
		//return 2;
	}

	freeaddrinfo(servinfo); // all done with this structure

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	sa.sa_handler = sigchld_handler; // reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}

	printf("server: waiting for connections...\n");

	while(1) {  // main accept() loop
		sin_size = sizeof their_addr;
                new_fd = (int*)malloc(sizeof(int));
		*new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (*new_fd == -1) {
			perror("accept");
			continue;
		}

		inet_ntop(their_addr.ss_family,
			get_in_addr((struct sockaddr *)&their_addr),
			s, sizeof s);
		printf("\nserver: got connection from %s\n", s);
                pthread_t game_session;

		if (!fork()) { // this is the child process
			close(sockfd); // child doesn't need the listener
                        pthread_create(&game_session, NULL, play_game,
                                       (void*) new_fd);
                        pthread_join(game_session, NULL);
			exit(0);
		}
		close(*new_fd);  // parent doesn't need this
                free(new_fd);
	}

	//return 0;
}

void * play_game(int * new_fd)
{
    int game_digits[4];
    int i;
    int sockfd = *new_fd;
    int guess;
    srand(time(NULL));
    printf("New game with digits: ");
    for (i = 0; i < 4; i++)
    {
        if (useRand == 1)
        {
            game_digits[i] = rand() % 6;
        }
        else
        {
            game_digits[i] = digits[i];
        }
        printf("%i", game_digits[i]);
    }
    printf("\n");
    send_to_client(sockfd, (void*) "Welcome to Mastermind!\n", 23);
    for (i = 0; i < 8; i++)
    {
        //send_to_client(sockfd, (void*) "Make a guess: \n", 15);
        receive_from_client(sockfd, (void*) &guess, sizeof(int));
        printf("%i %i\n",i, guess);
    }

    close(sockfd);
    //free(new_fd);
}

int send_to_client(int sockfd, void * buffer, int length)
{
    if (send(sockfd, buffer, length, 0) == -1)
    {
        perror("send");
        return -1;
    }
    return length;
}

int receive_from_client(int sockfd, void * buffer, int bufsize)
{
    int numbytes;
    if ((numbytes = recv(sockfd, buffer, bufsize - 1, 0)) == -1)
    {
        perror("recv");
        exit(1);
    }
    return numbytes;
}
