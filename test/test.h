#ifndef TEST_H
#define TEST_H

#include <check.h>

#define REQUIRE_CHECK_VERSION(Major, Minor, Micro) \
	(CHECK_MAJOR_VERSION >= (Major)) && \
	(CHECK_MINOR_VERSION >= (Minor)) && \
	(CHECK_MICRO_VERSION >= (Micro))

#if REQUIRE_CHECK_VERSION(0, 9, 8)

/* Define more assert macros for those who are not using
 * a trunk build of check.
 */

#ifndef ck_assert_int_lt
#define ck_assert_int_lt(X, Y) _ck_assert_int(X, <, Y)
#endif // ck_assert_int_lt

#ifndef ck_assert_int_le
#define ck_assert_int_le(X, Y) _ck_assert_int(X, <=, Y)
#endif // ck_assert_int_le

#ifndef ck_assert_int_gt
#define ck_assert_int_gt(X, Y) _ck_assert_int(X, >, Y)
#endif // ck_assert_int_gt

#ifndef ck_assert_int_ge
#define ck_assert_int_ge(X, Y) _ck_assert_int(X, >=, Y)
#endif // ck_assert_int_ge

#ifndef ck_assert_str_lt
#define ck_assert_str_lt(X, Y) _ck_assert_str(X, <, Y)
#endif // ck_assert_str_lt

#ifndef ck_assert_str_le
#define ck_assert_str_le(X, Y) _ck_assert_str(X, <=, Y)
#endif // ck_assert_str_le

#ifndef ck_assert_str_gt
#define ck_assert_str_gt(X, Y) _ck_assert_str(X, >, Y)
#endif // ck_assert_str_gt

#ifndef ck_assert_str_ge
#define ck_assert_str_ge(X, Y) _ck_assert_str(X, >=, Y)
#endif // ck_assert_str_ge

#else
#error "Unsupported check version, please upgrade to v.0.9.8+."
#endif // REQUIRE_CHECK_VERSION
#undef REQUIRE_CHECK_VERSION

#endif // TEST_H

