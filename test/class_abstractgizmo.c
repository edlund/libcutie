
#include "test.h"

#include "class_abstractgizmo.h"

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
	ck_assert((struct mtbl_AbstractGizmo*)((Object*)a)->mtbl_ == &mtbl_AbstractGizmo);
	ck_assert(((Object*)a)->metadata_ == &metadata_AbstractGizmo);
	ck_assert(class_mtbl(a, Object)->Constructor == AbstractGizmo_Constructor);
	ck_assert(class_mtbl(a, Object)->Destructor == AbstractGizmo_Destructor);
	ck_assert(class_mtbl(a, Object)->Clone == Object_Clone);
	ck_assert(class_mtbl(a, AbstractGizmo)->Transmogrify == NULL);
	ck_assert(((Object*)a)->metadata_->size_ == sizeof(AbstractGizmo));
}

#endif // CUTIE_ENABLE_ABSTRACT

