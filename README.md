


# ROSPlan PDDL experiment 
This repository contains the experiment published in [ROS-POMDP](https://icaps20subpages.icaps-conference.org/wp-content/uploads/2020/10/08-PlanRob_2020_paper_21.pdf) [PlanRob2020](https://icaps20subpages.icaps-conference.org/workshops/planrob/) using [ROSPlan](https://kcl-planning.github.io/ROSPlan/documentation/) with pddl.

It was used to evaluate the [ROSPlan](https://ojs.aaai.org/index.php/ICAPS/article/view/13699/13548) system. 




## Backgroud
As a preliminary effort for designing the AOS planning engine, I wanted to evaluate other robot planning and execution systems starting with ROSPlan.
ROSPlan has made a significant first step in making AI planning accessible for robot programmers using [ROS](http://wiki.ros.org) 
I wanted to compare it with our ROS-POMDP, so I conducted the same experiment as we published in PlanROB2020.

I wanted to use ROSPLan with contingent planning (see [ROSPlan's planner interface](https://kcl-planning.github.io/ROSPlan//documentation/interfaces/02_planner_interface.html) regarding Contingent-FF). But contingent planning is not supported on ROSPlan's main branch (see [github discussion](https://github.com/KCL-Planning/ROSPlan/issues/254#issuecomment-822048585)), so I used the supported temporal planner with replanning. I expected ROSPlan to have a module that controls the triggering of replanning. Yet, they [replied](https://github.com/KCL-Planning/ROSPlan/issues/254#issuecomment-822048585) that it was an existing capability described in their [first article](https://ojs.aaai.org/index.php/ICAPS/article/view/13699/13548), which was removed from the current version, so I implemented a module that triggers planning and replanning when needed. 

# Running the experiment
## Installation
Clone the code using:
```sh
$ git clone --recurse-submodules https://github.com/orhaimwerthaim/AOS-OtherSystems-ROSPlanExperimentPDDL.git
```

echo 'export APP=/opt/tinyos-2.x/apps' >> ~/.bashrc 

Install:
- [ROS](http://wiki.ros.org/ROS/Installation)
- [Install ROSPlan dependencies](https://github.com/KCL-Planning/ROSPlan)

Build it using:
```sh
$ cd <project_path>
$ catkin_make
```
<project_path> stand for the path to your local copy of the repository.

Source:
```sh
echo 'source <project_path>/devel/setup.bash' >> ~/.bashrc     
```

## Running
Since ROSPlan changes the problem.pddl file during its run, we must make sure that the original problem.pddl file is placed.
```sh
cp "<project_path>/src/rosplan_experiment_pddl/pddl/working pddl backup/experiment_problem.pddl" "<project_path>/src/rosplan_experiment_pddl/pddl/experiment_problem.pddl"
```
You will need to restore the experiment_problem.pddl file after every run (use the command above).

To run the experiment symbolically, open a new terminal and run the follwing commands:
```sh
$ roslaunch rosplan_experiment_pddl icaps_experiment_sequential.launch
$ rosservice call /run_planning_control  
```

If you want the gazebo simulation to work:
- Change 'bool useSimulationServices = false;' to 'bool useSimulationServices = true;' in both 'NoKbUpdateActionInterface.h' and 'RPActionInterface.h' placed in '<project_path>/src/ROSPlan/rosplan_planning_system/include/rosplan_action_interface'
- Change the relative path of parameter 'map' in the launch file '<project_path>/src/rosplan_experiment_pddl/launch/icaps_experiment_sequential.launch'
- You may need to change additional relative paths of launch files for the gazebo simulation services (red errors in the terminal screen will point to the paths you need to change)




The ROSPlan experiment is controlled by '<project_path>/src/ROSPlan/rosplan_planning_system/src/RunPlanningControl.cpp', which triggers planning and replanning.

## Related repositories:
- [ROSPlan](https://github.com/KCL-Planning/ROSPlan) repository was copied AS-IS. It will not be updated to prevent breaking the experiment code.
- The BGU [catkin_ws_elevator](https://github.com/bguplp/catkin_ws_elevator/tree/master/src) contains the gazebo simulation used for the ROS-POMDP experiment.

# ROSPlan eveluation report:
## ROSPlan Overview
As explained in the [article](https://ojs.aaai.org/index.php/ICAPS/article/view/13699/13548) and [tutorials](https://kcl-planning.github.io/ROSPlan/documentation/), ROSPlan is a modular system. It has a Knowledge Base (KB) that stores the domain and current state in PDDL format.  A Problem interface node is used to generate a PDDL problem instance from the current state, which is kept in the KB. The KB is initialized by a problem.pddl file, which is updated during execution with by the current state.  ROSPlan has a Planner Interface node, which is a wrapper for AI Planners. The planner is called through a service, which returns true if a solution is found. This interface activate the planner using a command line, sending a domain and problem files as arguments. The resulting plan is written to a file and/or published on a ROS topic. A Parsing Interface node parses the given plan to an executable representation (a simple or ESTEREL plan). This representation is executed by the Plan Dispatch service, which yields false if the plan fails to allow replanning (starting from the current state in the KB). 

ROSPlan also has a Sensing Interface that can update the KB regardless of action execution. This sensing is defined in a configuration file. It allows automatic subscription to ROS topics, periodic calls to ROS services, and defining the transformation from a topic message to a predicate update, possibly by a python script to process the message.

## Issues found in ROSPlan:
- ROSPlan's main branch does not support all of the planners listed in the documentation (See discussion on [Contingent-FF](https://github.com/KCL-Planning/ROSPlan/issues/254#issuecomment-822048585)).
- ROSPlan does not have a module that handles replanning, as one would expect from reading the article. It is the user's responsibility (see [GitHub](https://github.com/KCL-Planning/ROSPlan/issues/254#issuecomment-822048585)).
- ROSPlan's temporal planner (popf) allows concurrent action execution. When concurrent actions are dispatched in ROSPlan, and for some reason, we require replanning, the cancel dispatch service cannot actually cancel the execution, and replanning cannot occur. To allow replanning, I constructed the domain (with a 'can_act' predicate) so that only one action can be executed at any time point. 


## ROSPlan-user integration effort:
### Code:
- Create a PDDL domain and problem file.
- Add an action interface C++ (and header) file for every action,these files can be copied from the ROSPlan tutorial, and they contain a function triggered when ROSPlan dispatches the action. Users should only add a call to their robot action code module. ROSPlan will automatically update the KB by the action effects.   
- For non-deterministic actions, the user must implement his own action interface C++ file. In my implementation, I changed their base interface action class so it will not update the KB automatically. However, I still use their code for subscribing and listening to the dispatch action topic and to trigger the action interface when needed. I had to implement KB updates by the result of my sensing action.  
- The CMakeLists.txt and package.xml files must be updated to build the new files and add the dependency on the user code module packages. 
- The user must implement a module that triggers the different ROSPlan services for planning, plan parsing, and plan dispatching. This module should activate replanning when needed.

### Time:
- Using ROSPlan requires reading their (very good) tutorials, which can take around three days.
- When replanning is needed (since it is not covered in the tutorials) the users must investigate (understanding their code, searching the web, etc.), which can take additional three days.
- For domains with special behavior like indeterministic effects (or sensing), the user must implement his own action interface class; the time taken depends on the complexity of the action behavior and the user experience with ROSPlan. For beginners working on relatively simple actions, it can take another two days of implementation and integration.
- The user must implement his own class for controlling the planning and replanning process. This implementation requires additional knowledge in ROSPlan's code and can take around two days (with integration). 

For a very simple first project, ROSPlan integration can take around ten working days, reasonable. 
 > To understand how the AOS can be closer than ROSPlan to a plug&play solution, see the 'What ROSPlan taught me' section below.  

## Experiment results:
As expected, since PDDL does not capture the domain observation model. Consequently, it was not reasoned about during planning; each noisy sensing action caused an undesired sequence of actions, which in some, but not all, cases can be correct if a correct observation is given afterward. 

An example of when replanning cannot fix a noisy observation is when the robot receives noisy sensing that a can is at the table. It will continue to try and pick it (if it can sense pick action failed). 

Replanning can help if noisy sensing is given that the can is not outside the lab. The robot will try to sense if the can is outside the corridor; correct sensing will cause replanning to bring the robot back to track.

Affective replanning requires users to wisely design the PDDL domain and carefully update the KB when a possibly noisy sensing was received. 


## _What ROSPlan taught me (for designing the AOS):_
- ROSPlan is a modular system that can connect to different planners. **The AOS should also have an architecture that can use other planners, parse their plans to a uniform plan format, and then execute them if needed.**
- [ROSPlan uses](http://kcl-planning.github.io/ROSPlan//tutorials/tutorial_05) ubuntu's DOT application for drawing directed graphs to generate a PDF describing the current plan. Additionally, it has an rqt plugin to see the plan in real-time. This plugin was handy when I needed to fix my PDDL domain. **The AOS should use [ubuntu's applications for drawing graphs](http://manpages.ubuntu.com/manpages/bionic/man1/dot.1.html) to visualize the POMCP tree. Currently, in ROS-POMDP, I am debugging the solver to see the tree. We cannot expect users to do so.**
- ROSPlan has detailed tutorials for some of its capabilities. Any documented capability was easy to understand and emulate; capabilities that were not documented required significant time, investigating ROSPlan's code, searching for examples on the web, and communicating with the ROSPlan's team, so I can understand how to work with ROSPlan. **The AOS must have detailed, user-friendly tutorials. Capabilities that are not documented areas if they do not exist.** Additionally, we cannot expect to have a team working on the system and replying to user requests as ROSPlan has.  
- ROSPlan is strongly coupled with ROS (their communication, data structures, and process activation), it is not required, and **we should be careful from coupling the AOS with specific target frameworks**.
- ROSPlan stores the domain and current state in a persistent way decoupled from the planner. It allows replanning, changing the goals, and is more flexible in general. **To allow flexibility, the AOS should save its domain and current belief state outside the planner process.** 


#### To better support plug&play:
- The AOS should include mapping on how to activate the user code module. More specifically, it should support mapping between action symbolic parameters to actual module activation. This mapping can be done similarly to ROSPlans sensing interface configuration. By either using a direct mapping from a set of action arguments to an activation command; or in a more advanced setting, users can define a python script that performs preprocessing to evaluate the module activation parameters.
- The AOS should map in the same way the translation of module response to valid observations the planner can read.  

#### For increased useability:
- The AOS should also allow the project to run in a symbolic mode without activating the user code modules. The user will see the plan, actions that are currently dispatched, the progress of the belief state, and observation received. 
> Ideally, The system should have a control panel for this and additional uses (like validation and auto-editing of PLPs). In ROSPlan, it is hard to keep track of the current state, and the user may need to activate different services from the terminal along with using the rqt plugin.  

