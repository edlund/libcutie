
#include "test.h"

#include "class_autogizmo.h"

#if CUTIE_ENABLE_AUTO

int autoGizmoInstanceCounter = 0;

class_begin_impl(AutoGizmo, Object)
class_end_impl(AutoGizmo, Object)

/**
 * No constructor args.
 */
class_begin_ctor(AutoGizmo, Object)
	autoGizmoInstanceCounter++;
class_end_ctor(AutoGizmo, Object)

class_begin_dtor(AutoGizmo, Object)
	autoGizmoInstanceCounter--;
class_end_dtor(AutoGizmo, Object)

void CheckAutoGizmoObject(AutoGizmo* a)
{
	ck_assert((struct mtbl_AutoGizmo*)((Object*)a)->mtbl_ == &mtbl_AutoGizmo);
	ck_assert(((Object*)a)->metadata_ == &metadata_AutoGizmo);
	ck_assert(class_mtbl(a, Object)->Constructor == AutoGizmo_Constructor);
	ck_assert(class_mtbl(a, Object)->Destructor == AutoGizmo_Destructor);
	ck_assert(class_mtbl(a, Object)->Clone == Object_Clone);
	ck_assert(((Object*)a)->metadata_->size_ == sizeof(AutoGizmo));
}

#endif // CUTIE_ENABLE_AUTO

