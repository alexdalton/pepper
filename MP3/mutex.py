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
        # sends a message to a node does not wait for a response
        g_msg[self.to_id].put([self.from_id, self.msg, self.msg_args])

    def send_and_get_response(self):
        # sends a message to a node and waits for a response
        g_msg[self.to_id].put([self.from_id, self.msg, self.msg_args])

        response = g_msg[self.from_id].get(block=True)
        while response[1] != self.ackID:
            g_msg[self.from_id].put(response)
            response = g_msg[self.from_id].get(block=True)
        return response[2]


# thread of each node
class NodeThread(threading.Thread):
    def __init__(self, node_id, N, cs_int, next_req, option):
        threading.Thread.__init__(self)
        self.node_id = node_id

        # set node running parameters
        self.cs_int = cs_int
        self.next_req = next_req
        self.option = option
        self.N = N

        # set state to be init (state = 0)
        self.state = 0

        self.alive = True

        # create message queue for this node
        g_msg[node_id] = Queue.Queue()

        self.receiveThread = receiveThread(self.node_id, self.N)

    def run(self):
        # send hello to N - 1 other threads
        for i in range(0, self.N):
            if (i != self.node_id):
                helloMsg = message(self.node_id, i, "hello")
                helloMsg.send()

        # receive N - 1 hello messages before entering request state
        count = 0
        recvList = []
        while(count < (self.N - 1)):
            if not g_msg[self.node_id].empty():
                msg_tp = g_msg[self.node_id].get()
                from_id = msg_tp[0]
                msg = msg_tp[1]
                if (msg == "hello") and (from_id not in recvList):
                    count = count + 1
                    recvList.append(from_id)

        # received N - 1 messages, set state to request (state = 1)
        self.state = 1

        # start a thread to handle responding the messages
        self.receiveThread.start()

        # start doing the state machine stuff
        self.state_machine()

        # kill receiveThread
        self.receiveThread.kill()

        if self.receiveThread.is_alive():
            self.receiveThread.join()

    def state_machine(self):
        while self.alive:
            pass

    def kill(self):
        self.alive = False


class receiveThread(threading.Thread):
    def __init__(self, node_id, N):
        threading.Thread.__init__(self)
        self.node_id = node_id
        self.N = N
        self.alive = True

    # parse the queue and call respective functions
    def run(self):
        while self.alive:
            if not g_msg[self.node_id].empty():
                msg_tp = g_msg[self.node_id].get()

                # get contents of message
                from_id = msg_tp[0]
                msg = msg_tp[1]
                msg_args = msg_tp[2]

    def kill(self):
        self.alive = False


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
