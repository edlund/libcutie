
#include <stdio.h>
#include <string.h>

#include <check.h>

#include "check_class_widget.h"

void Widget_Clone(self(Object), Object* original)
{
	class_qcast(self, Widget)->name = strdup(class_qcast(original,
		Widget)->name);
}

void Widget_Rename(self(Widget), const char* const name)
{
	memfree(self->name);
	self->name = strdup(name);
}

void Widget_Colorize(self(Widget), const color_t r, const color_t g,
	const color_t b)
{
	self->color.r = r;
	self->color.g = g;
	self->color.b = b;
}

char* Widget_HexColor(self(Widget))
{
	char hex[7] = { '\0' };
	snprintf(hex, 7, "%X%X%X", self->color.r, self->color.g,
		self->color.b);
	return strdup(hex);
}

int Widget_Complexity(self(Widget))
{
	UNUSED(self);
	return COMPLEXITY_LOW;
}

class_begin_impl(Widget, Object)
	class_method_impl(Object, Clone, Widget_Clone)
	class_method_impl(Widget, Rename, Widget_Rename)
	class_method_impl(Widget, Colorize, Widget_Colorize)
	class_method_impl(Widget, HexColor, Widget_HexColor)
	class_method_impl(Widget, Complexity, Widget_Complexity)
class_end_impl(Widget, Object)

/**
 * @param char* name
 * @param Color* color
 */
class_begin_ctor(Widget, Object)
	self->name = strdup(class_ctor_arg(char*));
	Color* color = class_ctor_arg(Color*);
	if (color) {
		memcpy(&self->color, color, sizeof(Color));
	} else {
		memset(&self->color, 0, sizeof(Color));
	}
class_end_ctor(Widget, Object)

class_begin_dtor(Widget, Object)
	memfree(self->name);
	self->name = NULL;
	memset(&self->color, 0, sizeof(Color));
class_end_dtor(Widget, Object)

void CheckWidgetObject(Widget* w)
{
	fail_unless((struct _mtbl_Widget*)((Object*)w)->_mtbl == &_mtbl_Widget);
	fail_unless(((Object*)w)->_metadata == &_metadata_Widget);
	fail_unless(class_mtbl(w, Object)->Constructor == Widget_Constructor);
	fail_unless(class_mtbl(w, Object)->Destructor == Widget_Destructor);
	fail_unless(class_mtbl(w, Object)->Clone == Widget_Clone);
	fail_unless(class_mtbl(w, Widget)->Rename == Widget_Rename);
	fail_unless(class_mtbl(w, Widget)->Colorize == Widget_Colorize);
	fail_unless(class_mtbl(w, Widget)->HexColor == Widget_HexColor);
	fail_unless(class_mtbl(w, Widget)->Complexity == Widget_Complexity);
	fail_unless(((Object*)w)->_metadata->_size == sizeof(Widget));
}

