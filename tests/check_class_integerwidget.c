
#include <check.h>

#include "check_class_integerwidget.h"

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
	fail_unless((struct _mtbl_IntegerWidget*)((Object*)w)->_mtbl == &_mtbl_IntegerWidget);
	fail_unless(((Object*)w)->_metadata == &_metadata_IntegerWidget);
	fail_unless(class_mtbl(w, Object)->Constructor == IntegerWidget_Constructor);
	fail_unless(class_mtbl(w, Object)->Destructor == IntegerWidget_Destructor);
	fail_unless(class_mtbl(w, Object)->Clone == Widget_Clone);
	fail_unless(class_mtbl(w, Widget)->Rename == Widget_Rename);
	fail_unless(class_mtbl(w, Widget)->Colorize == Widget_Colorize);
	fail_unless(class_mtbl(w, Widget)->HexColor == Widget_HexColor);
	fail_unless(class_mtbl(w, Widget)->Complexity == Widget_Complexity);
	fail_unless(((Object*)w)->_metadata->_size == sizeof(IntegerWidget));
}

