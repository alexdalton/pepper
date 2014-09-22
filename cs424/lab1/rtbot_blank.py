from pyrobot import *
import sys
import logging
import time
import SocketServer
import Queue

BUFFER_SIZE = 1024
COMMANDS = []
ACK = "ACK\n"
CONFIG_CMD = "__cfg_"

#=============================================================
# put defines here e.x.
# define_name = define value



#=============================================================
# define the Rtbot class to init and start itself
class Rtbot(Create):
    def __init__(self, tty='/dev/ttyUSB0'):
        super(Create, self).__init__(tty)
        self.sci.AddOpcodes(CREATE_OPCODES)
        self.sensors = CreateSensors(self)
        self.safe = False  # Use full mode for control.

    def start(self):
        logging.debug('Starting up the Rtbot.')
        self.SoftReset()
        self.Control()

    def DriveDistance(self, velocity, distance):
        self.sensors.GetDistance()
        self.DriveStraight(velocity)
        dist = 0
        while(abs(dist) < distance):
            dist += self.sensors.GetDistance()
        self.Stop()

    def TurnAngle(self, velocity, degree, direction):
        self.sensors.GetAngle()
        self.TurnInPlace(velocity, direction)
        angle = 0
        while(abs(angle) < degree):
            angle += self.sensors.GetAngle()
        self.Stop()

#=============================================================
#place further functions in the Rtbot class e.x.
# def somefunction(some_argvs):
#   some code


# To implement a service, you must derive a class from BaseRequestHandler and redefine its handle() method


#subclass of threading.Thread
#override the run() method in a subclass	
    			
    		
