
#include <stdio.h>
#include <string.h>

#include "test.h"

#include <config.h>
#include <cutie.h>

/* Class hierarchy:
 *   > Object
 *   -> AbstractGizmo
 *   -> AutoGizmo
 *   -> EmptyGizmo
 *   -> Widget
 *   --> FileWidget
 *   --> IntegerWidget
 */
#include "class_abstractgizmo.h"
#include "class_autogizmo.h"
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
	ck_assert(empty != NULL);
	CheckEmptyGizmoObject(empty);
	delete_Object(empty);
	
	Widget* widget = new_Widget(NULL, "Widget", NULL);
	ck_assert(widget != NULL);
	CheckWidgetObject(widget);
	delete_Object(widget);
	
	FileWidget* fileWidget = new_FileWidget(NULL, "Widget", NULL);
	ck_assert(fileWidget != NULL);
	CheckFileWidgetObject(fileWidget);
	delete_Object(fileWidget);
	
	IntegerWidget* integerWidget = new_IntegerWidget(NULL, "Widget", NULL, 0);
	ck_assert(integerWidget != NULL);
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
	ck_assert(widget != NULL);
	delete_Object(widget);
	ck_assert(widget == NULL);
	// It should be safe to call delete_Object() on a NULL ptr.
	delete_Object(widget);
END_TEST

static void test_constructor_CheckWidget(Widget* widget, const char* const name,
	const Color* const color)
{
	ck_assert_str_eq(widget->name, name);
	ck_assert(memcmp(&widget->color, color, sizeof(Color)) == 0);
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
	ck_assert(fileWidget.path == NULL);
	ck_assert(fileWidget.file == NULL);
	class_call0(&fileWidget, Object, Destructor);
	
	IntegerWidget integerWidget;
	new_IntegerWidget(&integerWidget, "Widget#202010", &DefaultColor, 7317);
	test_constructor_CheckWidget(class_qcast(&integerWidget, Widget),
		"Widget#202010", &DefaultColor);
	ck_assert(integerWidget.n == 7317);
	class_call0(&integerWidget, Object, Destructor);
END_TEST

static void test_destructor_CheckWidget(Widget* widget)
{
	ck_assert(widget->name == NULL);
	ck_assert(
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
	ck_assert(class_calln(&fileWidget, FileWidget, OpenFile,
		FILEWIDGET_FILE_PATH) != EOF);
	class_call0(&fileWidget, Object, Destructor);
	test_destructor_CheckWidget(class_qcast(&fileWidget, Widget));
	ck_assert(fileWidget.path == NULL);
	ck_assert(fileWidget.file == NULL);
END_TEST

START_TEST(test_class_callx)
	Widget* widget = new_Widget(NULL, "Widget#1", &DefaultColor);
	ck_assert(widget != NULL);
	class_calln(widget, Widget, Rename, "Widget#2");
	ck_assert_str_eq(widget->name, "Widget#2");
	class_calln(widget, Widget, Colorize, 255, 255, 255);
	ck_assert(
		widget->color.r == 255 &&
		widget->color.g == 255 &&
		widget->color.b == 255
	);
	ck_assert(class_call0(widget, Widget, Complexity) == COMPLEXITY_LOW);
	delete_Object(widget);
	
	FileWidget* fileWidget = new_FileWidget(NULL, "Widget#1", &TrendyColor);
	ck_assert(fileWidget != NULL);
	class_calln(fileWidget, Widget, Rename, "Widget#42");
	ck_assert_str_eq(fileWidget->Widget.name, "Widget#42");
	class_calln(fileWidget, Widget, Colorize, 6, 9, 13);
	ck_assert_int_eq(fileWidget->Widget.color.r, 6);
	ck_assert_int_eq(fileWidget->Widget.color.g, 9);
	ck_assert_int_eq(fileWidget->Widget.color.b, 13);
	ck_assert(class_call0(fileWidget, Widget, Complexity) == COMPLEXITY_MEDIUM);
	ck_assert(class_calln(fileWidget, FileWidget, OpenFile, FILEWIDGET_FILE_PATH) != EOF);
	ck_assert(fileWidget->file != NULL);
	ck_assert_str_eq(fileWidget->path, FILEWIDGET_FILE_PATH);
	for (int i = 0; i < 3; ++i) {
		ck_assert(class_call0(fileWidget, FileWidget, GetC) == 'a' + i);
	}
	delete_Object(fileWidget);
END_TEST

START_TEST(test_class_name)
	Widget widget;
	new_Widget(&widget, "W", NULL);
	ck_assert_str_eq(class_name(&widget), "Widget");
	class_call0(&widget, Object, Destructor);
	
	FileWidget fileWidget;
	new_FileWidget(&fileWidget, "W", NULL);
	ck_assert_str_eq(class_name(&fileWidget), "FileWidget");
	class_call0(&fileWidget, Object, Destructor);
END_TEST

START_TEST(test_class_cast)
	FileWidget* fileWidget = new_FileWidget(NULL, "FileWidget", NULL);
	ck_assert(fileWidget != NULL);
	ck_assert(class_cast(fileWidget, Widget) != NULL);
	delete_Object(fileWidget);
	
	Widget* widget = new_Widget(NULL, "Widget", NULL);
	ck_assert(widget != NULL);
	ck_assert(class_cast(widget, FileWidget) == NULL);
	delete_Object(widget);
END_TEST

START_TEST(test_class_instanceof)
	FileWidget* fileWidget = new_FileWidget(NULL, "FileWidget", NULL);
	ck_assert(fileWidget != NULL);
	ck_assert(class_instanceof(fileWidget, Object));
	ck_assert(class_instanceof(fileWidget, Widget));
	ck_assert(class_instanceof(fileWidget, FileWidget));
	ck_assert(!class_instanceof(fileWidget, EmptyGizmo));
	ck_assert(!class_instanceof(fileWidget, IntegerWidget));
	delete_Object(fileWidget);
END_TEST

static void test_class_clone_CheckWidget(Widget* widget, Widget* clone)
{
	ck_assert_str_eq(clone->name, widget->name);
	ck_assert(memcmp(&clone->color, &widget->color, sizeof(Color)) == 0);
}

START_TEST(test_class_clone)
	EmptyGizmo* empty = new_EmptyGizmo(NULL);
	ck_assert(empty != NULL);
	EmptyGizmo* emptyClone = (EmptyGizmo*)class_clone(empty);
	ck_assert(emptyClone != NULL);
	ck_assert(memcmp(empty, emptyClone, sizeof(EmptyGizmo)) == 0);
	delete_Object(empty);
	delete_Object(emptyClone);
	
	Widget* widget = new_Widget(NULL, "Widget", &DefaultColor);
	ck_assert(widget != NULL);
	Widget* widgetClone = (Widget*)class_clone(widget);
	ck_assert(widgetClone != NULL);
	test_class_clone_CheckWidget(widget, widgetClone);
	delete_Object(widget);
	delete_Object(widgetClone);
	
	FileWidget* fileWidget = new_FileWidget(NULL, "FileWidget", &DefaultColor);
	ck_assert(fileWidget != NULL);
	ck_assert(class_calln(fileWidget, FileWidget, OpenFile,
		FILEWIDGET_FILE_PATH) != EOF);
	FileWidget* fileWidgetClone = (FileWidget*)class_clone(fileWidget);
	ck_assert(fileWidgetClone != NULL);
	test_class_clone_CheckWidget(class_qcast(fileWidget, Widget),
		class_qcast(fileWidgetClone, Widget));
	ck_assert_str_eq(fileWidgetClone->path, fileWidget->path);
	ck_assert(class_call0(fileWidgetClone, FileWidget, GetC) == 'a');
	delete_Object(fileWidget);
	delete_Object(fileWidgetClone);
	
	IntegerWidget* integerWidget = new_IntegerWidget(NULL, "IntegerWidget",
		&DefaultColor, 101010);
	ck_assert(integerWidget != NULL);
	IntegerWidget* integerWidgetClone = (IntegerWidget*)class_clone(integerWidget);
	ck_assert(integerWidgetClone != NULL);
	test_class_clone_CheckWidget(class_qcast(integerWidget, Widget),
		class_qcast(integerWidgetClone, Widget));
	ck_assert(integerWidgetClone->n == 101010);
	delete_Object(integerWidget);
	delete_Object(integerWidgetClone);
END_TEST

#if CUTIE_ENABLE_ABSTRACT

static bool test_class_method_abstract_AbstractGizmoHandler_called = false;

void test_class_method_abstract_AbstractGizmoHandler(const char* const name,
	const char* const class, const char* const method)
{
	ck_assert_str_eq(name, "AbstractGizmo");
	ck_assert_str_eq(class, "AbstractGizmo");
	ck_assert_str_eq(method, "Transmogrify");
	test_class_method_abstract_AbstractGizmoHandler_called = true;
}

START_TEST(test_class_method_abstract)
	ClassAbstractHandler expectedHandler = ClassDefaultAbstractHandler;
	ClassAbstractHandler actualHandler = ClassSetAbstractHandler(
		test_class_method_abstract_AbstractGizmoHandler);
	ck_assert(expectedHandler == actualHandler);
	
	AbstractGizmo* abstract = new_AbstractGizmo(NULL);
	CheckAbstractGizmoObject(abstract);
	delete_Object(abstract);
	ck_assert(test_class_method_abstract_AbstractGizmoHandler_called);
	
	ClassSetAbstractHandler(ClassDefaultAbstractHandler);
END_TEST

#endif // CUTIE_ENABLE_ABSTRACT

#if CUTIE_ENABLE_AUTO

START_TEST(test_class_auto_object)
	ck_assert(autoGizmoInstanceCounter == 0);
	do {
		class_auto_object0(AutoGizmo, gizmo);
		ck_assert(autoGizmoInstanceCounter == 1);
		for (int i = 0; i < 2; ++i) {
			class_auto_object0(AutoGizmo, nestedGizmo);
			ck_assert(autoGizmoInstanceCounter == 2);
		}
	} while (0);
	ck_assert(autoGizmoInstanceCounter == 0);
	
	do {
		class_auto_objectn(Widget, widget, "Widget", &TrendyColor);
	} while (0);
END_TEST

#endif // CUTIE_ENABLE_AUTO

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
#endif // CUTIE_ENABLE_ABSTRACT
#if CUTIE_ENABLE_AUTO
	tcase_add_test(tc, test_class_auto_object);
#endif // CUTIE_ENABLE_AUTO
	
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

