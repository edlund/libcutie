#ifndef CHECK_CLASS_EMPTYGIZMO_H
#define CHECK_CLASS_EMPTYGIZMO_H

#include <cutie.h>

class_begin_def(EmptyGizmo, Object)
class_end_def(EmptyGizmo, Object)

#define EmptyGizmo_Init { Object_Init }

class_begin_methods(EmptyGizmo, Object)
class_end_methods(EmptyGizmo, Object)

void CheckEmptyGizmoObject(EmptyGizmo* e);

#endif
