#ifndef REPLICATOR_H
#define REPLICATOR_H

#include "robot.h"

class_begin_def(Replicator, Robot)
	int blocks;
class_end_def(Replicator, Robot)

#define Replicator_Init { Robot_Init }

class_begin_methods(Replicator, Robot)
class_end_methods(Replicator, Robot)

void Replicator_Status(self(Robot));

#endif // REPLICATOR_H
