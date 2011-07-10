#ifndef ROBOT_H
#define ROBOT_H

#include <cutie.h>

class_begin_def(Robot, Object)
	char* name;
class_end_def(Robot, Object)

#define Robot_Init { Object_Init }

class_begin_methods(Robot, Object)
	void (*Rename)(self(Robot), const char* const name);
	void (*Status)(self(Robot));
class_end_methods(Robot, Object)

void Robot_Clone(self(Object), Object* original);
void Robot_Rename(self(Robot), const char* const newName);
void Robot_Status(self(Robot));

#endif // ROBOT_H
