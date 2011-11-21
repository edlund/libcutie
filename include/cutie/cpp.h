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
 * Use in macros to make sure that cpp does not interpret
 * the comma as an argument delimeter.
 */
#define CPP_COMMA() ,

/**
 * Empty placeholder, expands to nothing.
 */
#define CPP_EMPTY()

/**
 * Count the number of arguments passed to the macro.
 * 
 * http://groups.google.com/group/comp.std.c/msg/346fc464319b1ee5
 */
#define CPP_COUNT_ARGS(...) \
	CPP_COUNT_ARGS_(__VA_ARGS__, CPP_COUNT_ARGS_RSEQ_N())

#ifndef CUTIE_HIDE_IMPLEMENTATION_DETAILS

#define CPP_COUNT_ARGS_(...) \
	CPP_COUNT_ARGS_ARG_N(__VA_ARGS__)

#define CPP_COUNT_ARGS_ARG_N( \
		 a1,  a2,  a3,  a4,  a5,  a6,  a7,  a8,  a9, a10, \
		a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, \
		a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, \
		a31, a32, a33, a34, a35, a36, a37, a38, a39, a40, \
		a41, a42, a43, a44, a45, a46, a47, a48, a49, a50, \
		a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, \
		a61, a62, a63, a64,                               \
	N, ...) N

#define CPP_COUNT_ARGS_RSEQ_N() \
	                    64, 63, 62, 61, 60, \
	59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
	49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
	39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
	29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
	19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
	 9,  8,  7,  6,  5,  4,  3,  2,  1,  0 

#endif // CUTIE_HIDE_IMPLEMENTATION_DETAILS

/**
 * Mark @p Var as an unused variable in order to avoid
 * compiler warnings.
 */
#define UNUSED(Var) \
	(void)Var

/**@}*/ //group:cpp

#endif // CUTIE_CPP_H

