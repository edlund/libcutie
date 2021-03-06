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

#include <cutie/class.h>
#include <cutie/panic.h>

struct metadata_Class metadata_Object = {
	.parent_ = NULL,
	.name_ = "Object",
	.populated_ = false,
	.size_ = sizeof(Object)
};

void Object_Constructor(void* const self_, va_list* args_)
{
	UNUSED(self_);
	UNUSED(args_);
}

void Object_Destructor(void* const self_)
{
	UNUSED(self_);
}

void Object_Clone(self(Object), Object* original)
{
	UNUSED(self);
	UNUSED(original);
}

void populate_mtbl_Object(struct mtbl_Object* mtbl_,
	const char* const name_)
{
	UNUSED(name_);
	class_method_impl(Object, Constructor, Object_Constructor)
	class_method_impl(Object, Destructor, Object_Destructor)
	class_method_impl(Object, Clone, Object_Clone)
}

void* class_cast_(Object* const instance_,
	const struct metadata_Class* const target_)
{
	bool found_ = false;
	if (instance_ && target_) {
		const struct metadata_Class* current_ = instance_->metadata_;
		while (current_) {
			if (current_ == target_) {
				found_ = true;
				break;
			}
			current_ = current_->parent_;
		}
	}
	return found_? instance_: NULL;
}

Object* class_clone_(Object* const original_, Object* clone_)
{
	clone_ = clone_? clone_: (Object*)walloc(original_->metadata_->size_);
	if (clone_) {
		memcpy(clone_, original_, original_->metadata_->size_);
		class_calln(clone_, Object, Clone, original_);
	}
	return clone_;
}

#if CUTIE_ENABLE_ABSTRACT

ClassAbstractHandler classAbstractHandler_ = ClassDefaultAbstractHandler;

ClassAbstractHandler ClassSetAbstractHandler(ClassAbstractHandler handler_)
{
	ClassAbstractHandler old_ = classAbstractHandler_;
	classAbstractHandler_ = handler_;
	return old_;
}

void ClassDefaultAbstractHandler(const char* const name_, const char*
	const class_, const char* const method_)
{
	panic("Abstract class \"%s\" can not be instantiated"
		" (method \"%s::%s\" is abstract)\n", name_, class_, method_);
}

#endif // CUTIE_ENABLE_ABSTRACT

