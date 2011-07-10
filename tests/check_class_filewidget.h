#ifndef CHECK_CLASS_FILEWIDGET_H
#define CHECK_CLASS_FILEWIDGET_H

#include <stdio.h>

#include "check_class_widget.h"

class_begin_def(FileWidget, Widget)
	char* path;
	FILE* file;
class_end_def(FileWidget, Widget)

#define FileWidget_Init { Widget_Init }

class_begin_methods(FileWidget, Widget)
	int (*GetC)(self(FileWidget));
	int (*CloseFile)(self(FileWidget));
	int (*OpenFile)(self(FileWidget), const char* const path);
class_end_methods(FileWidget, Widget)

void FileWidget_Clone(self(Object), Object* original);
int FileWidget_Complexity(self(Widget));
int FileWidget_GetC(self(FileWidget));
int FileWidget_CloseFile(self(FileWidget));
int FileWidget_OpenFile(self(FileWidget), const char* const path);

void CheckFileWidgetObject(FileWidget* w);

#endif
