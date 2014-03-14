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

#define PORT "7654"      // the manager port
#define INT_PORT 8000    // initial port
#define MAXDATASIZE 300  // max number of bytes we can get at once
#define MAXNODES 16      // maximum number of nodes


// basic message class for storing data messages received both by other nodes
// and the manager. string hops is used to store the hops made so far by the message
class Message {
    public:
        int from, to;
        std::string message;
        std::string hops;
        Message(int a, int b, std::string msg, std::string hps) :
            from(a), to(b), message(msg), hops(hps) {}
};

// Basic link class for storing links in the link state
class Link {
    public:
        int nodea, nodeb, cost;
        Link(int a, int b, int c) : nodea(a), nodeb(b), cost(c) {}
        Link() : nodea(-1), nodeb(-1), cost(-1) {}
};

// Lots of global variables
std::vector<std::string> ip_store(MAXNODES); // store the ips of the nodes
std::vector<Message> message_store;          // holds messages sent by the manager
std::vector<Message> forwards_store;         // holds messages that need to be forwarded
std::vector<int> path_store[MAXNODES];       // holds the current routing table
std::vector<int> previous_path_store[MAXNODES]; // holds the previous routing ttable
std::vector<Link> link_states;                  // holds all the links in the network
addrinfo * node_addrinfo[MAXNODES];             // holds info for sending UDP packets to nodes

int neighbors[MAXNODES] = {-1, -1, -1, -1,      // stores information on the link costs
                           -1, -1, -1, -1,      // to neighbors
                           -1, -1, -1, -1,
                           -1, -1, -1, -1};
int my_id, manager_fd, sockUDP_fd;             // this nodes ID, and TCP & UDP socket FDs
int sendMessages = 0;       // flag that a new round of messages should be sent
int sendUpdates = 0;        // flag that updates incoming from manager and should be forward
int sendForwards = 0;       // flag indicating pending data messages to forward
int numNodes = 2;           // tracks number of nodes (assumes 2 nodes in a network)
char my_id_str[3];          // string value for node's ID

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

// Sends link state information to all neighbors
void send_links_to_neighbors()
{
    for(std::vector<Link>::iterator it = link_states.begin(); it != link_states.end(); it++)
    {
        for( int i = 0; i < numNodes; i++)
        {
            if (neighbors[i] >= 0 && my_id != i + 1 && it->nodea != i + 1 && it->nodeb != i + 1)
            { 
                char message[100];
                int length = sprintf(message, "R %i %i %i %d", my_id, it->nodea,
                                     it->nodeb, it->cost);
                send_udp_message(i + 1, message, length);
            }
        }
    }
}

// Adds a link state from a message to the link store
void add_to_link_state(int interface, int nodea, int nodeb, int cost, int fromManager)
{
    int isNewLink = 1;
    int neighbor;
    if (nodea == my_id)
    {
        neighbor = nodeb;
    }
    else
    {
        neighbor = nodea;
    }

    for(std::vector<Link>::iterator it = link_states.begin(); it != link_states.end(); it++)
    {
        if((((nodea == it->nodea) && (nodeb == it->nodeb)) or
           ((nodea == it->nodeb) && (nodeb == it->nodea))))
        {
            // existing link, don't do anything with it
            if (cost == it->cost)
            {
                isNewLink = 0;
                break;
            }
            // broken link, set it to broken in link store
            if ( cost < 0)
            {
                it->cost = cost;
                // if the manager told us this, print message
                if(fromManager)
                {
                    std::cout << "no longer linked to node " << neighbor << std::endl;
                }
            }
        }
    }
    if(isNewLink)
    {
        // if new and from manager, print message
        if(fromManager && cost > 0)
        {
            std::cout << "now linked to node " << neighbor << " with cost " <<
                         cost << std::endl;
        }
        Link new_link(nodea, nodeb, cost);
        link_states.push_back(new_link);
        // pass link along to neighbors - interface message was received on
        if(sendMessages or sendUpdates)
        {
            char message[100];
            int length = sprintf(message, "R %i %i %i %d", my_id, nodea, nodeb, cost);
            for(int i = 0; i < numNodes; i++)
            {
                if ((neighbors[i] >= 0) && (my_id != i + 1) && (interface != i + 1))
                {
                    send_udp_message(i + 1, message, length);
                }
            }
        }
    }   
}

// initialize the previous path store to some values
void initialize_previous_path_store()
{
    for(int i = 0; i < numNodes; i++)
    {
        std::vector<int> path;
        path.push_back(i + 1);
        previous_path_store[i] = path;
    }
}

// send the messages sent to this node by the manager
void send_messages()
{
    for(std::vector<Message>::iterator it = message_store.begin(); it != message_store.end(); it++)
    {
        char message[300];
        int length = sprintf(message, "M %i %i %s %s", it->from, it->to, it->hops.c_str(),
                             it->message.c_str());
        send_udp_message(path_store[it->to - 1].front(), message, length);
        std::cout << "from " << it->from << " to " << it->to << " hops ";
        for (int i = 0; i < (int)it->hops.size(); i++)
        {
            std::cout << it->hops[i] << " ";
        }
        std::cout << "message " << it->message << std::endl;

    }
    sendMessages = 0;
}

// send the data messages that need to be forwarded to other nodes
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
            send_udp_message(path_store[it->to - 1].front(), message, length);
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

// gets the cost between two nodes by looking through the link store
// if no link is found or it's negative return a really high number (infinity)
int get_cost(int nodea, int nodeb)
{
    for(std::vector<Link>::iterator it = link_states.begin(); it != link_states.end(); it++)
    {
        if(((nodea == it->nodea) && (nodeb == it->nodeb)) or
           ((nodea == it->nodeb) && (nodeb == it->nodea)))
        {
            if (it->cost > 0)
            {
                return it->cost;
            }
        }
    }
    return 1000000;
}

// check to see if the previous path store and current one match or not
// sometimes with updates a link won't actually change the routing table
// in this case we want indicate it so nothing is printed
int new_path_store()
{
    for(int i = 0; i < numNodes; i++)
    {
        if(path_store[i].size() != previous_path_store[i].size())
        {
            return 1;
        }
        for(int j = 0; j < (int)path_store[i].size(); j++)
        {
            if(path_store[i][j] != previous_path_store[i][j])
            {
                return 1;
            } 
        }
    }
    return 0;
}

// calculates the routing table using Dijkstra's algorithm
void calculate_routing_table()
{
    int node_set[MAXNODES];
    int costs[MAXNODES];
    int count = 1;
    int previous[MAXNODES];
    std::vector<int> rpath_store[MAXNODES];
    for(int i = 0; i  < numNodes; i++)
    {
        std::vector<int> path;
        rpath_store[i] = path;
        path_store[i] = path;
        previous[i] = my_id;
        if(my_id != i + 1)
        {
            costs[i] = get_cost(my_id, i + 1);
            node_set[i] = 0;
        }
        else
        {
            node_set[i] = 1;
            costs[i] = 0;
        }
    }
    while(count <= numNodes)
    {
        int minNode = -1;
        int minCost = 1000000;
        for(int i = 0; i < numNodes; i++)
        {
           if(!node_set[i])
            {
                if(costs[i] < minCost)
                {
                    minCost = costs[i];
                    minNode = i;
                }
            }
        }
        node_set[minNode] = 1;
        count++;
        for(int i = 0; i < numNodes; i++)
        {
            if(!node_set[i])
            {
                int link_cost = get_cost(minNode + 1, i + 1);
                if(minCost + link_cost < costs[i])
                {
                    costs[i] = minCost + link_cost;
                    previous[i] = minNode + 1; // save previous for path tracking
                }
            }
        }
    }

    // get the path to each destination
    // this will be in reversed order
    for(int i = 0; i < numNodes; i++)
    {
        int j = i + 1;
        int count = 0;
        while(j != my_id && count < 10)
        {
            rpath_store[i].push_back(j);
            j = previous[j - 1];
            count++;
        }
    }

    // reverse the paths and set the global path store
    // to be the correct paths
    for( int i = 0; i < numNodes; i++)
    {
        while(!rpath_store[i].empty())
        {
            path_store[i].push_back(rpath_store[i].back());
            rpath_store[i].pop_back();
        } 
    }

    // check if this calculated path store is different than the previous one
    if(new_path_store())
    {
        // if it is print it out
        std::cout << std::endl;
        for( int i = 0; i < numNodes; i++)
        {
            std::cout << i + 1 << " " << costs[i] << ": " << my_id << " ";
            for(std::vector<int>::iterator it = path_store[i].begin();
                it != path_store[i].end(); it++)
            {
                std::cout << *it << " ";
            } 
            std::cout << std::endl;
        }          
        std::cout << std::endl;
    }

    // update previous path store to current path store
    for(int i = 0; i < numNodes; i++)
    {
        previous_path_store[i] = path_store[i];
    }
}


int main(int argc, char *argv[])
{
    // setup connection the manager over TCP
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
    // use FD sets for select functionality
    // need to listen to both TCP from manager and UDP from nodes
    FD_SET(manager_fd, &master);
    fdmax = manager_fd;

    // main listen loop
    // handles node funtionality
    while(1)
    {
        tv.tv_sec = 4; // time out values
        tv.tv_usec = 0;
        read_fds = master;
        if (select(fdmax + 1, &read_fds, NULL, NULL, &tv) == -1)
        {
            perror("select");
            exit(4);
        }

        // have message from manager
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
            // each individual thing is split by new line
            // if it all got sent in one packet
            while (std::getline(stream, line))
            {
                char msg_type;
                char ip_address[MAXNODES];
                char message[256];
                char hops_c[5];
                std::string ip_str;
                std::string msg_str;
                int id, neighbor, cost, to, from, num_nodes;
                Message new_message(-1, -1, "", "");
                Link neighbor_link;
                switch (line[0])
                {
                    case 'I': // ID information for the node
                        sscanf(line.c_str(), "%c %i %i", &msg_type, &id, &num_nodes);
                        numNodes = num_nodes;
                        my_id = id;
                        sprintf(my_id_str, "%d", my_id);
                        // initialize things and start listening on UDP socket
                        initialize_previous_path_store();
                        start_udp();
                        FD_SET(sockUDP_fd, &master);
                        if (sockUDP_fd > fdmax)
                        {
                            fdmax = sockUDP_fd;
                        }
                        break;
                    // neighbor information for the node
                    // includes update information from manager
                    case 'N':
                        sscanf(line.c_str(), "%c %i %d", &msg_type, &neighbor, &cost);
                        add_to_link_state(neighbor, neighbor, my_id, cost, 1);
                        neighbors[neighbor - 1] = cost;
                        break;
                    // IP information for other nodes
                    case 'P':
                        sscanf(line.c_str(), "%c %i %s", &msg_type, &id, ip_address);
                        ip_str = ip_address;
                        ip_store[id - 1] = ip_str;
                        node_addrinfo[id - 1] = get_address_info(id, ip_address);
                        break;
                    // Data message information
                    case 'M':
                        sscanf(line.c_str(), "%c %i %i %[^\n]", &msg_type, &from, &to, message);
                        msg_str = message;
                        new_message.from = from;
                        new_message.to = to;
                        new_message.message = msg_str;
                        sprintf(hops_c, "%d", my_id); 
                        new_message.hops = hops_c;
                        message_store.push_back(new_message);
                        break;
                    // Start message (should start sending data messages when ready)
                    case 'S':
                        sendMessages = 1;
                        //std::cout << "Got start!\n";
                        send_links_to_neighbors();
                        break;
                    // Updates coming from manager, ensure they're forwarded to other nodes
                    case 'C':
                        sendUpdates = 1;
                        break;
                }
            }
	    }
        // message from UDP socket (other nodes)
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
            //std::cout << buf << std::endl; 
            std::istringstream stream(buf);
            std::string line;
            while (std::getline(stream, line))
            {
                char msg_type;
                char message[300];
                int  nodea, nodeb, interface, cost;
                int from, to;
                char hops[50];
                Link new_route;
                std::string hops_str;
                Message new_message(-1, -1, "", "");
                switch (line[0])
                {
                    case 'R': // link state information
                        sscanf(line.c_str(), "%c %i %i %i %d", &msg_type, &interface,
                               &nodea, &nodeb, &cost);
                        add_to_link_state(interface, nodea, nodeb, cost, 0);
                        break;
                    case 'M': // data message information
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
        // we timed out, this means still waiting for nodes to show up
        // or have our routing table and time to send data messages
        else
        {
            sendUpdates = 0; 
            if (sendMessages)
            {
                // whenever sendMessages is high should
                // recalculate routing table
                calculate_routing_table();
                send_messages();
            }
            if (sendForwards)
            {
                send_forwards();
                // make sure to clear forwards storage
                // don't want to resend messages over and over
                forwards_store.clear();
            }
        }
    }
	return 0;
}
