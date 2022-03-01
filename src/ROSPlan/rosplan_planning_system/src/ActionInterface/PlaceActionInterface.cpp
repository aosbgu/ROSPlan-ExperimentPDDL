#include "rosplan_action_interface/PlaceActionInterface.h"
#include "rosplan_knowledge_msgs/KnowledgeUpdateService.h"
#include "rosplan_planning_system/PlanDispatch/EsterelPlanDispatcher.h"
#include "diagnostic_msgs/KeyValue.h"
#include <iostream>
#include "robotican_demos_upgrade/place_unknown.h" 
#include <string>
using namespace std;

/* The implementation of RPTutorial.h */
namespace KCL_rosplan {

/* constructor */
	PlaceActionInterface::PlaceActionInterface(ros::NodeHandle &nh) {
		// perform setup
	}

	/* action dispatch callback */
	bool PlaceActionInterface::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) {

		// The action implementation goes here.

		// complete the action
		ROS_WARN("KCL: (%s) ---------------------------------------------------------------------------PlaceActionInterface Action completing.", msg->name.c_str());
ROS_WARN("KCL: PlaceActionInterface Parameters: robot:%s obj:%s location:%s'", msg->parameters[0].value.c_str(),msg->parameters[1].value.c_str(),msg->parameters[2].value.c_str());


		// ROS_INFO("KCL: parameters1:{key='%s',value='%s'} parameters2:{key='%s',value='%s'}", \
		// msg->parameters[0].key, msg->parameters[0].value, msg->parameters[1].key, msg->parameters[1].value);


if(useSimulationServices)
{
ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<robotican_demos_upgrade::place_unknown>("place_unknown");
  robotican_demos_upgrade::place_unknown srv;
  srv.request.robot = msg->parameters[0].value.c_str();
  srv.request.obj = msg->parameters[1].value.c_str();
  srv.request.discrete_location = msg->parameters[2].value.c_str();
  if (client.call(srv))
  {
    ROS_WARN("KCL: (%s) Service place was called from ROSPlan action", msg->name.c_str());
  }
  else
  {
    ROS_ERROR("Failed to call service place");
    return false;
  } 
}
ROS_WARN("KCL: (%s) ************************************************************************PlaceActionInterface Action completing.", msg->name.c_str());
		
		return true;
	}
} // close namespace

	/*-------------*/
	/* Main method */
	/*-------------*/

	int main(int argc, char **argv) {

		ros::init(argc, argv, "rosplan_tutorial_action", ros::init_options::AnonymousName);
		ros::NodeHandle nh("~");

		// create PDDL action subscriber
		KCL_rosplan::PlaceActionInterface rpti(nh);

		rpti.runActionInterface();

		return 0;
	}