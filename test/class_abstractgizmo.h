#ifndef CLASS_ABSTRACTGIZMO_H
#define CLASS_ABSTRACTGIZMO_H

#include <cutie.h>

#if CUTIE_ENABLE_ABSTRACT

class_begin_def(AbstractGizmo, Object)
class_end_def(AbstractGizmo, Object)

class_begin_methods(AbstractGizmo, Object)
	void (*Transmogrify)(self(AbstractGizmo));
class_end_methods(AbstractGizmo, Object)

void CheckAbstractGizmoObject(AbstractGizmo* a);

#endif // CUTIE_ENABLE_ABSTRACT

#endif // CLASS_ABSTRACTGIZMO_H

