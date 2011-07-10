
#include <stdio.h>

#include "robot.h"

void Robot_Clone(self(Object), Object* original)
{
	class_qcast(self, Robot)->name = strdup(class_qcast(original,
		Robot)->name);
}

void Robot_Rename(self(Robot), const char* const name)
{
	memfree(self->name);
	self->name = strdup(name);
}

void Robot_Status(self(Robot))
{
	printf("class: %s\n", class_name(self));
	printf("name: %s\n", self->name);
}

class_begin_impl(Robot, Object)
	class_method_impl(Object, Clone, Robot_Clone)
	class_method_impl(Robot, Rename, Robot_Rename)
	class_method_impl(Robot, Status, Robot_Status)
class_end_impl(Robot, Object)

/**
 * @param char* name
 */
class_begin_ctor(Robot, Object)
	self->name = strdup(class_ctor_arg(char*));
class_end_ctor(Robot, Object)

class_begin_dtor(Robot, Object)
	memfree(self->name);
	self->name = NULL;
class_end_dtor(Robot, Object)

