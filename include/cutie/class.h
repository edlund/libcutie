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

#ifndef CUTIE_CLASS_H
#define CUTIE_CLASS_H

#include <cutie/config.h>
#include <cutie/cpp.h>
#include <cutie/wrapped.h>

CUTIE_BEGIN_EXTERN_C

/**
 * @defgroup class class
 * OOP utilities.
 * @{
 */

/**
 * Declare a class named @p Name and list its data members.
 * All classes must inherit another class specified by @p
 * Parent. If no suitable user defined class exists which
 * can be used as parent, #Object must be used.
 */
#define class_begin_def(Name, Parent) \
	extern struct CPP_CAT(mtbl_, Name) CPP_CAT(mtbl_, Name); \
	extern struct metadata_Class CPP_CAT(metadata_, Name); \
	struct Name* CPP_CAT(new_, Name)(struct Name*, ...); \
	void CPP_CAT(Name, _Constructor)(void* const, va_list*); \
	void CPP_CAT(Name, _Destructor)(void* const); \
	void CPP_CAT(populate_mtbl_, Name)(struct CPP_CAT(mtbl_, Name)* \
		const, const char* const); \
	typedef struct Name { \
		Parent Parent;
/**
 * @endof class_begin_def().
 */
#define class_end_def(Name, Parent) \
	} Name;

/**
 * Declare the method table for the class @p Name. All
 * methods declared are "virtual" and may be overridden by
 * a sub class. An entry for the method table is simply a
 * function pointer.
 */
#define class_begin_methods(Name, Parent) \
	struct CPP_CAT(mtbl_, Name) { \
		struct CPP_CAT(mtbl_, Parent) Parent;
/**
 * @endof class_begin_methods().
 */
#define class_end_methods(Name, Parent) \
	};

/**
 * Used to declare the self param for methods with a little
 * less typing.
 */
#define self(Class) \
	Class* const self

/**
 * Get the method table declared for @p Class for the given
 * @p Instance. For calling a method use class_call0() or
 * class_calln().
 * 
 * Specifying an invalid @p Class for the given @p Instance
 * will result in undefined behavior at run-time.
 * 
 * Monkey patching is theoretically possible by modifying
 * the method table for a class directly, but it is probably
 * a terrible idea which should be avoided. Special care
 * needs to be taken in a multi-threaded environment to avoid
 * race conditions with new_X() calls when the method table
 * for a class is not yet populated.
 */
#define class_mtbl(Instance, Class) \
	((struct CPP_CAT(mtbl_, Class)*)((Object*)Instance)->mtbl_)

/**
 * Call a method taking no parameters, declared for @p Class,
 * with the given @p Instance.
 */
#define class_call0(Instance, Class, Method) \
	class_mtbl(Instance, Class)->Method((Class*)Instance)

/**
 * Call a method taking one or more parameters, declared
 * for @p Class on the given @p Instance.
 * 
 * Calling class_calln() without method arguments would violate
 * 6.10.3p4 of ISO C99.
 * 
 * http://www.open-std.org/jtc1/sc22/WG14/www/docs/n1256.pdf
 */
#define class_calln(Instance, Class, Method, ...) \
	class_mtbl(Instance, Class)->Method((Class*)Instance, __VA_ARGS__)

/**
 * Declare structures and functions related to the class
 * @p Name and specify how the method table will be populated.
 * Put class_begin_impl() / class_end_impl() in an
 * implementation file (C source file).
 * 
 * Notes about populate_mtbl_X():
 * 
 * - Threads could get into a race about assigning the methods
 * for a class, but since all threads will perform exactly
 * the same actions the result will be consistent.
 * 
 * - The method table being handled is assumed to have all
 * function pointers set to @p NULL before new_X() has been
 * called at least once. Since method tables are initialized
 * from bottom to top, this makes it possible to override
 * a parent method for a child class. Method tables are
 * assumed to be initialized by the compiler in accordance
 * with 6.7.8 of ISO C99.
 * 
 * Notes about new_X():
 * 
 * - If @p ptr_ is NULL memory will be allocated using walloc().
 * Use wfree() to free the ptr. NULL will be returned if the
 * allocation failed.
 */
#define class_begin_impl(Name, Parent) \
	struct CPP_CAT(mtbl_, Name) CPP_CAT(mtbl_, Name); \
	struct metadata_Class CPP_CAT(metadata_, Name) = { \
		.parent_ = &CPP_CAT(metadata_, Parent), \
		.name_ = CPP_STR(Name), \
		.populated_ = 0, \
		.size_ = sizeof(Name) \
	}; \
	Name* CPP_CAT(new_, Name)(Name* ptr_, ...) \
	{ \
		va_list args_; \
		Name* obj_ = (Name*) \
			(ptr_? ptr_: walloc(sizeof(Name))); \
		if (obj_) { \
			if (!CPP_CAT(metadata_, Name).populated_) { \
				CPP_CAT(populate_mtbl_, Name)(&CPP_CAT(mtbl_, Name), \
					CPP_STR(Name)); \
				CPP_CAT(metadata_, Name).populated_ = true; \
			} \
			if (CUTIE_ENABLE_MEMZERO_NEW) { \
				wmemzero(obj_, sizeof(Name)); \
			} \
			class_qcast(obj_, Object)->mtbl_ = (struct mtbl_Object*) \
				&CPP_CAT(mtbl_, Name); \
			class_qcast(obj_, Object)->metadata_ = &CPP_CAT(metadata_, Name); \
			va_start(args_, ptr_); \
			class_mtbl(obj_, Object)->Constructor(obj_, &args_); \
			va_end(args_); \
		} \
		return obj_; \
	} \
	void CPP_CAT(populate_mtbl_, Name)(struct CPP_CAT(mtbl_, Name)* \
		const mtbl_, const char* const name_) \
	{ \
		class_method_impl(Object, Constructor, CPP_CAT(Name, _Constructor)) \
		class_method_impl(Object, Destructor, CPP_CAT(Name, _Destructor))
/**
 * @endof class_begin_impl().
 */
#define class_end_impl(Name, Parent) \
		CPP_CAT(populate_mtbl_, Parent)(&mtbl_->Parent, name_); \
	}

/**
 * Set @p Method on @p Class to @p Impl.
 * 
 * @scope class_begin_impl() => class_end_impl()
 */
#define class_method_impl(Class, Method, Impl) \
	if (!((struct CPP_CAT(mtbl_, Class)*)mtbl_)->Method) { \
		((struct CPP_CAT(mtbl_, Class)*)mtbl_)->Method = Impl; \
	}

/**
 * Declare the constructor for the class @p Name.
 */
#define class_begin_ctor(Name, Parent) \
	void CPP_CAT(Name, _Constructor)(void* const self_, va_list* args_) \
	{ \
		Name* const self = (Name*)self_; \
		CPP_CAT(Parent, _Constructor)(self_, args_); \
		(void)self;
/**
 * @endof class_begin_ctor().
 */
#define class_end_ctor(Name, Parent) \
	}

/**
 * Shift of a constructor argument of the given @p Type.
 * 
 * @scope class_begin_ctor() => class_end_ctor()
 */
#define class_ctor_arg(Type) \
	va_arg(*args_, Type)

/**
 * Declare the destructor for the class @p Name.
 */
#define class_begin_dtor(Name, Parent) \
	void CPP_CAT(Name, _Destructor)(void* const self_) \
	{ \
		Name* const self = (Name*)self_; \
		(void)self;
/**
 * @endof class_begin_dtor().
 */
#define class_end_dtor(Name, Parent) \
		CPP_CAT(Parent, _Destructor)(self_); \
	}

/**
 * @defgroup Object Object
 * Structures and functions related to Object, which is the
 * topmost parent of all classes.
 * @{
 */

struct mtbl_Object;
struct metadata_Class;

/**
 * Topmost parent of all classes.
 */
typedef struct Object {
	/// Method table for the class.
	const struct mtbl_Object* mtbl_;
	/// Metadata about the class.
	const struct metadata_Class* metadata_;
} Object;

/**
 * Each class will have an associated metadata_Class
 * structure which each object of that class will have a
 * pointer to. This is required in order to implement certain
 * RTTI features.
 */
struct metadata_Class {
	/// The metadata for the parent of the described class.
	/// Will be NULL for #Object.
	const struct metadata_Class* const parent_;
	/// The name of the described class.
	const char* const name_;
	/// The size in bytes of the described class.
	const size_t size_;
	/// Determine if the method table for the described class
	/// has been populated.
	bool populated_;
};

/**
 * Metadata about Object.
 */
extern struct metadata_Class metadata_Object;

/**
 * Method table for Object.
 */
struct mtbl_Object {
	/// Called when a new object is created.
	void (*Constructor)(void* const, va_list*);
	/// Should be explicitly called before an object is destroyed.
	void (*Destructor)(void* const);
	/// Called on the replica when an object is cloned.
	void (*Clone)(Object* self, Object* original);
};

/**
 * Initialize the method table for Object to default values
 * if necessary.
 */
void populate_mtbl_Object(struct mtbl_Object*,
	const char* const);

/**
 * Object constructor.
 */
void Object_Constructor(void* const, va_list*);

/**
 * Object destructor.
 */
void Object_Destructor(void* const);

/**
 * Default no-op which is called on the new object created
 * by class_clone() unless a sub class overrides it.
 */
void Object_Clone(self(Object), Object* original);

/**@}*/ //group:Object

/**
 * Get the class name for the given @p Instance.
 */
#define class_name(Instance) \
	((Object*)Instance)->metadata_->name_

/**
 * Perform a quick, but unsafe/unchecked, cast of @p Instance
 * to @p Class.
 */
#define class_qcast(Instance, Class) \
	((Class*)Instance)

/**
 * Perform a "safe" cast of @p Instance to @p Class, @p NULL
 * will be returned if the cast is impossible.
 * 
 * Make sure not to violate strict aliasing rules when using
 * class_cast().
 */
#define class_cast(Instance, Class) \
	(Class*)class_cast_((Object*)Instance, &CPP_CAT(metadata_, Class))

/**
 * Backend for class_cast().
 */
void* class_cast_(Object* const instance_,
	const struct metadata_Class* const target_);

/**
 * Determine if the given @p Instance is an instance of @p
 * Class.
 */
#define class_instanceof(Instance, Class) \
	(class_cast(Instance, Class) != NULL)

/**
 * Clone the given object @p Original. A pointer to an
 * identical object will be returned. Each class can
 * optionally override Object_Clone() to deal with members
 * which needs special handling, like for example a pointer
 * or a resource which can not be shared between multiple
 * objects. It will be called for the created clone.
 * 
 * @p NULL will be returned if memory for the clone could
 * not be allocated using walloc().
 */
#define class_clone(Original) \
	class_clone_((Object*)Original, NULL)

/**
 * Backend for class_clone().
 * 
 * If @p clone_ is NULL, memory for the clone will be
 * allocated using walloc(). If @p clone_ is not NULL, it
 * will be used for the cloning. If @p original_ and @p clone_
 * are not instances of the same class the result will be
 * undefined behaviour.
 */
Object* class_clone_(Object* const original_, Object* clone_);

/**
 * Delete the given heap allocated @p Instance. If @p Instance
 * is a null pointer, no action occurs. wfree() is used to
 * free the pointer, use delete_Object_() to specify another
 * deallocation method.
 */
#define delete_Object(Instance) \
	delete_Object_(wfree, Instance)

/**
 * Backend for delete_Object().
 */
#define delete_Object_(Deallocator, Instance) \
	do { \
		if (Instance) { \
			class_call0(Instance, Object, Destructor); \
			Deallocator(Instance); \
			Instance = NULL; \
		} \
	} while (0)

#if CUTIE_ENABLE_ALIASES
/**
 * @defgroup aliases aliases
 * Aliases for commonly used macros and functions.
 * @{
 */

/**
 * @alias class_call0().
 */
#define call0(Instance, Class, Method) \
	class_call0(Instance, Class, Method)

/**
 * @alias class_calln().
 */
#define calln(Instance, Class, Method, ...) \
	class_calln(Instance, Class, Method, __VA_ARGS__)

/**
 * @alias class_instanceof().
 */
#define instanceof(Instance, Class) \
	class_instanceof(Instance, Class)

/**
 * @alias class_clone().
 */
#define clone(Original) \
	class_clone(Original)

/**@}*/ //group:aliases
#endif // CUTIE_ENABLE_ALIASES

#if CUTIE_ENABLE_ABSTRACT
/**
 * @defgroup abstract abstract
 * Support for abstract methods. This feature is of limited
 * use since instantiation of an abstract class only can
 * be detected and handled at run time.
 * @{
 */

/**
 * Mark a @p Method on @p Class as abstract.
 * 
 * @scope class_begin_impl() => class_end_impl()
 */
#define class_method_abstract(Class, Method) \
	if (!((struct CPP_CAT(mtbl_, Class)*)mtbl_)->Method) { \
		classAbstractHandler_(name_, CPP_STR(Class), CPP_STR(Method)); \
	}

/**
 * Default abstract handler which is called when someone
 * tries to instantiate an abstract class.
 */
void ClassDefaultAbstractHandler(const char* const name_, const char*
	const class_, const char* const method_);

/**
 * Signature for abstract handlers.
 */
typedef void (*ClassAbstractHandler)(const char* const, const char* const,
	const char* const);

/**
 * Pointer to the abstract handler.
 */
extern ClassAbstractHandler classAbstractHandler_;

/**
 * Replace the default abstract handler.
 */
ClassAbstractHandler ClassSetAbstractHandler(ClassAbstractHandler handler_);

/**@}*/ //group:abstract
#endif // CUTIE_ENABLE_ABSTRACT

#if CUTIE_ENABLE_AUTO
/**
 * @defgroup auto auto
 * Support for automatic/scoped objects. In order to work,
 * the compiler must support the cleanup variable attribute
 * which is a gcc extension.
 * @{
 */

#if defined(__GNUC__) || defined(__clang__)

/**
 * Create an @p Instance of @p Class which will be destroyed
 * using class_auto_object_cleanup_() when it goes out of
 * scope. This is achieved through the variable attribute
 * "cleanup", which is a gcc extension.
 * 
 * http://gcc.gnu.org/onlinedocs/gcc/Variable-Attributes.html
 */
#define class_auto_object(Class, Instance) \
	Class Instance __attribute__((cleanup(class_auto_object_cleanup_)))

/**
 * No constructor args.
 */
#define class_auto_object0(Class, Instance) \
	class_auto_object(Class, Instance); \
	CPP_CAT(new_, Class)(&Instance)

/**
 * One or more constructor args.
 */
#define class_auto_objectn(Class, Instance, ...) \
	class_auto_object(Class, Instance); \
	CPP_CAT(new_, Class)(&Instance, __VA_ARGS__)

/**
 * Cleanup function for auto objects.
 */
static inline void class_auto_object_cleanup_(const void* obj_)
{
	class_call0(obj_, Object, Destructor);
}

#else
#error "__attribute__((cleanup(function))) is not supported by your compiler."
#endif // __GNUC__ || __clang__

/**@}*/ //group:auto
#endif // CUTIE_ENABLE_AUTO

/**@}*/ //group:class

CUTIE_END_EXTERN_C

#endif // CUTIE_CLASS_H

