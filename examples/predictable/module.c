#include "module.h"

MODULE_LICENSE("Dual BSD/GPL");

static int seed = 0;
module_param(seed, int, 0);
MODULE_PARM_DESC(seed, "Seed the PredictableNumGen");

PredictableNumGen predictableGenerator;

int predictable_proc_read(char* page, char** start, off_t offset,
	int count, int *eof, void* data)
{
	int num;
	int length;
	if (offset) {
		*eof = 1;
		length = 0;
	} else {
		num = class_call0(&predictableGenerator, PredictableNumGen, NextNumber);
		length = snprintf(page, count, "%d", num);
		if (unlikely(length >= count)) {
			length = count;
			BUG();
		}
	}
	return length;
}

static int __init predictable_init(void)
{
	printk(KERN_INFO "predictable: init, seed=%d\n", seed);
	new_PredictableNumGen(&predictableGenerator, seed);
	return class_call0(&predictableGenerator, PredictableNumGen, Setup);
} module_init(predictable_init);

static void __exit predictable_exit(void)
{
	class_call0(&predictableGenerator, Object, Destructor);
	printk(KERN_INFO "predictable: exit\n");
} module_exit(predictable_exit);

// PredictableNumGen

class_begin_impl(PredictableNumGen, Object)
	class_method_impl(PredictableNumGen, Setup,
		PredictableNumGen_Setup)
	class_method_impl(PredictableNumGen, Reseed,
		PredictableNumGen_Reseed)
	class_method_impl(PredictableNumGen, NextNumber,
		PredictableNumGen_NextNumber)
class_end_impl(PredictableNumGen, Object)

/**
 * @param int
 */
class_begin_ctor(PredictableNumGen, Object)
	self->seed_ = class_ctor_arg(int);
	self->procEntry_ = NULL;
class_end_ctor(PredictableNumGen, Object)

class_begin_dtor(PredictableNumGen, Object)
	if (self->procEntry_)
		remove_proc_entry("predictable", NULL);
class_end_dtor(PredictableNumGen, Object)

int PredictableNumGen_Setup(self(PredictableNumGen))
{
	self->procEntry_ = create_proc_entry("predictable", 0644, NULL);
	if (!self->procEntry_) {
		return -ENOMEM;
	}
	self->procEntry_->read_proc = predictable_proc_read;
	return 0;
}

void PredictableNumGen_Reseed(self(PredictableNumGen), int32_t seed)
{
	self->seed_ = seed;
}

int32_t PredictableNumGen_NextNumber(self(PredictableNumGen))
{
	self->seed_ = self->seed_ * 1103515245 + 12345;
	return ((uint32_t)(self->seed_ / 65536) % 32768);
}

