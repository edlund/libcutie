
#include <check.h>

#include "check_class_filewidget.h"

void FileWidget_Clone(self(Object), Object* original)
{
	Widget_Clone(self, original);
	class_qcast(self, FileWidget)->path = NULL;
	class_qcast(self, FileWidget)->file = NULL;
	class_calln(self, FileWidget, OpenFile, class_qcast(original,
		FileWidget)->path);
}

int FileWidget_Complexity(self(Widget))
{
	UNUSED(self);
	return COMPLEXITY_MEDIUM;
}

int FileWidget_GetC(self(FileWidget))
{
	return self->file? fgetc(self->file): EOF;
}

int FileWidget_CloseFile(self(FileWidget))
{
	memfree(self->path);
	self->path = NULL;
	int result = 0;
	if (self->file) {
		result = fclose(self->file);
		self->file = NULL;
	}
	return result;
}

int FileWidget_OpenFile(self(FileWidget), const char* const path)
{
	FileWidget_CloseFile(self);
	self->path = strdup(path);
	if (self->path)
		self->file = fopen(self->path, "r");
	return self->file != NULL? 0: EOF;
}

class_begin_impl(FileWidget, Widget)
	class_method_impl(Object, Clone, FileWidget_Clone)
	class_method_impl(Widget, Complexity, FileWidget_Complexity)
	class_method_impl(FileWidget, GetC, FileWidget_GetC)
	class_method_impl(FileWidget, CloseFile, FileWidget_CloseFile)
	class_method_impl(FileWidget, OpenFile, FileWidget_OpenFile)
class_end_impl(FileWidget, Widget)

/**
 */
class_begin_ctor(FileWidget, Widget)
	self->path = NULL;
	self->file = NULL;
class_end_ctor(FileWidget, Widget)

class_begin_dtor(FileWidget, Widget)
	FileWidget_CloseFile(self);
class_end_dtor(FileWidget, Widget)

void CheckFileWidgetObject(FileWidget* w)
{
	fail_unless((struct _mtbl_FileWidget*)((Object*)w)->_mtbl == &_mtbl_FileWidget);
	fail_unless(((Object*)w)->_metadata == &_metadata_FileWidget);
	fail_unless(class_mtbl(w, Object)->Constructor == FileWidget_Constructor);
	fail_unless(class_mtbl(w, Object)->Destructor == FileWidget_Destructor);
	fail_unless(class_mtbl(w, Object)->Clone == FileWidget_Clone);
	fail_unless(class_mtbl(w, Widget)->Rename == Widget_Rename);
	fail_unless(class_mtbl(w, Widget)->Colorize == Widget_Colorize);
	fail_unless(class_mtbl(w, Widget)->HexColor == Widget_HexColor);
	fail_unless(class_mtbl(w, Widget)->Complexity == FileWidget_Complexity);
	fail_unless(class_mtbl(w, FileWidget)->GetC == FileWidget_GetC);
	fail_unless(class_mtbl(w, FileWidget)->CloseFile == FileWidget_CloseFile);
	fail_unless(class_mtbl(w, FileWidget)->OpenFile == FileWidget_OpenFile);
	fail_unless(((Object*)w)->_metadata->_size == sizeof(FileWidget));
}

