#ifndef CHECK_CLASS_INTEGERWIDGET_H
#define CHECK_CLASS_INTEGERWIDGET_H

#include "check_class_widget.h"

class_begin_def(IntegerWidget, Widget)
	int n;
class_end_def(IntegerWidget, Widget)

class_begin_methods(IntegerWidget, Widget)
class_end_methods(IntegerWidget, Widget)

void CheckIntegerWidgetObject(IntegerWidget* w);

#endif
