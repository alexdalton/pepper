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
#define BACKLOG 16   // pending connections (max num of nodes)
#define MAXNODES 16

// Function used to sort the nodes in ascending order
bool node_sort(int i, int j) {return (i < j);}

// Basic link class for keeping track of the links read from file and stdin
class Link {
    public:
        int node1, node2, cost;

        // Constructor
        Link(int a, int b, int l_cost) : node1(a), node2(b), cost(l_cost) {}
};

// Basic message class for keeping track of data messages for nodes
class Message {
    public:
        int from, to;
        std::string message;

        // Constructor
        Message(int a, int b, std::string msg) : from(a), to(b), message(msg) {}
};

// Topology class, keeps track of the network's topology for the manager
class Topology {
    public:
        std::vector<Link> links; // all links of the network
        int num_links;
        int num_nodes;
        std::vector<int> nodes; // a sortable list of the nodes

        // Constructor
        Topology() : num_links(0), num_nodes(0) {}

        // Adds a link to the network
        // overwrites existing links if updated
        // also return boolean for whether an exact match was found
        int add_link(int node1, int node2, int cost)
        {
            int isMatch = 0;
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
                // link exists, update and return
                if ((node1 == it->node1 and node2 == it->node2) or
                    (node2 == it->node1 and node1 == it->node1))
                {
                    if(cost == it->cost)
                    {
                        isMatch = 1;
                    }
                    *it = new_link;
                    return isMatch;
                }
            }
            // add link to network
            links.push_back(new_link); 
            num_links++;
            return isMatch;
        }

        // function that shorts the nodes for handing out
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

        // test function for printing out a given node's links
        void print_nodes_links(int node)
        {
            std::vector<Link> nodes_links = get_nodes_links(node);
            for (std::vector<Link>::iterator it = nodes_links.begin(); it != nodes_links.end(); it++)
            {
                std::cout << it->node1 << it->node2 << it->cost << std::endl;
            }
        }

        // test function for printing out the entire topology (links)
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

// read in the topology from the given file
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

// read in the data messages from the given file
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

// send data to a node over the TCP socket
void send_to_node(int node_fd, const char * message, int length)
{
    if (send(node_fd, message, length, 0) == -1)
    {
        perror("send");
        close(node_fd);
    }
    //std::cout << "Sending: " << message << std::endl;
}

// send a node's neighbors over the TCP socket
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
            int length = sprintf(message, "N %i %d\n", neighbor_id, it->cost);
            send_to_node(dest_fd, message, length);
        }
    }
}

// send data messages to nodes that are set as the 'from' parameter
// uses TCP socket
void send_messages(int dest_fd, int node_id, std::vector<Message> messages)
{
    for (std::vector<Message>::iterator it = messages.begin();  it != messages.end(); it++)
    {
        if (node_id == it->from)
        {
            char message[300];
            int length = sprintf(message, "M %i %i %s", node_id, it->to, it->message.c_str());
            send_to_node(dest_fd, message, length);
        }
    }
}

// send all the connected ips to give node over TCP socket
void send_connected_ips(int newNodeID, int * node_fds, int connected_nodes,
                        std::vector<std::string> ip_store)
{
    for (int i = 1; i <= connected_nodes; i++)
    {
        if(i != newNodeID)
        {
            char to_connected[100];
            char to_new[100];
            int length1 = sprintf(to_connected, "P %i %s\n", newNodeID,
                                  ip_store[newNodeID - 1].c_str());
            int length2 = sprintf(to_new, "P %i %s\n", i, ip_store[i - 1].c_str());
            send_to_node(node_fds[i - 1], to_connected, length1);
            send_to_node(node_fds[newNodeID - 1], to_new, length2);
        }
    }
}

// sets up the listener socket for new node connections
int setup_manager_listen()
{
    int sockfd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    int yes = 1;
    int rv;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return -1;
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
        return -1;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }

    return sockfd;
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
    std::vector<std::string> ip_store(MAXNODES);
    int node_fds[MAXNODES];

    read_topology(argv[1], topology);
    read_messages(argv[2], messages);

    topology.sort_nodes();
    //topology.print_topology();

    struct sockaddr_storage their_addr;
    socklen_t sin_size;
    int new_fd;
    int listener = setup_manager_listen();
    std::cout << "manager: waiting for nodes connections...\n";

    char s[INET6_ADDRSTRLEN];
    sin_size = sizeof their_addr;
    int connected_nodes = 0;
    // get a number of connections = number nodes
    while (connected_nodes < topology.num_nodes)
    {
        new_fd = accept(listener, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1)
        {
            perror("accept");
            continue;
        }
        node_fds[connected_nodes] = new_fd;

        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *)&their_addr),
                  s, sizeof s);
        std::cout << connected_nodes + 1 << " connection made from " << s << std::endl;
        ip_store[connected_nodes] = s;

        char send_message[100];
        int msg_size = sprintf(send_message, "I %i %i\n", topology.nodes[connected_nodes],
                               topology.num_nodes);
        // send this node all its required information
        send_to_node(new_fd, send_message, msg_size);
        send_connected_ips(topology.nodes[connected_nodes], node_fds, connected_nodes, ip_store);
        send_neighbors(new_fd, topology.nodes[connected_nodes], topology);
        send_messages(new_fd, topology.nodes[connected_nodes], messages);
        connected_nodes++; 
    }
    // all nodes have now connected, signal to each it can begin
    for(int i = 0; i < topology.num_nodes; i++)
    {
        send_to_node(node_fds[i], "S", 1);
    }
    // stdin loop for editing topology
    // the user must wait for the network to finish sending its
    // messages before changing the topology
    // otherwise unpredicatble things happen (probably seg faults)
    while(1)
    {
        int node1, node2, cost;
        std::cout << "Enter new topology:" << std::endl;
        std::cin >> node1 >> node2 >> cost;
        // get new link and add it to the internal topology
        if (topology.add_link(node1, node2, cost))
        {
            std::cout << "Link already exists\n";
            continue;
        }
        // Indicate to nodes the be prepared for a possible update
        for(int i = 0; i < topology.num_nodes; i++)
        {
            send_to_node(node_fds[i], "C", 1);
        }

        // send neighbors again to nodes with updated topology
        for(int i = 0; i < topology.num_nodes; i++)
        {
            send_neighbors(node_fds[i], i + 1, topology);
        }

        // safe gaurd to ensure all nodes handled updates
        sleep(1);

        // indicate to all nodes they can begin sending messages when they converge
        for(int i = 0; i < topology.num_nodes; i++)
        {
            send_to_node(node_fds[i], "S", 1);
        }

    }
    return 0;
}
