/*
** server.c -- a mastermind server
** uses the stream socket server demo as base
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
#include <string.h>
#include <time.h>

#define BACKLOG 10	 // how many pending connections queue will hold

// Play game function definition, main game function
void play_game(int new_fd, int useRand, int * digits);

// Send to client function definition, sends data to client
int send_to_client(int sockfd, void * buffer, int length);

// Receive from client function definition, receives from client
int receive_from_client(int sockfd, void * buffer, int bufsize);

void sigchld_handler()
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

// Get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char * argv[])
{
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;
    int useRand = 0;
    int digits[4]; // Variable to hold user defined code
    char in_str[80]; // Reads input from the user 

    // Check if enough arguments are given
    if (argc != 2)
    {
        fprintf(stderr, "usage: server port\n");
        exit(1);
    }

    // Get random or digits from stdin
    printf("Enter 'random' or 4 digits to be used in Mastermind\n");
    fgets(in_str, sizeof(in_str), stdin);
    // First four characters == "rand" use random
    if (in_str[0] == 'r' && in_str[1] == 'a' && in_str[2] == 'n' &&
        in_str[3] == 'd')
    {
      printf("Using random digits for all games\n");
      useRand = 1;      
    }
    else
    {
      // Use a number based off first 4 characters of input
      // If numbers everythign works fine otherwise, characters
      // converted to a value between 0-5
      digits[0] = (in_str[0] - '0') % 6;
      digits[1] = (in_str[1] - '0') % 6;
      digits[2] = (in_str[2] - '0') % 6;
      digits[3] = (in_str[3] - '0') % 6;
      printf("Using %i%i%i%i for all games\n", digits[0], digits[1],
             digits[2], digits[3]);
    }
    

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, argv[1], &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(int)) == -1)
        {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    // main accept() loop
    while(1)
    { 
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1)
        {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *)&their_addr),
                  s, sizeof s);
        printf("\nserver: got connection from %s\n", s);
        if (!fork())
        { // this is the child process
            close(sockfd);
            play_game(new_fd, useRand, digits);
            exit(0);
        }
        close(new_fd);  // parent doesn't need this
    }

    return 0;
}

/*
* Main game function for mastermind
* Each client runs this function in their process
* @param new_fd file descriptor for socket
* @param useRand bool to use random code or not
* @param digits array of user defined digits
*/
void play_game(int new_fd, int useRand, int * digits)
{
    int game_digits[4]; // code for this game
    char guess[5];      // receive buffer for client guesses
    int guess_digits[4]; // guessed digits from client
    int white, black, i, j, k; // white and black count color/peg matches
    int flag[4];        // marks whether a peg has already been counted
    char out_str[30];   // output string to send to client
    srand(time(NULL));
    // Generate code for game depending on whether rand or not
    printf("New game with digits: ");
    for (i = 0; i < 4; i++)
    {
        if (useRand == 1)
            game_digits[i] = rand() % 6;
        else
            game_digits[i] = digits[i];
        printf("%i", game_digits[i]);
    }
    printf("\n");

    // Send welcome message
    send_to_client(new_fd, (void*) "Welcome to Mastermind!\n", 23);
    // Loop 8 times for 8 guesses of the game
    for (i = 0; i < 8; i++)
    {
        white = 0; 
        black = 0;
        flag[0] = 0; flag[1] = 0; flag[2] = 0; flag[3] = 0;
        sprintf(out_str, "Make guess %i/8: \n", i + 1);
        // Send to client ready to receive guess
        send_to_client(new_fd, (void*) out_str, sizeof(out_str));
        // Receive from client their guess
        receive_from_client(new_fd, (void*) guess, sizeof(guess));
        // Convert guess to integers between 0 - 5
        guess_digits[0] = (guess[0] - '0') % 6;
        guess_digits[1] = (guess[1] - '0') % 6;
        guess_digits[2] = (guess[2] - '0') % 6;
        guess_digits[3] = (guess[3] - '0') % 6;
        printf("Guess #%i: %i%i%i%i\n", i + 1, guess_digits[0], guess_digits[1],
               guess_digits[2], guess_digits[3]);
        // Count number of color matches and matching pegs
        for (j = 0; j < 4; j++)
        {
            if (guess_digits[j] == game_digits[j])
            {
                flag[j] = 1;
                black++;
            }
        }
        for (j = 0; j < 4; j++)
        {
            if(guess_digits[j] != game_digits[j])
            {
                for(k = 0; k < 4; k++)
                {
                    if((k != j) && (guess_digits[j] == game_digits[k]) && !flag[k])
                    {
                        white++;
                        flag[k] = 1;
                        break;
                    }
                }
            }
        }
        // Send win
        if (black == 4)
        {
            send_to_client(new_fd, (void*) "You Win\n", 8);
            return;
        }
        // Send lose
        else if (i == 7)
        {
            send_to_client(new_fd, (void*) "You Lose\n", 9);
            return;
        }
        // Send information
        else
        {
            char send_str[40];
            sprintf(send_str, "%i correct color+slot, %i correct colors\n",
                    black, white);
            send_to_client(new_fd, (void*) send_str, sizeof(send_str));
        }
    }

}

/*
* Sends a message to the client
* @param sockfd the socket file descriptor
* @param buffer the message to send
* @param length length of message
* @return number of bytes sent, -1 if error
*/
int send_to_client(int sockfd, void * buffer, int length)
{
    if (send(sockfd, buffer, length, 0) == -1)
    {
        perror("send");
        return -1;
    }
    return length;
}

/*
* Receives a message from the client
* @param sockfd the socket file descriptor
* @param buffer holds received message
* @param bufsize the size of passed in buffer
* @return number of bytes received
*/
int receive_from_client(int sockfd, void * buffer, int bufsize)
{
    int numbytes;
    if ((numbytes = recv(sockfd, buffer, bufsize, 0)) < 0)
    {
        perror("recv");
        exit(0);
    }
    return numbytes;
}
