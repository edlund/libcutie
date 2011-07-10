
#include <stdio.h>

#include "replicator.h"

void Replicator_Status(self(Robot))
{
	Robot_Status(self);
	printf("blocks: %d\n", class_qcast(self, Replicator)->blocks);
}

class_begin_impl(Replicator, Robot)
	class_method_impl(Robot, Status, Replicator_Status)
class_end_impl(Replicator, Robot)

/**
 * @param int blocks
 */
class_begin_ctor(Replicator, Robot)
	self->blocks = class_ctor_arg(int);
class_end_ctor(Replicator, Robot)

class_begin_dtor(Replicator, Object)
	self->blocks = 0;
class_end_dtor(Replicator, Object)

