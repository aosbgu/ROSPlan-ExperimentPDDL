/*******************************************************************************
* Copyright (c) 2018, RoboTICan, LTD.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice, this
*   list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright notice,
*   this list of conditions and the following disclaimer in the documentation
*   and/or other materials provided with the distribution.
*
* * Neither the name of RoboTICan nor the names of its
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/
/* Author: Elchay Rauper*/

#include <ros/ros.h>
#include <std_srvs/SetBool.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/CollisionObject.h>
#include <iostream>
#include <sstream>
#include <kdl/chainfksolver.hpp>
#include <kdl/chain.hpp>
#include <kdl/chainjnttojacsolver.hpp>
#include <kdl/frames.hpp>
#include "kdl/chainfksolverpos_recursive.hpp"
#include "kdl_parser/kdl_parser.hpp"

#include "tf_conversions/tf_kdl.h"
#include <message_filters/subscriber.h>
#include <tf/message_filter.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
#include <std_msgs/Int8.h>


bool update_cb(std_srvs::SetBool::Request  &req,std_srvs::SetBool::Response &res);
void handle_objects(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& markers);
void handle_objects_table(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& markers);
void handle_objects_person(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& markers);
std::string get_obj_id(int id);
shape_msgs::SolidPrimitive get_obj_shape(int id);
geometry_msgs::Pose get_obj_position(int id,geometry_msgs::Pose  pose);

bool update=false;
float x_real =0;
float y_real =0;
float z_real =0;

float x_real_can =0;
float y_real_can =0;
float z_real_can =0;

float x_real_person =0;
float y_real_person =0;
float z_real_person =0;

int place_flag = 0;

ros::Publisher chatter16_new;

void cb_table(ar_track_alvar_msgs::AlvarMarkers req) {
    if (!req.markers.empty()) {
      //tf::Quaternion q(req.markers[0].pose.pose.orientation.x, req.markers[0].pose.pose.orientation.y, req.markers[0].pose.pose.orientation.z, req.markers[0].pose.pose.orientation.w);
      //tf::Matrix3x3 m(q);
      //double roll, pitch, yaw;
      //m.getRPY(roll, pitch, yaw);
      //ROS_INFO("roll, pitch, yaw=%1.2f  %1.2f  %1.2f", roll, pitch, yaw);
      // roll  --> rotate around vertical axis
      // pitch --> rotate around horizontal axis
      // yaw   --> rotate around depth axis
      x_real=req.markers[0].pose.pose.position.x;
      y_real=req.markers[0].pose.pose.position.y;
      z_real=req.markers[0].pose.pose.position.z;
      //ROS_INFO_STREAM(x_real);
    }
}

void cb_can(ar_track_alvar_msgs::AlvarMarkers req) {
    if (!req.markers.empty()) {
      //tf::Quaternion q(req.markers[0].pose.pose.orientation.x, req.markers[0].pose.pose.orientation.y, req.markers[0].pose.pose.orientation.z, req.markers[0].pose.pose.orientation.w);
      //tf::Matrix3x3 m(q);
      //double roll, pitch, yaw;
      //m.getRPY(roll, pitch, yaw);
      //ROS_INFO("roll, pitch, yaw=%1.2f  %1.2f  %1.2f", roll, pitch, yaw);
      // roll  --> rotate around vertical axis
      // pitch --> rotate around horizontal axis
      // yaw   --> rotate around depth axis
      x_real_can=req.markers[0].pose.pose.position.x;
      y_real_can=req.markers[0].pose.pose.position.y;
      z_real_can=req.markers[0].pose.pose.position.z;
      //ROS_INFO_STREAM(x_real);
    }
}


void cb_person(ar_track_alvar_msgs::AlvarMarkers req) {
    if (!req.markers.empty()) {
      //tf::Quaternion q(req.markers[0].pose.pose.orientation.x, req.markers[0].pose.pose.orientation.y, req.markers[0].pose.pose.orientation.z, req.markers[0].pose.pose.orientation.w);
      //tf::Matrix3x3 m(q);
      //double roll, pitch, yaw;
      //m.getRPY(roll, pitch, yaw);
      //ROS_INFO("roll, pitch, yaw=%1.2f  %1.2f  %1.2f", roll, pitch, yaw);
      // roll  --> rotate around vertical axis
      // pitch --> rotate around horizontal axis
      // yaw   --> rotate around depth axis
      x_real_person=req.markers[0].pose.pose.position.x;
      y_real_person=req.markers[0].pose.pose.position.y;
      z_real_person=req.markers[0].pose.pose.position.z;
      //ROS_INFO_STREAM(x_real);
    }
}
/*
void cb_flag(const std_msgs::Int8::ConstPtr& msg)
{
  place_flag=msg.data;
}*/

moveit::planning_interface::PlanningSceneInterface *planning_scene_interface_ptr;

//listening to alvar msgs, that are sent througth find object node


int main(int argc, char **argv) {
    ros::init(argc, argv, "objects_handler");
    ros::NodeHandle n;
    ros::NodeHandle n_table;
    ros::NodeHandle nh;
    ros::NodeHandle nh_can;
    ros::NodeHandle nh_flag;
    ros::NodeHandle pn("~");

    // TODO: READ OBJECTS DB
    std::string db_path;
    pn.param<std::string>("db_path", db_path, "??");

    ros::Subscriber ar_sub = n.subscribe("ar_pose_marker", 10, handle_objects);
    ros::Subscriber color_sub = n.subscribe("detected_objects", 10, handle_objects);
    ros::Subscriber color_sub_person = n.subscribe("detected_objects_person", 10, handle_objects_person);
    ros::Subscriber color_sub_table = n_table.subscribe("detected_objects_table", 10, handle_objects_table);

    ros::Subscriber sub = nh.subscribe("/detected_objects_table", 1, cb_table);
    ros::Subscriber sub_can = nh_can.subscribe("/detected_objects", 1, cb_can);
    ros::Subscriber sub_person = nh_can.subscribe("/detected_objects_person", 1, cb_person);
    //ros::Subscriber sub_flag = nh_flag.subscribe("/place_flag", 1000, cb_flag);

    
    ros::ServiceServer service = n.advertiseService("update_collision_objects", update_cb);


    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
    planning_scene_interface_ptr=&planning_scene_interface;

    while (ros::ok())
    {
	//TODO: RATE + TIMEOUT
	//if (update) planning_scene_interface.removeCollisionObjects();
	ros::spinOnce();
    }
    return 0;
}

std::string get_obj_id(int id) { //TODO: FROM DB

   /* std::ostringstream os;
    os<<"object_";
      os << id;
    return os.str();
    */
    if (id==1) 
        return "can";
    if (id==0)
     return "table";
    if (id==2)
     return "person";

}

shape_msgs::SolidPrimitive get_obj_shape(int id) 
{ 	
	//TODO: FROM DB

	shape_msgs::SolidPrimitive object_primitive;
	if (id==1) {
		object_primitive.type = object_primitive.CYLINDER;
		object_primitive.dimensions.resize(2);
		object_primitive.dimensions[0] = 0.145;
		object_primitive.dimensions[1] = 0.03;
	}
	else {
		object_primitive.type = object_primitive.BOX;
   		object_primitive.dimensions.resize(3);
   		object_primitive.dimensions[0] = 0.3;
   		object_primitive.dimensions[1] = 0.3;
     		object_primitive.dimensions[2] = 0.01;
	}
    	return object_primitive;
}

geometry_msgs::Pose get_obj_position(int id,geometry_msgs::Pose  pose){ //TODO: FROM DB

    //if (id==1) pose.position.x+=0.015;
    return pose;
 }

void handle_objects(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& markers)
{
    // Build collisions for moveit
    std::vector<moveit_msgs::CollisionObject> col_objects;

    for (int i=0;i<markers->markers.size();i++) {

        ar_track_alvar_msgs::AlvarMarker m=markers->markers[i];

        moveit_msgs::CollisionObject obj;
        obj.header.frame_id = m.header.frame_id;
        obj.id = get_obj_id(m.id);
        obj.primitives.push_back(get_obj_shape(m.id));

        //obj.primitive_poses.push_back(get_obj_position(m.id,m.pose.pose));
        /* 
        place_flag=0 - initial value, first time
        place_flag=2 - place_talbe service

        */
        

        if (obj.id=="can")
        {
        
        
        m.pose.pose.position.x=x_real_can;
        m.pose.pose.position.y=y_real_can;
        m.pose.pose.position.z=z_real_can;
        obj.primitive_poses.push_back(get_obj_position(m.id,m.pose.pose));
        obj.operation = obj.ADD;
        //true;
        }
        else
        {
        if (obj.id=="table")
        {
        m.pose.pose.position.x=x_real-0.1; //-0.05
        if (y_real>0)
        {
        m.pose.pose.position.y=y_real-0.05;
        }
        else
        {
            m.pose.pose.position.y=y_real+0.05;
        }
        
        m.pose.pose.position.z=z_real-0.05;
        obj.primitive_poses.push_back(get_obj_position(m.id,m.pose.pose));
        obj.operation = obj.ADD;
        }
        }

        if (obj.id=="person")
        {
        m.pose.pose.position.x=x_real_person-0.1;
        m.pose.pose.position.y=y_real_person;
        m.pose.pose.position.z=z_real_person-0.78;
        obj.primitive_poses.push_back(get_obj_position(m.id,m.pose.pose));
        obj.operation = obj.ADD;   
        }
        //obj.operation = obj.ADD;
       

        col_objects.push_back(obj);

        if (update) 
		planning_scene_interface_ptr->addCollisionObjects(col_objects);

    }
}


void handle_objects_table(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& markers)
{
    // Build collisions for moveit
    std::vector<moveit_msgs::CollisionObject> col_objects;

    for (int i=0;i<markers->markers.size();i++) {

        ar_track_alvar_msgs::AlvarMarker m=markers->markers[i];

        moveit_msgs::CollisionObject obj;
        obj.header.frame_id = m.header.frame_id;
        obj.id = get_obj_id(m.id);
        obj.primitives.push_back(get_obj_shape(m.id));

        //obj.primitive_poses.push_back(get_obj_position(m.id,m.pose.pose));
        /* 
        place_flag=0 - initial value, first time
        place_flag=2 - place_talbe service

        */
        

        if (obj.id=="can")
        {
        
        
        m.pose.pose.position.x=x_real_can;
        m.pose.pose.position.y=y_real_can;
        m.pose.pose.position.z=z_real_can;
        obj.primitive_poses.push_back(get_obj_position(m.id,m.pose.pose));
        obj.operation = obj.ADD;
        //true;
        }
  else
        {
           if (obj.id=="table")
        {
        m.pose.pose.position.x=x_real-0.1; //-0.05
        if (y_real>0)
        {
        m.pose.pose.position.y=y_real-0.05;
        }
        else
        {
            m.pose.pose.position.y=y_real+0.05;
        }
        
        m.pose.pose.position.z=z_real-0.05;
        obj.primitive_poses.push_back(get_obj_position(m.id,m.pose.pose));
        obj.operation = obj.ADD;
        }
        }
        //obj.operation = obj.ADD;
          if (obj.id=="person")
        {
        m.pose.pose.position.x=x_real_person-0.1;
        m.pose.pose.position.y=y_real_person;
        m.pose.pose.position.z=z_real_person-0.78;
        obj.primitive_poses.push_back(get_obj_position(m.id,m.pose.pose));
        obj.operation = obj.ADD;   
        }

        col_objects.push_back(obj);

        //if (update) 
		planning_scene_interface_ptr->addCollisionObjects(col_objects);

    }
}

void handle_objects_person(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& markers)
{
    // Build collisions for moveit
    std::vector<moveit_msgs::CollisionObject> col_objects;

    for (int i=0;i<markers->markers.size();i++) {

        ar_track_alvar_msgs::AlvarMarker m=markers->markers[i];

        moveit_msgs::CollisionObject obj;
        obj.header.frame_id = m.header.frame_id;
        obj.id = get_obj_id(m.id);
        obj.primitives.push_back(get_obj_shape(m.id));

        //obj.primitive_poses.push_back(get_obj_position(m.id,m.pose.pose));
        /* 
        place_flag=0 - initial value, first time
        place_flag=2 - place_talbe service

        */
        

        if (obj.id=="can")
        {
        
        
        m.pose.pose.position.x=x_real_can;
        m.pose.pose.position.y=y_real_can;
        m.pose.pose.position.z=z_real_can;
        obj.primitive_poses.push_back(get_obj_position(m.id,m.pose.pose));
        obj.operation = obj.ADD;
        //true;
        }
        else
        {
           if (obj.id=="table")
        {
        m.pose.pose.position.x=x_real-0.1; //-0.05
        if (y_real>0)
        {
        m.pose.pose.position.y=y_real-0.05;
        }
        else
        {
            m.pose.pose.position.y=y_real+0.05;
        }
        
        m.pose.pose.position.z=z_real-0.05;
        obj.primitive_poses.push_back(get_obj_position(m.id,m.pose.pose));
        obj.operation = obj.ADD;
        }
        }
        //obj.operation = obj.ADD;
      if (obj.id=="person")
        {
        m.pose.pose.position.x=x_real_person-0.1;
        m.pose.pose.position.y=y_real_person;
        m.pose.pose.position.z=z_real_person-0.78;
        obj.primitive_poses.push_back(get_obj_position(m.id,m.pose.pose));
        obj.operation = obj.ADD;   
        }

        col_objects.push_back(obj);

        //if (update) 
		planning_scene_interface_ptr->addCollisionObjects(col_objects);

    }
}

bool update_cb(std_srvs::SetBool::Request  &req, std_srvs::SetBool::Response &res) 
{
    update = req.data;
    res.success = true;
    if (update)  res.message = "update collision is ON";
    else res.message = "update collision is OFF";
    return true;
}

