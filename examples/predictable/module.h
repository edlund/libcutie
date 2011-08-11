#ifndef MODULE_H
#define MODULE_H

#include <linux/errno.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/proc_fs.h>

#include "cutie.h"

class_begin_def(PredictableNumGen, Object)
	struct proc_dir_entry* procEntry_;
	int32_t seed_;
class_end_def(PredictableNumGen, Object)

#define PredictableNumGen_Init { Object_Init }

class_begin_methods(PredictableNumGen, Object)
	int (*Setup)(self(PredictableNumGen));
	void (*Reseed)(self(PredictableNumGen), int32_t);
	int32_t (*NextNumber)(self(PredictableNumGen));
class_end_methods(PredictableNumGen, Object)

int PredictableNumGen_Setup(self(PredictableNumGen));
void PredictableNumGen_Reseed(self(PredictableNumGen), int32_t);
int32_t PredictableNumGen_NextNumber(self(PredictableNumGen));

#endif

