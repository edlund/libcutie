#ifndef CHECK_CLASS_WIDGET_H
#define CHECK_CLASS_WIDGET_H

#include <cutie.h>

typedef unsigned char color_t;

typedef struct _Color
{
	color_t r;
	color_t g;
	color_t b;
} Color;

enum {
	COMPLEXITY_LOW = 2,
	COMPLEXITY_MEDIUM = 4,
	COMPLEXITY_HIGH = 8
};

class_begin_def(Widget, Object)
	char* name;
	Color color;
class_end_def(Widget, Object)

#define Widget_Init { Object_Init }

class_begin_methods(Widget, Object)
	void (*Rename)(self(Widget), const char* const name);
	void (*Colorize)(self(Widget), const color_t r, const color_t g,
		const color_t b);
	int (*Complexity)(self(Widget));
class_end_methods(Widget, Object)

void Widget_Clone(self(Object), Object* original);
void Widget_Rename(self(Widget), const char* const newName);
void Widget_Colorize(self(Widget), const color_t r, const color_t g,
	const color_t b);
int Widget_Complexity(self(Widget));

void CheckWidgetObject(Widget* w);

#endif // CHECK_CLASS_WIDGET_H
