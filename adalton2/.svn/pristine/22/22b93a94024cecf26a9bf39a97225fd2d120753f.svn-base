#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <signal.h>
#include <sstream>
#include <netdb.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <vector>

#include <arpa/inet.h>

#define PORT "7654"     // the manager port
#define INT_PORT 8000   // initial port
#define MAXDATASIZE 300 // max number of bytes we can get at once
#define MAXNODES 16     // maximum number of nodes

// basic message class for storing data messages received both by other nodes
// and the manager. string hopes is used to store the hops made so far by the message
class Message {
    public:
        int from, to;
        std::string message;
        std::string hops;
        Message(int a, int b, std::string msg, std::string hps) :
            from(a), to(b), message(msg), hops(hps) {}
};


// Basic route class for storing neighbor links for distvec
class Route {
    public:
        int dest;
        int nextHop;
        int cost;
        Route(int a, int b, int c) : dest(a), nextHop(b), cost(c) {}
        Route() : dest(-1), nextHop(-1), cost(-1) {}
};

// Lots of global variables
std::vector<std::string> ip_store(MAXNODES);   // store the ips of the nodes
std::vector<Message> message_store;            // holds messages sent by the manager
std::vector<Message> forwards_store;           // holds messages that need to be forwarded
addrinfo * node_addrinfo[MAXNODES];            // holds info for sending UDP packets
int neighbors[MAXNODES] = {-1, -1, -1, -1,     // stores information on the link costs
                           -1, -1, -1, -1,     // to neighbors
                           -1, -1, -1, -1,
                           -1, -1, -1, -1};
int my_id, manager_fd, sockUDP_fd;    // this nodes ID, and sockets
int sendMessages = 0;           // flag that a new round of messages shold be sent
int sendForwards = 0;           // flag that messages ready to be forwarded
int numRoutes = 0;              // keeps track on the number of routes in the table
Route routingTable[MAXNODES];   // routingTable used for distvec algorithm
Route saveTable[MAXNODES];      // previous routing table
int numNodes = 2;               // number of nodes (assume 2 in a network)
int tableChanged = 1;           // a flag to indicate whether routing table has changed
char my_id_str[3];              // string value of node ID

// Catch SIGINT and do some cleanup
void sigint_handler(int param)
{
    std::cout << "Signal: " << param << " Closing node" << std::endl;
    for (int i = 0; i < MAXNODES; i++)
    {
        freeaddrinfo(node_addrinfo[i]);
    }
    close(manager_fd);
    close(sockUDP_fd);
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// Get the address info for a node given its ID and IP
// port is always INT_PORT + nodeID
addrinfo * get_address_info(int nodeID, char * ip_address)
{
    struct addrinfo hints, *servinfo;
    int rv;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    char port[6];
    sprintf(port, "%d", nodeID + INT_PORT); 
    if ((rv = getaddrinfo(ip_address, port, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return NULL;
    }
    return servinfo; 
}

// Start up the UDP socket
void start_udp()
{
    sockUDP_fd =  -1;
    struct addrinfo hints, *servinfo, *p;
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    char port[6];
    sprintf(port,"%d", INT_PORT + my_id);
    if ((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockUDP_fd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("listener: socket");
            continue;
        }

        if (bind(sockUDP_fd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockUDP_fd);
            perror("listener: bind");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "listener: failed to bind socket\n");
        return;
    }

    freeaddrinfo(servinfo);
}

// Sends a UDP message to a specified node
int send_udp_message(int nodeID, char * message, int length)
{
    int numbytes;
    if ((numbytes = sendto(sockUDP_fd, message, length, 0,
        node_addrinfo[nodeID - 1]->ai_addr, node_addrinfo[nodeID - 1]->ai_addrlen)) == -1)
    {
        perror("send_udp_message: sendto");
        return -1;
    }
    return numbytes;
}

// Sends initial routes to neighbors
void send_routes_to_neighbors()
{
    for(int i = 0; i < MAXNODES; i++)
    {
        if (neighbors[i] != -1)
        {
            for(int j = 0; j < MAXNODES; j++)
            {
               if((routingTable[j].nextHop != -1) && 
                  (routingTable[j].cost != -1 ) && ((j + 1) != my_id) &&
                  (routingTable[j].dest != i + 1))
                {
                    char message[100];
                    int length = sprintf(message, "R %i %i %d", routingTable[j].dest,
                                         my_id, routingTable[j].cost);
                    send_udp_message(i + 1, message, length);              
                }
            }
        }
    }
}

// Function for printing outthe routing table
void print_routing_table()
{
    for(int i = 0; i < numNodes; i++)
    {
        std::cout << routingTable[i].dest << " " << routingTable[i].nextHop << " " <<
                      routingTable[i].cost << std::endl;
    }
    std::cout << std::endl;
}

// send a single route to a neighbor
// used when a route updates the table
void send_route_to_neighbors(Route route)
{
    for(int i = 0; i < MAXNODES; i++)
    {
        if(neighbors[i] != -1)
        {
            char message[100];
            int length = sprintf(message, "R %i %i %d", route.dest,
                                 my_id, route.cost);
            send_udp_message(i + 1, message, length);
        }
    }
}

// main distvec function that takes in a new route from a node
// and handles it properly
void mergeRoute(Route new_route)
{
    Route myRoute = routingTable[new_route.dest - 1];
    if ( ((myRoute.cost < 0) && (new_route.cost > 0)) or
         (myRoute.cost > new_route.cost + routingTable[new_route.nextHop - 1].cost) )
    {
        routingTable[new_route.dest - 1] = new_route;
        routingTable[new_route.dest - 1].cost = 
            new_route.cost + routingTable[new_route.nextHop - 1].cost;
        tableChanged = 1;
        send_route_to_neighbors(routingTable[new_route.dest - 1]);
    }
}

// sends the data messages from the manager
void send_messages()
{
    for(std::vector<Message>::iterator it = message_store.begin(); it != message_store.end(); it++)
    {
        char message[300];
        int length = sprintf(message, "M %i %i %s %s", it->from, it->to, it->hops.c_str(),
                             it->message.c_str());
        send_udp_message(routingTable[it->to - 1].nextHop, message, length);
        std::cout << "from " << it->from << " to " << it->to << " hops ";
        for (int i = 0; i < (int)it->hops.size(); i++)
        {
            std::cout << it->hops[i] << " ";
        }
        std::cout << "message " << it->message << std::endl;

    }
    sendMessages = 0;
}

// sends the messages ready to be forwarded
void send_forwards()
{
    for(std::vector<Message>::iterator it = forwards_store.begin();
        it != forwards_store.end(); it++)
    {
        if (my_id != it->to)
        {
            char message[300];
            int length = sprintf(message, "M %i %i %s %s", it->from, it->to, it->hops.c_str(),
                                 it->message.c_str());
            send_udp_message(routingTable[it->to - 1].nextHop, message, length);
        }
        std::cout << "from " << it->from << " to " << it->to << " hops ";
        for (int i = 0; i < (int)it->hops.size(); i++)
        {
            std::cout << it->hops[i] << " ";
        }
        std::cout << "message " << it->message << std::endl;

    }
    sendForwards = 0;
}

int main(int argc, char *argv[])
{
    // connect to the manager
    int numbytes;  
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    fd_set read_fds;
    fd_set master;
    int fdmax;
    struct timeval tv;

    if (argc != 2)
    {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }

    signal(SIGINT, sigint_handler);
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

    freeaddrinfo(servinfo); // all done with this structure
    FD_SET(manager_fd, &master);
    fdmax = manager_fd;

    // main listen loop
    // uses select to choose between manager and nodes 
    while(1)
    {
        tv.tv_sec = 4;   // timeout values
        tv.tv_usec = 0;
        read_fds = master;
        if (select(fdmax + 1, &read_fds, NULL, NULL, &tv) == -1)
        {
            perror("select");
            exit(4);
        }

        // got message from manager
        if (FD_ISSET(manager_fd, &read_fds))
        {
            if ((numbytes = recv(manager_fd, buf, MAXDATASIZE-1, 0)) == -1)
            {
                perror("recv");
                exit(1);
            }

            buf[numbytes] = '\0';
            std::istringstream stream(buf);
            std::string line;
            // each new line indicates a new set of information
            while (std::getline(stream, line))
            {
                char msg_type;
                char ip_address[MAXNODES];
                char message[256];
                char hops_c[5];
                std::string ip_str;
                std::string msg_str;
                int id, i, neighbor, cost, to, from, num_nodes;
                Message new_message(-1, -1, "", "");
                Route neighbor_route;
                switch (line[0])
                {
                    case 'I': // nod ID information
                        sscanf(line.c_str(), "%c %i %i", &msg_type, &id, &num_nodes);
                        numNodes = num_nodes;
                        my_id = id;
                        sprintf(my_id_str, "%d", my_id);
                        // initialization and start UDP socket
                        for(i = 0; i < numNodes; i++)
                        {
                            Route init_route(i + 1, -1, -1);
                            if (i == (my_id - 1))
                            {
                                init_route.nextHop = my_id;
                                init_route.cost = 0;
                            }
                            routingTable[i] = init_route;
                            saveTable[i] = init_route;
                        }

                        start_udp();
                        FD_SET(sockUDP_fd, &master);
                        if (sockUDP_fd > fdmax)
                        {
                            fdmax = sockUDP_fd;
                        }
                        break;
                    case 'N': // neighbor information
                        sscanf(line.c_str(), "%c %i %d", &msg_type, &neighbor, &cost);
                        neighbor_route.dest = neighbor;
                        neighbor_route.nextHop = neighbor;
                        neighbor_route.cost = cost;
                        routingTable[neighbor - 1] = neighbor_route;
                        // neighbor differs from what it was before
                        // print message depending on value
                        if (cost >= 0 && neighbors[neighbor - 1] != cost)
                        {
                            std::cout << "now linked to node " << neighbor << " with cost " <<
                                         cost << std::endl;
                        }
                        else if (cost < 0 && neighbors[neighbor - 1] >= 0)
                        {
                            std::cout << "no longer linked to node " << neighbor << std::endl;
                        }
                        neighbors[neighbor - 1] = cost;
                        break;
                    case 'P': // IP information
                        sscanf(line.c_str(), "%c %i %s", &msg_type, &id, ip_address);
                        ip_str = ip_address;
                        ip_store[id - 1] = ip_str;
                        node_addrinfo[id - 1] = get_address_info(id, ip_address);
                        break;
                    case 'M': // data message information
                        sscanf(line.c_str(), "%c %i %i %[^\n]", &msg_type, &from, &to, message);
                        msg_str = message;
                        new_message.from = from;
                        new_message.to = to;
                        new_message.message = msg_str;
                        sprintf(hops_c, "%d", my_id); 
                        new_message.hops = hops_c;
                        message_store.push_back(new_message);
                        break;
                    case 'S': // Start signal, indicates ready to start sending data messages
                        sendMessages = 1;
                        send_routes_to_neighbors();
                        break;
                    case 'C': // Indicates updates coming from manager
                        // Do some clearing of structures to handle new information
                        for(i = 0; i < numNodes; i++)
                        {
                            Route init_route(i + 1, -1, -1);
                            if (i == (my_id - 1))
                            {
                                init_route.nextHop = my_id;
                                init_route.cost = 0;
                            }
                            routingTable[i] = init_route;
                        }
                        numRoutes = 0;
                        sendMessages = 0;
                        sendForwards = 0;
                        tableChanged = 1;
                }
            }
	    }
        // Message from nodes (UDP)
        else if (FD_ISSET(sockUDP_fd, &read_fds))
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
            std::istringstream stream(buf);
            std::string line;
            while (std::getline(stream, line))
            {
                char msg_type;
                char message[300];
                int  dest, nextHop, cost;
                int from, to;
                char hops[50];
                Route new_route;
                std::string hops_str;
                Message new_message(-1, -1, "", "");
                switch (line[0])
                {
                    case 'R': // Route information used in distvec
                        sscanf(line.c_str(), "%c %i %i %d", &msg_type, &dest, &nextHop, &cost);
                        new_route.dest = dest;
                        new_route.nextHop = nextHop;
                        new_route.cost = cost;
                        mergeRoute(new_route);
                        break;
                    case 'M': // Data message to be forwarded
                        sscanf(line.c_str(), "%c %i %i %s %[^\n]", &msg_type, &from, &to,
                               hops, message);
                        hops_str = hops;
                        sendForwards = 1;
                        new_message.from = from;
                        new_message.to = to;
                        new_message.hops = hops_str + my_id_str;
                        new_message.message = message; 
                        forwards_store.push_back(new_message);
                        break;
                }
            }
        }
        // select timed out, waiting for nodes to connect or converged
        // if converged should start sending messages
        else
        {
            if (tableChanged && sendMessages)
            {
                int isNewTable = 0;
                for(int i = 0; i < numNodes; i++)
                {
                    if ((saveTable[i].dest != routingTable[i].dest) or
                        (saveTable[i].nextHop != routingTable[i].nextHop) or
                        (saveTable[i].cost != routingTable[i].cost))
                    {
                        isNewTable = 1;
                        break;
                    }
                }
                if(isNewTable)
                {
                    print_routing_table();
                    tableChanged = 0;
                    for(int i = 0; i < numNodes; i++)
                    {
                        saveTable[i] = routingTable[i];
                    }
                }
            }
            if (sendMessages)
            {
                send_messages();
            }
            if (sendForwards)
            {
                send_forwards();
                forwards_store.clear();
            }
        }
    }
	return 0;
}
