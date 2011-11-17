
#include "test.h"

#include "class_filewidget.h"

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
	free(self->path);
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
	ck_assert((struct mtbl_FileWidget*)((Object*)w)->mtbl_ == &mtbl_FileWidget);
	ck_assert(((Object*)w)->metadata_ == &metadata_FileWidget);
	ck_assert(class_mtbl(w, Object)->Constructor == FileWidget_Constructor);
	ck_assert(class_mtbl(w, Object)->Destructor == FileWidget_Destructor);
	ck_assert(class_mtbl(w, Object)->Clone == FileWidget_Clone);
	ck_assert(class_mtbl(w, Widget)->Rename == Widget_Rename);
	ck_assert(class_mtbl(w, Widget)->Colorize == Widget_Colorize);
	ck_assert(class_mtbl(w, Widget)->Complexity == FileWidget_Complexity);
	ck_assert(class_mtbl(w, FileWidget)->GetC == FileWidget_GetC);
	ck_assert(class_mtbl(w, FileWidget)->CloseFile == FileWidget_CloseFile);
	ck_assert(class_mtbl(w, FileWidget)->OpenFile == FileWidget_OpenFile);
	ck_assert(((Object*)w)->metadata_->size_ == sizeof(FileWidget));
}

