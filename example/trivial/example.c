
#include <stdio.h>

#include "robot.h"
#include "replicator.h"

int main(int argc, char* argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	
	printf("\n");
	
	Robot* robot = new_Robot(NULL, "Robo");
	class_call0(robot, Robot, Status);
	printf("\n");
	delete_Object(robot);
	
	Replicator* replicator = new_Replicator(NULL, "Bug#1", 128);
	Replicator* replica = (Replicator*)class_clone(replicator);
	class_calln(replica, Robot, Rename, "Bug#2");
	class_call0(replicator, Robot, Status);
	printf("\n");
	class_call0(replica, Robot, Status);
	printf("\n");
	delete_Object(replicator);
	delete_Object(replica);
}

