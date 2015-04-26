__author__ = 'Alex Dalton'

from optparse import OptionParser
import threading
import time
import Queue


# global queues for message passing between threads
g_msg = {}
# global dictionary to store thread handles indexed by node ID
n_threads = {}


class message():
    # message class for sending messages between the nodes
    def __init__(self, from_id, to_id, msg, msg_args=[], ackID=None):
        self.from_id = from_id
        self.to_id = to_id
        self.msg = msg
        self.msg_args = msg_args
        self.ackID = ackID

    def send(self):
        # sends a message to a node/s does not wait for a response
        if type(self.to_id) is list:
            for to_id in self.to_id:
                g_msg[to_id].put([self.from_id, self.msg, self.msg_args])
        elif type(self.to_id) is int:
            g_msg[self.to_id].put([self.from_id, self.msg, self.msg_args])

    def send_and_get_response(self):
        # sends a message to a node and waits for a response
        g_msg[self.to_id].put([self.from_id, self.msg, self.msg_args])

        response = g_msg[self.from_id].get(block=True)
        while response[1] != self.ackID:
            g_msg[self.from_id].put(response)
            response = g_msg[self.from_id].get(block=True)
        return response[2]


# thread for each node
class NodeThread(threading.Thread):
    def __init__(self, node_id, N, cs_int, next_req, option):
        threading.Thread.__init__(self)

        # set node running parameters
        self.node_id = node_id
        self.cs_int = float(cs_int) / 1000      # convert from ms to s
        self.next_req = float(next_req) / 1000  # convert from ms to s
        self.option = option
        self.N = N
        self.numReplies = 0
        self.voted = False
        self.requestQueue = Queue.PriorityQueue()

        # set state to be init (state = 0)
        self.state = 0

        # get voting set for this node
        self.votingSet = []
        sqrtN = int(pow(self.N, .5))
        myCol = self.node_id % sqrtN
        myRow = self.node_id / sqrtN
        for i in range(0, self.N):
            col = i % sqrtN
            row = i / sqrtN
            if col == myCol or row == myRow:
                self.votingSet.append(i)

        print(self.node_id, self.votingSet)
        # set node as alive
        self.alive = True

        # create message queue for this node
        g_msg[node_id] = Queue.Queue()

        # get handle for receive thread
        #self.receiveThread = receiveThread(self.node_id, self.N)

    def run(self):
        # send hello to N threads
        message(self.node_id, range(0, self.N), "hello").send()

        # receive N hello messages before entering request state
        count = 0
        while(count < self.N):
            if not g_msg[self.node_id].empty():
                msg = g_msg[self.node_id].get()[1]
                if (msg == "hello"):
                    count = count + 1

        # received N hellos, set state to request (state = 1)
        self.state = 1

        # start a thread to handle responding to messages
        #self.receiveThread.start()

        # start doing the state machine stuff
        self.state_machine()

        # kill receiveThread
        self.receiveThread.kill()

        if self.receiveThread.is_alive():
            self.receiveThread.join()

    def state_machine(self):
        while self.alive:
            # in the request state
            if self.state == 1:
                # multicast request to all nodes in voting set
                message(self.node_id, self.votingSet, "request", [time.time()]).send()
                self.numReplies = 0

                # wait for K = len(self.votingSet) replies
                while (self.numReplies < len(self.votingSet)):
                    self.receive()

                # got K replies set state to held
                self.state = 2

            # in the held state
            elif self.state == 2:
                print("Critical: {0} {1} {2}".format(time.time(), self.node_id, self.votingSet))
                # just receive for cs_int seconds (converted earlier from milliseconds)
                startTime = time.time()
                while(time.time() - startTime < self.cs_int):
                    self.receive()
                # set state to release
                self.state = 3

            # in the release state
            elif self.state == 3:
                # multicast release to all processes in voting set
                message(self.node_id, self.votingSet, "release").send()
                # just receive for next_req seconds (converted earlier from milliseconds)
                startTime = time.time()
                while(time.time() - startTime < self.next_req):
                    self.receive()
                # set state to request again
                self.state = 1



    def receive(self):
        if not g_msg[self.node_id].empty():
            msg_tp = g_msg[self.node_id].get()

            # get contents of message
            from_id = msg_tp[0]
            msg = msg_tp[1]
            msg_args = msg_tp[2]

            if self.option:
                print("\nReceive: {0:.6f} {1} {2} {3} {4}".format(time.time(), self.node_id, from_id, msg, msg_args))

            if msg == "request":
                if self.state == 2 or self.voted == True:
                    self.requestQueue.put((msg_args[0], from_id))
                else:
                    message(self.node_id, from_id, "reply").send()
                    self.voted = True

            elif msg == "reply":
                self.numReplies = self.numReplies + 1
                print("{0} numReplies: {1}".format(self.node_id, self.numReplies))

            elif msg == "release":
                if not self.requestQueue.empty():
                    from_id = self.requestQueue.get()
                    message(self.node_id, from_id, "reply").send()
                    self.voted = True
                else:
                    self.voted = False


    def kill(self):
        self.alive = False


# class receiveThread(threading.Thread):
#     def __init__(self, node_id, N):
#         threading.Thread.__init__(self)
#         self.node_id = node_id
#         self.N = N
#         self.alive = True

#     # parse the queue and call respective functions
#     def run(self):
#         while self.alive:
#             if not g_msg[self.node_id].empty():
#                 msg_tp = g_msg[self.node_id].get()

#                 # get contents of message
#                 from_id = msg_tp[0]
#                 msg = msg_tp[1]
#                 msg_args = msg_tp[2]

#     def kill(self):
#         self.alive = False


if __name__ == '__main__':
    # get command line options for MP3
    parser = OptionParser()
    parser.add_option("-c", "--csint", dest="cs_int", help="time a process spends in the critical section")
    parser.add_option("-n", "--nextreq", dest="next_req", help="time a process waits after exiting the critical section before it requests another critical section entrance")
    parser.add_option("-t", "--totexectime", dest="tot_exec_time", help="total execution time for a thread")
    parser.add_option("-o", "--option", dest="option", help="Whether to print additional info", default=0)

    (options, args) = parser.parse_args()
    print options
    N = 9

    # spawn N node threads
    for i in range(0, N):
        n_threads[i] = NodeThread(i, N, int(options.cs_int), int(options.next_req), bool(options.option))

    # start N threads
    for thread in n_threads.values():
        thread.start()

    # wait for tot_exec_time seconds
    time.sleep(int(options.tot_exec_time))

    # kill all N threads
    for thread in n_threads.values():
        thread.kill()
        if thread.is_alive():
            thread.join()
