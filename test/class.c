
#include <stdio.h>
#include <string.h>

#include <check.h>

#include <config.h>
#include <cutie.h>

/* Class hierarchy:
 *   > Object
 *   -> AbstractGizmo
 *   -> EmptyGizmo
 *   -> Widget
 *   --> FileWidget
 *   --> IntegerWidget
 */
#include "class_abstractgizmo.h"
#include "class_emptygizmo.h"
#include "class_widget.h"
#include "class_filewidget.h"
#include "class_integerwidget.h"

#define FILEWIDGET_FILE_PATH \
	TOP_SRCDIR "/test/class_filewidget.txt"

const Color DefaultColor = { 128, 128, 128 };
const Color TrendyColor = { 16, 16, 16 };

START_TEST(test_new)
	EmptyGizmo* empty = new_EmptyGizmo(NULL);
	fail_if(empty == NULL);
	CheckEmptyGizmoObject(empty);
	delete_Object(empty);
	
	Widget* widget = new_Widget(NULL, "Widget", NULL);
	fail_if(widget == NULL);
	CheckWidgetObject(widget);
	delete_Object(widget);
	
	FileWidget* fileWidget = new_FileWidget(NULL, "Widget", NULL);
	fail_if(fileWidget == NULL);
	CheckFileWidgetObject(fileWidget);
	delete_Object(fileWidget);
	
	IntegerWidget* integerWidget = new_IntegerWidget(NULL, "Widget", NULL, 0);
	fail_if(integerWidget == NULL);
	CheckIntegerWidgetObject(integerWidget);
	delete_Object(integerWidget);
END_TEST

START_TEST(test_placement_new)
	EmptyGizmo empty;
	new_EmptyGizmo(&empty);
	CheckEmptyGizmoObject(&empty);
	class_call0(&empty, Object, Destructor);
	
	Widget widget;
	new_Widget(&widget, "Widget", NULL);
	CheckWidgetObject(&widget);
	class_call0(&widget, Object, Destructor);
	
	FileWidget fileWidget;
	new_FileWidget(&fileWidget, "Widget", NULL);
	CheckFileWidgetObject(&fileWidget);
	class_call0(&fileWidget, Object, Destructor);
	
	IntegerWidget integerWidget;
	new_IntegerWidget(&integerWidget, "Widget", NULL, 0);
	CheckIntegerWidgetObject(&integerWidget);
	class_call0(&integerWidget, Object, Destructor);
END_TEST

START_TEST(test_delete_Object)
	Widget* widget = new_Widget(NULL, "Widget", NULL);
	fail_if(widget == NULL);
	delete_Object(widget);
	fail_unless(widget == NULL);
	// It should be safe to call delete_Object() on a NULL ptr.
	delete_Object(widget);
END_TEST

static void test_constructor_CheckWidget(Widget* widget, const char* const name,
	const Color* const color)
{
	fail_unless(strcmp(widget->name, name) == 0);
	fail_unless(memcmp(&widget->color, color, sizeof(Color)) == 0);
}

START_TEST(test_constructor)
	Widget widget;
	new_Widget(&widget, "Widget#114752", &DefaultColor);
	test_constructor_CheckWidget(&widget, "Widget#114752", &DefaultColor);
	class_call0(&widget, Object, Destructor);
	
	FileWidget fileWidget;
	new_FileWidget(&fileWidget, "Widget#194752", &DefaultColor);
	test_constructor_CheckWidget(class_qcast(&fileWidget, Widget),
		"Widget#194752", &DefaultColor);
	fail_unless(fileWidget.path == NULL);
	fail_unless(fileWidget.file == NULL);
	class_call0(&fileWidget, Object, Destructor);
	
	IntegerWidget integerWidget;
	new_IntegerWidget(&integerWidget, "Widget#202010", &DefaultColor, 7317);
	test_constructor_CheckWidget(class_qcast(&integerWidget, Widget),
		"Widget#202010", &DefaultColor);
	fail_unless(integerWidget.n == 7317);
	class_call0(&integerWidget, Object, Destructor);
END_TEST

static void test_destructor_CheckWidget(Widget* widget)
{
	fail_unless(widget->name == NULL);
	fail_unless(
		widget->color.r == 0 &&
		widget->color.g == 0 &&
		widget->color.b == 0
	);
}

START_TEST(test_destructor)
	Widget widget;
	new_Widget(&widget, "Widget", &DefaultColor);
	class_call0(&widget, Object, Destructor);
	test_destructor_CheckWidget(&widget);
	
	FileWidget fileWidget;
	new_FileWidget(&fileWidget, "Widget", &DefaultColor);
	fail_if(class_calln(&fileWidget, FileWidget, OpenFile,
		FILEWIDGET_FILE_PATH) == EOF);
	class_call0(&fileWidget, Object, Destructor);
	test_destructor_CheckWidget(class_qcast(&fileWidget, Widget));
	fail_unless(fileWidget.path == NULL);
	fail_unless(fileWidget.file == NULL);
END_TEST

START_TEST(test_class_callx)
	Widget* widget = new_Widget(NULL, "Widget#1", &DefaultColor);
	fail_if(widget == NULL);
	class_calln(widget, Widget, Rename, "Widget#2");
	fail_unless(strcmp(widget->name, "Widget#2") == 0);
	class_calln(widget, Widget, Colorize, 255, 255, 255);
	fail_unless(
		widget->color.r == 255 &&
		widget->color.g == 255 &&
		widget->color.b == 255
	);
	fail_unless(class_call0(widget, Widget, Complexity) == COMPLEXITY_LOW);
	delete_Object(widget);
	
	FileWidget* fileWidget = new_FileWidget(NULL, "Widget#1", &TrendyColor);
	fail_if(fileWidget == NULL);
	class_calln(fileWidget, Widget, Rename, "Widget#42");
	fail_unless(strcmp(fileWidget->Widget.name, "Widget#42") == 0);
	class_calln(fileWidget, Widget, Colorize, 6, 9, 13);
	fail_unless(
		fileWidget->Widget.color.r == 6 &&
		fileWidget->Widget.color.g == 9 &&
		fileWidget->Widget.color.b == 13
	);
	fail_unless(class_call0(fileWidget, Widget, Complexity) == COMPLEXITY_MEDIUM);
	fail_if(class_calln(fileWidget, FileWidget, OpenFile, FILEWIDGET_FILE_PATH) == EOF);
	fail_if(fileWidget->file == NULL);
	fail_unless(strcmp(fileWidget->path, FILEWIDGET_FILE_PATH) == 0);
	for (int i = 0; i < 3; ++i) {
		fail_unless(class_call0(fileWidget, FileWidget, GetC) == 'a' + i);
	}
	delete_Object(fileWidget);
END_TEST

START_TEST(test_class_name)
	Widget widget;
	new_Widget(&widget, "W", NULL);
	fail_unless(strcmp(class_name(&widget), "Widget") == 0);
	class_call0(&widget, Object, Destructor);
	
	FileWidget fileWidget;
	new_FileWidget(&fileWidget, "W", NULL);
	fail_unless(strcmp(class_name(&fileWidget), "FileWidget") == 0);
	class_call0(&fileWidget, Object, Destructor);
END_TEST

START_TEST(test_class_cast)
	FileWidget* fileWidget = new_FileWidget(NULL, "FileWidget", NULL);
	fail_if(fileWidget == NULL);
	fail_if(class_cast(fileWidget, Widget) == NULL);
	delete_Object(fileWidget);
	
	Widget* widget = new_Widget(NULL, "Widget", NULL);
	fail_if(widget == NULL);
	fail_unless(class_cast(widget, FileWidget) == NULL);
	delete_Object(widget);
END_TEST

START_TEST(test_class_instanceof)
	FileWidget* fileWidget = new_FileWidget(NULL, "FileWidget", NULL);
	fail_if(fileWidget == NULL);
	fail_unless(class_instanceof(fileWidget, Object));
	fail_unless(class_instanceof(fileWidget, Widget));
	fail_unless(class_instanceof(fileWidget, FileWidget));
	fail_if(class_instanceof(fileWidget, EmptyGizmo));
	fail_if(class_instanceof(fileWidget, IntegerWidget));
	delete_Object(fileWidget);
END_TEST

static void test_class_clone_CheckWidget(Widget* widget, Widget* clone)
{
	fail_unless(strcmp(clone->name, widget->name) == 0);
	fail_unless(memcmp(&clone->color, &widget->color, sizeof(Color)) == 0);
}

START_TEST(test_class_clone)
	EmptyGizmo* empty = new_EmptyGizmo(NULL);
	fail_if(empty == NULL);
	EmptyGizmo* emptyClone = (EmptyGizmo*)class_clone(empty);
	fail_if(emptyClone == NULL);
	fail_unless(memcmp(empty, emptyClone, sizeof(EmptyGizmo)) == 0);
	delete_Object(empty);
	delete_Object(emptyClone);
	
	Widget* widget = new_Widget(NULL, "Widget", &DefaultColor);
	fail_if(widget == NULL);
	Widget* widgetClone = (Widget*)class_clone(widget);
	fail_if(widgetClone == NULL);
	test_class_clone_CheckWidget(widget, widgetClone);
	delete_Object(widget);
	delete_Object(widgetClone);
	
	FileWidget* fileWidget = new_FileWidget(NULL, "FileWidget", &DefaultColor);
	fail_if(fileWidget == NULL);
	fail_if(class_calln(fileWidget, FileWidget, OpenFile,
		FILEWIDGET_FILE_PATH) == EOF);
	FileWidget* fileWidgetClone = (FileWidget*)class_clone(fileWidget);
	fail_if(fileWidgetClone == NULL);
	test_class_clone_CheckWidget(class_qcast(fileWidget, Widget),
		class_qcast(fileWidgetClone, Widget));
	fail_unless(strcmp(fileWidgetClone->path, fileWidget->path) == 0);
	fail_unless(class_call0(fileWidgetClone, FileWidget, GetC) == 'a');
	delete_Object(fileWidget);
	delete_Object(fileWidgetClone);
	
	IntegerWidget* integerWidget = new_IntegerWidget(NULL, "IntegerWidget",
		&DefaultColor, 101010);
	fail_if(integerWidget == NULL);
	IntegerWidget* integerWidgetClone = (IntegerWidget*)class_clone(integerWidget);
	fail_if(integerWidgetClone == NULL);
	test_class_clone_CheckWidget(class_qcast(integerWidget, Widget),
		class_qcast(integerWidgetClone, Widget));
	fail_unless(integerWidgetClone->n == 101010);
	delete_Object(integerWidget);
	delete_Object(integerWidgetClone);
END_TEST

#if CUTIE_ENABLE_ABSTRACT

static bool test_class_method_abstract_AbstractGizmoHandler_called = false;

void test_class_method_abstract_AbstractGizmoHandler(const char* const name,
	const char* const class, const char* const method)
{
	fail_unless(
		strcmp(name, "AbstractGizmo") == 0 &&
		strcmp(class, "AbstractGizmo") == 0
	);
	fail_unless(strcmp(method, "Transmogrify") == 0);
	test_class_method_abstract_AbstractGizmoHandler_called = true;
}

START_TEST(test_class_method_abstract)
	ClassAbstractHandler expectedHandler = ClassDefaultAbstractHandler;
	ClassAbstractHandler actualHandler = ClassSetAbstractHandler(
		test_class_method_abstract_AbstractGizmoHandler);
	fail_unless(expectedHandler == actualHandler);
	
	AbstractGizmo* abstract = new_AbstractGizmo(NULL);
	CheckAbstractGizmoObject(abstract);
	delete_Object(abstract);
	fail_unless(test_class_method_abstract_AbstractGizmoHandler_called);
	
	ClassSetAbstractHandler(ClassDefaultAbstractHandler);
END_TEST

#endif

Suite* class_suite(void)
{
	Suite* s;
	TCase* tc;
	
	s = suite_create("class");
	tc = tcase_create("core");
	
	suite_add_tcase(s, tc);
	tcase_add_test(tc, test_new);
	tcase_add_test(tc, test_placement_new);
	tcase_add_test(tc, test_delete_Object);
	tcase_add_test(tc, test_constructor);
	tcase_add_test(tc, test_destructor);
	tcase_add_test(tc, test_class_callx);
	tcase_add_test(tc, test_class_name);
	tcase_add_test(tc, test_class_cast);
	tcase_add_test(tc, test_class_instanceof);
	tcase_add_test(tc, test_class_clone);
#if CUTIE_ENABLE_ABSTRACT
	tcase_add_test(tc, test_class_method_abstract);
#endif
	
	return s;
}

int main(int argc, char* argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	
	int failures;
	Suite* s = class_suite();
	SRunner* sr = srunner_create(s);
#if !ENABLE_CHECK_FORK
	srunner_set_fork_status(sr, CK_NOFORK);
#endif
	srunner_run_all(sr, CK_NORMAL);
	failures = srunner_ntests_failed(sr);
	srunner_free(sr);
	return failures == 0? EXIT_SUCCESS: EXIT_FAILURE;
}

