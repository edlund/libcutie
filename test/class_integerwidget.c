
#include "test.h"

#include "class_integerwidget.h"

class_begin_impl(IntegerWidget, Widget)
class_end_impl(IntegerWidget, Widget)

/**
 * @param int
 */
class_begin_ctor(IntegerWidget, Widget)
	self->n = class_ctor_arg(int);
class_end_ctor(IntegerWidget, Widget)

class_begin_dtor(IntegerWidget, Widget)
	self->n = 0;
class_end_dtor(IntegerWidget, Widget)

void CheckIntegerWidgetObject(IntegerWidget* w)
{
	ck_assert((struct mtbl_IntegerWidget*)((Object*)w)->mtbl_ == &mtbl_IntegerWidget);
	ck_assert(((Object*)w)->metadata_ == &metadata_IntegerWidget);
	ck_assert(class_mtbl(w, Object)->Constructor == IntegerWidget_Constructor);
	ck_assert(class_mtbl(w, Object)->Destructor == IntegerWidget_Destructor);
	ck_assert(class_mtbl(w, Object)->Clone == Widget_Clone);
	ck_assert(class_mtbl(w, Widget)->Rename == Widget_Rename);
	ck_assert(class_mtbl(w, Widget)->Colorize == Widget_Colorize);
	ck_assert(class_mtbl(w, Widget)->Complexity == Widget_Complexity);
	ck_assert(((Object*)w)->metadata_->size_ == sizeof(IntegerWidget));
}

