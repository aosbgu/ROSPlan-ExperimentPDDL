#!/usr/bin/env python

from plps_launcher.srv import *
import sys
import rospy
import socket
import threading
import os

def pick_action(robot,object, location):
    print "pick execute start"
    rospy.wait_for_service('pick')
    try:
        pick_proxy = rospy.ServiceProxy('pick', pick)
        resp1 = pick_proxy(robot,object, location)
        print "pick result: "+resp1.result
        return resp1.result
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e

def move_to_point_action(robot,location, destination, floor):
    print "move_to_point execut start"
    rospy.wait_for_service('move_to_point')
    try:
        move_to_point_proxy = rospy.ServiceProxy('move_to_point', move_to_point)
        resp1 = move_to_point_proxy(robot, location, destination, floor)
        print "move_to_point result: "+resp1.result
        return resp1.result
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e

def observe_can_action(robot,location, can):
    print "observe_can execut start"
    rospy.wait_for_service('observe_can')
    try:
        observe_can_proxy = rospy.ServiceProxy('observe_can', observe_can)
        resp1 = observe_can_proxy(robot, location, can)
        print "observe_can result: "+resp1.result
        return resp1.result
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e


def dispatcher(service_name, *args):
    #print "module name:"
    #print sys.modules[__name__]
    #print "module att:"
    #print(dir(sys.modules[__name__]))
    #import pdb;
    #pdb.set_trace()
    method_to_call = getattr(sys.modules[__name__], service_name + '_action')
    observation = method_to_call(*args)
    return service_name + ':' + observation


def handle_client_connection(client_socket):
    try:
        print ' '
        print ' '
        print '-----------------------------------------------------------------------------------------------'
        request = client_socket.recv(1024)
        print 'Received {}'.format(request)
        args = request.split(',')
        action_name = args[0]
        args.pop(0)
        print "start calling:" +action_name
        observation = dispatcher(action_name, *args)
        print "finished:" + action_name
        print "action observation:" + observation
        print "response to planner:'" + observation
        client_socket.send(observation)
        client_socket.close()
        print 'connection ended'
    except Exception as e:
        print 'exception thrown: ', e
        client_socket.close()
        print 'connection ended'

def start_tcp_server(host, port):
    #import pdb;
    #pdb.set_trace()
    #with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    server= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((host, port))
    print('bind executed')
    server.listen(100)

    while not rospy.is_shutdown():
        try:
            client_sock, address = server.accept()
            print 'Accepted connection from {}:{}'.format(address[0], address[1])
            client_handler = threading.Thread(
                target=handle_client_connection,
                args=(client_sock,)
                # without comma you'd get a... TypeError: handle_client_connection() argument after * must be a sequence, not _socketobject
            )
            client_handler.start()
        except Exception as e:
            print e
            server.close()
            print('socket closed')
    server.close()
    print('TCP server closed')



if __name__ == "__main__":
    #dispatcher("pick", *['robot2','obj2','location2'])
    #dispatcher("move_to_point", *['robot4','loc4','dest4','floor4'])
    # pick_client("1", "2", "3")


    try:
        HOST = socket.gethostbyname("localhost")
        PORT = 1770
        print('HOST:', HOST)
        start_tcp_server(HOST, PORT)
    except rospy.ROSInterruptException:
        pass
    #pick_client("$robot1", "$object1","$location1")