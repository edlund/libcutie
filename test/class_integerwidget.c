
#include <check.h>

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
	fail_unless((struct mtbl_IntegerWidget*)((Object*)w)->mtbl_ == &mtbl_IntegerWidget);
	fail_unless(((Object*)w)->metadata_ == &metadata_IntegerWidget);
	fail_unless(class_mtbl(w, Object)->Constructor == IntegerWidget_Constructor);
	fail_unless(class_mtbl(w, Object)->Destructor == IntegerWidget_Destructor);
	fail_unless(class_mtbl(w, Object)->Clone == Widget_Clone);
	fail_unless(class_mtbl(w, Widget)->Rename == Widget_Rename);
	fail_unless(class_mtbl(w, Widget)->Colorize == Widget_Colorize);
	fail_unless(class_mtbl(w, Widget)->Complexity == Widget_Complexity);
	fail_unless(((Object*)w)->metadata_->size_ == sizeof(IntegerWidget));
}
