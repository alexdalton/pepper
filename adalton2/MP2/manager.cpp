#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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

#define PORT "7654"  // manager port
#define BACKLOG 16   // # pending connections (max num of nodes)


bool node_sort(int i, int j) {return (i < j);}

class Link {
    public:
        int node1, node2, cost;
        Link(int a, int b, int l_cost) : node1(a), node2(b), cost(l_cost) {}
};

class Message {
    public:
        int from, to;
        std::string message;
        Message(int a, int b, std::string msg) : from(a), to(b), message(msg) {}
};

class Topology {
    public:
        std::vector<Link> links;
        int num_links;
        int num_nodes;
        std::vector<int> nodes;
        Topology() : num_links(0), num_nodes(0) {}

        void add_link(int node1, int node2, int cost)
        {
            int node1_isNew = 1;
            int node2_isNew = 1;
            for (std::vector<int>::iterator it = nodes.begin(); it != nodes.end(); it++)
            {
                if (node1 == *it)
                {
                    node1_isNew = 0;
                }
                if (node2 == *it)
                {
                    node2_isNew = 0;
                }
            }
            if (node1_isNew)
            {
                nodes.push_back(node1);
                num_nodes++;
            }
            if (node2_isNew)
            {
                nodes.push_back(node2);
                num_nodes++;
            }
            Link new_link(node1, node2, cost);
            for (std::vector<Link>::iterator it = links.begin(); it != links.end(); it++)
            {
                // link exists erase before adding link
                if ((node1 == it->node1 and node2 == it->node2) or
                    (node2 == it->node1 and node1 == it->node1))
                {
                    links.erase(it);
                    num_links--;
                }
            }
            links.push_back(new_link); 
            num_links++;
        }

        void sort_nodes()
        {
            std::sort(nodes.begin(), nodes.end(), node_sort); 
        }

        std::vector<Link> get_nodes_links(int node)
        {
            std::vector<Link> node_links;
            for (std::vector<Link>::iterator it = links.begin(); it != links.end(); it++)
            {
                if (node == it->node1 or node == it->node2)
                {
                    node_links.push_back(*it);
                } 
            }
            return node_links;
        }

        void print_nodes_links(int node)
        {
            std::vector<Link> nodes_links = get_nodes_links(node);
            for (std::vector<Link>::iterator it = nodes_links.begin(); it != nodes_links.end(); it++)
            {
                std::cout << it->node1 << it->node2 << it->cost << std::endl;
            }
        }

        void print_topology()
        {
            std::cout << "Number nodes: " << num_nodes << std::endl;
            std::cout << "Number links: " << num_links << std::endl;
            for (std::vector<Link>::iterator it = links.begin(); it != links.end(); it++)
            {
                std::cout << it->node1 << it->node2 << it->cost << std::endl;
            }
            for (std::vector<int>::iterator it = nodes.begin(); it != nodes.end(); it++)
            {
                std::cout << *it << std::endl;
            }

        }
};

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void read_topology(char * filename, Topology &topology)
{
    std::ifstream top_file;
    std::string link_str;
    top_file.open(filename);
    if (top_file.is_open())
    {
        int a, b, cost;
        while (getline(top_file, link_str))
        {
            sscanf(link_str.c_str(), "%d %d %d", &a, &b, &cost);
            topology.add_link(a, b, cost);
        }
    }
    else
    {
        std::cout << "Invalid topology file!" << std::endl;
        exit(1);
    }
}

void read_messages(char * filename, std::vector<Message> &messages)
{
    std::ifstream msg_file;
    std::string msg_str;
    msg_file.open(filename);
    if (msg_file.is_open())
    {
        int a, b;
        char msg_in[300];
        while (getline(msg_file, msg_str))
        {
            sscanf(msg_str.c_str(),"%d %d %[^\n]", &a, &b, msg_in);
            std::string message(msg_in);
            Message new_message(a, b, message);
            messages.push_back(new_message); 
        }
    }
    else
    {
        std::cout << "Invalid message file!" << std::endl;
        exit(1);
    }
}

void send_to_node(int node_fd, char * message, int length)
{
    if (send(node_fd, message, length, 0) == -1)
    {
        perror("send");
        close(node_fd);
    }
}

void send_neighbors(int dest_fd, int node_id, Topology top)
{
    for (std::vector<Link>::iterator it = top.links.begin(); it != top.links.end(); it++)
    {
        int neighbor_id;
        if (node_id == it->node1 or node_id == it->node2)
        {
            if (node_id == it->node1)
            {
                neighbor_id = it->node2;
            }
            else
            {
                neighbor_id = it->node1;
            }
            char message[100];
            int length = sprintf(message, "N %i %i\n", neighbor_id, it->cost);
            send_to_node(dest_fd, message, length);
        }
    }
}

int send_udp()
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    if ((rv = getaddrinfo("127.0.0.1", "8001", &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and make a socket
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("talker: socket");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "talker: failed to bind socket\n");
        return 2;
    }

    if ((numbytes = sendto(sockfd, "test", 4, 0,
             p->ai_addr, p->ai_addrlen)) == -1) {
        perror("talker: sendto");
        exit(1);
    }

    freeaddrinfo(servinfo);

    printf("talker: sent %d bytes to %s\n", numbytes, "127.0.0.1");
    close(sockfd);

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "usage: ./manager topologyfile messagefile\n");
        exit(1);
    }

    Topology topology;
    std::vector<Message> messages;
    std::vector<std::string> ip_store(16);
    int node_fds[16];

    read_topology(argv[1], topology);
    read_messages(argv[2], messages);

    topology.sort_nodes();
    topology.print_topology();
    /*
    for (std::vector<Message>::iterator it = messages.begin(); it != messages.end(); it++)
    {
        std::cout << it->from << it->to << it->message << std::endl;
    }*/

    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    int yes = 1;
    int rv;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0)
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

    std::cout << "server: waiting for connections...\n";

    char s[INET6_ADDRSTRLEN];
    sin_size = sizeof their_addr;
    int connected_nodes = 0;
    while (connected_nodes < topology.num_nodes)
    {
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1)
        {
            perror("accept");
            continue;
        }
        node_fds[connected_nodes] = new_fd;

        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *)&their_addr),
                  s, sizeof s);
        ip_store[connected_nodes] = s;
        printf("server: got connection from %s\n", s);

        char send_message[100];
        int msg_size = sprintf(send_message, "I %i\n", topology.nodes[connected_nodes]);
        send_to_node(new_fd, send_message, msg_size);
        send_neighbors(new_fd, topology.nodes[connected_nodes], topology);
        connected_nodes++;
        
    }
    send_udp();

    while(1);
    for(int i = 0; i < topology.num_nodes; i++)
    {
        close(node_fds[i]);
    }


    return 0;
}
