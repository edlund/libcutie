
#include <check.h>

#include "check_class_abstractgizmo.h"

#if CUTIE_ENABLE_ABSTRACT

class_begin_impl(AbstractGizmo, Object)
	class_method_abstract(AbstractGizmo, Transmogrify)
class_end_impl(AbstractGizmo, Object)

/**
 * No constructor args.
 */
class_begin_ctor(AbstractGizmo, Object)
class_end_ctor(AbstractGizmo, Object)

class_begin_dtor(AbstractGizmo, Object)
class_end_dtor(AbstractGizmo, Object)

void CheckAbstractGizmoObject(AbstractGizmo* a)
{
	fail_unless((struct mtbl_AbstractGizmo*)((Object*)a)->mtbl_ == &mtbl_AbstractGizmo);
	fail_unless(((Object*)a)->metadata_ == &metadata_AbstractGizmo);
	fail_unless(class_mtbl(a, Object)->Constructor == AbstractGizmo_Constructor);
	fail_unless(class_mtbl(a, Object)->Destructor == AbstractGizmo_Destructor);
	fail_unless(class_mtbl(a, Object)->Clone == Object_Clone);
	fail_unless(class_mtbl(a, AbstractGizmo)->Transmogrify == NULL);
	fail_unless(((Object*)a)->metadata_->size_ == sizeof(AbstractGizmo));
}

#endif

