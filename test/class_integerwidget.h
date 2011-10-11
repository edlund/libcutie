#ifndef CLASS_INTEGERWIDGET_H
#define CLASS_INTEGERWIDGET_H

#include "class_widget.h"

class_begin_def(IntegerWidget, Widget)
	int n;
class_end_def(IntegerWidget, Widget)

class_begin_methods(IntegerWidget, Widget)
class_end_methods(IntegerWidget, Widget)

void CheckIntegerWidgetObject(IntegerWidget* w);

#endif // CLASS_INTEGERWIDGET_H

