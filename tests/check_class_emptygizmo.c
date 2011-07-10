
#include <check.h>

#include "check_class_emptygizmo.h"

class_begin_impl(EmptyGizmo, Object)
class_end_impl(EmptyGizmo, Object)

/**
 * No constructor args.
 */
class_begin_ctor(EmptyGizmo, Object)
class_end_ctor(EmptyGizmo, Object)

class_begin_dtor(EmptyGizmo, Object)
class_end_dtor(EmptyGizmo, Object)

void CheckEmptyGizmoObject(EmptyGizmo* e)
{
	fail_unless((struct _mtbl_EmptyGizmo*)((Object*)e)->_mtbl == &_mtbl_EmptyGizmo);
	fail_unless(((Object*)e)->_metadata == &_metadata_EmptyGizmo);
	fail_unless(class_mtbl(e, Object)->Constructor == EmptyGizmo_Constructor);
	fail_unless(class_mtbl(e, Object)->Destructor == EmptyGizmo_Destructor);
	fail_unless(class_mtbl(e, Object)->Clone == Object_Clone);
	fail_unless(((Object*)e)->_metadata->_size == sizeof(EmptyGizmo));
}

