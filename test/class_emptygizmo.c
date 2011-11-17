
#include "test.h"

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
	ck_assert((struct mtbl_EmptyGizmo*)((Object*)e)->mtbl_ == &mtbl_EmptyGizmo);
	ck_assert(((Object*)e)->metadata_ == &metadata_EmptyGizmo);
	ck_assert(class_mtbl(e, Object)->Constructor == EmptyGizmo_Constructor);
	ck_assert(class_mtbl(e, Object)->Destructor == EmptyGizmo_Destructor);
	ck_assert(class_mtbl(e, Object)->Clone == Object_Clone);
	ck_assert(((Object*)e)->metadata_->size_ == sizeof(EmptyGizmo));
}

