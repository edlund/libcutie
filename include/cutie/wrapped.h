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

#ifndef CUTIE_WRAPPED_H
#define CUTIE_WRAPPED_H

#include <cutie/config.h>

CUTIE_BEGIN_EXTERN_C

#if !CUTIE_KERNEL_CK(CUTIE_KERNEL_CUSTOM)

/**
 * Allocate @p n bytes, usually a wrapper for #malloc. NULL
 * is returned if the request could not be satisfied.
 */
static inline void* walloc(const size_t n)
{
#if CUTIE_KERNEL_CK(CUTIE_KERNEL_NONE)
	return malloc(n);
#elif CUTIE_KERNEL_CK(CUTIE_KERNEL_LINUX)
	return kmalloc(n, GFP_KERNEL);
#endif // CUTIE_KERNEL_CK
}

/**
 * Free a pointer allocated by walloc(), usually a wrapper
 * for #free.
 */
static inline void wfree(void* p)
{
#if CUTIE_KERNEL_CK(CUTIE_KERNEL_NONE)
	free(p);
#elif CUTIE_KERNEL_CK(CUTIE_KERNEL_LINUX)
	kfree(p);
#endif // CUTIE_KERNEL_CK
}

/**
 * Set @p n bytes pointed to by @p p to zero, usually a
 * wrapper for #memset.
 */
static inline void wmemzero(void* p, const size_t n)
{
	memset(p, 0, n);
}

#endif // CUTIE_KERNEL_CK

CUTIE_END_EXTERN_C

#endif // CUTIE_WRAPPED_H

