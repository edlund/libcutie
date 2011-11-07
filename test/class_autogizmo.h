#ifndef CLASS_AUTOGIZMO_H
#define CLASS_AUTOGIZMO_H

#include <cutie.h>

#if CUTIE_ENABLE_AUTO

extern int autoGizmoInstanceCounter;

class_begin_def(AutoGizmo, Object)
class_end_def(AutoGizmo, Object)

class_begin_methods(AutoGizmo, Object)
class_end_methods(AutoGizmo, Object)

void CheckAutoGizmoObject(AutoGizmo* a);

#endif // CUTIE_ENABLE_AUTO

#endif // CLASS_AUTOGIZMO_H

