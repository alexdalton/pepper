#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sstream>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define PORT "7654" // the manager port
#define INT_PORT 8000 // initial port

#define MAXDATASIZE 100 // max number of bytes we can get at once 

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int start_udp(int node_id)
{
    int udp_fd =  -1;
    struct addrinfo hints, *servinfo, *p;
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    char port[6];
    sprintf(port,"%d", INT_PORT + node_id);
    std::cout << port << std::endl;
    if ((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return -1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((udp_fd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("listener: socket");
            continue;
        }

        if (bind(udp_fd, p->ai_addr, p->ai_addrlen) == -1) {
            close(udp_fd);
            perror("listener: bind");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "listener: failed to bind socket\n");
        return -1;
    }

    freeaddrinfo(servinfo);
    return udp_fd;
}

int main(int argc, char *argv[])
{
    int manager_fd, numbytes;  
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    fd_set master;
    fd_set read_fds;
    int fdmax;
    int sockUDP_fd = -1;

    if (argc != 2)
    {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next)
    {
	    if ((manager_fd = socket(p->ai_family, p->ai_socktype,
                                 p->ai_protocol)) == -1)
        {
            perror("client: socket");
		    continue;
	    }

        if (connect(manager_fd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(manager_fd);
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
    FD_SET(manager_fd, &master);
    fdmax = manager_fd;

    int my_id;
    int neighbors[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    
    while(1)
    {
        read_fds = master;
        if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1)
        {
            perror("select");
            exit(4);
        }

        for(int i = 0; i <= fdmax; i++)
        {
            if (FD_ISSET(i, &read_fds))
            {
                if (i == manager_fd)
                {
                    if ((numbytes = recv(manager_fd, buf, MAXDATASIZE-1, 0)) == -1)
                    {
                        perror("recv");
                        exit(1);
                    }

	                buf[numbytes] = '\0';

                    std::istringstream stream(buf);
                    std::string line;
                    while (std::getline(stream, line))
                    {
                        switch (line[0])
                        {
                            char msg_type;
                            case 'I':
                                int id;
                                sscanf(line.c_str(), "%c %i", &msg_type, &id);
                                my_id = id;
                                sockUDP_fd = start_udp(my_id);
                                std::cout << sockUDP_fd << std::endl;
                                FD_SET(sockUDP_fd, &read_fds);
                                if (sockUDP_fd > fdmax)
                                {
                                    fdmax = sockUDP_fd;
                                }
                                break;
                            case 'N':
                                int neighbor;
                                int cost;
                                sscanf(line.c_str(), "%c %i %i", &msg_type, &neighbor, &cost);
                                neighbors[neighbor - 1] = cost;
                                break;
                            case 'P':
                                break;
                            case 'M':
                                break;
                            case 'T':
                                break;
                        }
                    }
                    std::cout << "ID: " << my_id << std::endl;
                    for(int i = 0; i < 16; i++)
                    {
                        if (neighbors[i] != -1)
                            std::cout << "Neighbor: " << i + 1 << " " << "Cost: " << neighbors[i] << std::endl;
                    }
	            }
                if (i == sockUDP_fd)
                {
                    struct sockaddr_storage their_addr;
                    socklen_t addr_len = sizeof(their_addr);
                    if ((numbytes = recvfrom(sockUDP_fd, buf, MAXDATASIZE-1, 0,
                        (struct sockaddr *) &their_addr, &addr_len)) == -1)
                    {
                        perror("recvfrom");
                        exit(1);
                    }
                    buf[numbytes] = '\0';
                    std::cout << buf << std::endl;
                }
            }
        }
    }
	return 0;
}
