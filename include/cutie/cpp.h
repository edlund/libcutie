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

#ifndef CUTIE_CPP_H
#define CUTIE_CPP_H

/**
 * @defgroup cpp cpp
 * C preprocessor utilities.
 * @{
 */

/**
 * Evaluator for CPP_STR().
 */
#define CPP_STR_(s) #s

/**
 * Stringize @p s.
 */
#define CPP_STR(s) CPP_STR_(s)

/**
 * Evaluator for CPP_CAT().
 */
#define CPP_CAT_(a, b) a##b

/**
 * Concat @p a with @p b.
 */
#define CPP_CAT(a, b) CPP_CAT_(a, b)

/**
 * Mark @p Var as an unused variable in order to avoid
 * compiler warnings.
 */
#define UNUSED(Var) \
	(void)Var

/**@}*/ //group:cpp

#endif // CUTIE_CPP_H

