import sys
from sys import stdin
from rtbot_blank import *
import logging
import time
import SocketServer
import socket
import threading
import Queue
import signal

HOST = ''
PORT = 50000

FORMAT = '%(asctime)s %(levelname)s [%(filename)s:%(lineno)d] %(message)s'
DATE_FORMAT = '%H%M%S'

def main():
    logging.basicConfig(level=logging.INFO, format=FORMAT, datefmt=DATE_FORMAT)
    global robot
    robot = Rtbot(sys.argv[1])
    robot.start()
    robot.DriveDistance(300, 1400)
    robot.TurnAngle(200, 17, "ccw")
    robot.DriveDistance(300, 610)
    robot.TurnAngle(200, 70, "cw")

    robot.DriveStraight(300)
    while(not robot.sensors.GetBump()):
        pass
    robot.Stop()

    robot.DriveDistance(-300, 480)
    robot.TurnAngle(200, 70, "ccw")
    robot.DriveDistance(300, 1562)
    robot.TurnAngle(200, 70, "cw")

    robot.DriveStraight(200)
    cliff = True
    while(cliff):
        robot.sensors.GetAll()
        cliff = not(robot.sensors.data['cliff-front-right'] or robot.sensors.data['cliff-front-left'])
    robot.Stop()

    robot.DriveDistance(-300, 700)
    robot.TurnAngle(200, 70, "ccw")

    robot.DriveStraight(300)
    while(robot.sensors.GetAnalogInput() > 30):
        pass
    robot.Stop()

    robot.DriveStraight(-300)
    wheelDrop = True
    while(wheelDrop):
        robot.sensors.GetAll()
        wheelDrop = not(robot.sensors.data['wheel-drop-left'] or robot.sensors.data['wheel-drop-right'])
    robot.Stop()


    

#=============================================================
# place the function calls here

        
if __name__ == '__main__':
  main()
