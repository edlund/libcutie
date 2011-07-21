/* cutie - C UTilitIEs
 * Copyright (c) 2011, Erik Edlund <erik.o.edlund@gmail.com>
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 *  * Redistributions of source code must retain the above copyright notice,
 *  this list of conditions and the following disclaimer.
 * 
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation
 *  and/or other materials provided with the distribution.
 * 
 *  * Neither the name of Erik Edlund, nor the names of its contributors may
 *  be used to endorse or promote products derived from this software without
 *  specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "cutie.h"

struct _metadata_Class _metadata_Object = {
	._parent = NULL,
	._name = "Object",
	._populated = false,
	._size = sizeof(Object)
};

void Object_Constructor(void* const _self, va_list* _args)
{
	UNUSED(_self);
	UNUSED(_args);
}

void Object_Destructor(void* const _self)
{
	UNUSED(_self);
}

void Object_Clone(self(Object), Object* original)
{
	UNUSED(self);
	UNUSED(original);
}

void _populate_mtbl_Object(struct _mtbl_Object* mtbl,
	const char* const name)
{
	UNUSED(name);
	class_method_impl(Object, Constructor, Object_Constructor)
	class_method_impl(Object, Destructor, Object_Destructor)
	class_method_impl(Object, Clone, Object_Clone)
}

void* _class_cast(Object* const instance,
	const struct _metadata_Class* const target)
{
	bool found = false;
	if (instance && target) {
		const struct _metadata_Class* current = instance->_metadata;
		while (current) {
			if (current == target) {
				found = true;
				break;
			}
			current = current->_parent;
		}
	}
	return found? instance: NULL;
}

Object* _class_clone(Object* const original)
{
	Object* clone = (Object*)walloc(original->_metadata->_size);
	if (clone) {
		memcpy(clone, original, original->_metadata->_size);
		class_calln(clone, Object, Clone, original);
	}
	return clone;
}

#if CUTIE_ENABLE_ABSTRACT

ClassAbstractHandler _classAbstractHandler = ClassDefaultAbstractHandler;

ClassAbstractHandler ClassSetAbstractHandler(ClassAbstractHandler handler)
{
	ClassAbstractHandler old = _classAbstractHandler;
	_classAbstractHandler = handler;
	return old;
}

void ClassDefaultAbstractHandler(const char* const name, const char*
	const class, const char* const method)
{
	panic("Abstract class %s can not be instantiated (method %s::%s is abstract)\n",
		name, class, method);
}

#endif

void* walloc(const size_t n)
{
	return malloc(n);
}

void wfree(void* p)
{
	free(p);
}

#include <signal.h>
#include <stdio.h>
#if HAVE_EXECINFO_H
#include <execinfo.h>
#endif

/* Print a formatted message to stderr, print a backtrace if
 * supported and raise the SIGKILL signal.
 * 
 * This is cuties default user space panic() function.
 * 
 * http://www.gnu.org/s/hello/manual/libc/Backtraces.html
 */
void panic(const char* const format, ...)
{
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
#if HAVE_EXECINFO_H
	void* buffer[32];
	int size = backtrace(buffer, 32);
	char** symbols = backtrace_symbols(buffer, size);
	if (size > 0 && symbols) {
		fprintf(stderr, "\n[backtrace]\n");
		for (int i = 0; i < size; i++)
			fprintf(stderr, "%s\n", symbols[i]);
	}
	free(symbols);
#endif
	raise(SIGKILL);
}

