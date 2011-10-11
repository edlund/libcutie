
#include <check.h>

#include "class_emptygizmo.h"

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
	fail_unless((struct mtbl_EmptyGizmo*)((Object*)e)->mtbl_ == &mtbl_EmptyGizmo);
	fail_unless(((Object*)e)->metadata_ == &metadata_EmptyGizmo);
	fail_unless(class_mtbl(e, Object)->Constructor == EmptyGizmo_Constructor);
	fail_unless(class_mtbl(e, Object)->Destructor == EmptyGizmo_Destructor);
	fail_unless(class_mtbl(e, Object)->Clone == Object_Clone);
	fail_unless(((Object*)e)->metadata_->size_ == sizeof(EmptyGizmo));
}

