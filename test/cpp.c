
#include "test.h"

#include <config.h>
#include <cutie.h>

START_TEST(test_CPP_STR)
	const char* foo = CPP_STR(foo);
	UNUSED(foo);
	#define MUST_EXPAND bar
	const char* bar = CPP_STR(MUST_EXPAND);
	#undef MUST_EXPAND
	UNUSED(bar);
END_TEST

START_TEST(test_CPP_CAT)
	int myVar = 0;
	// Normal concat.
	CPP_CAT(my, Var) = 1;
	// Concat with macro expansion.
	#define MUST_EXPAND Var
	CPP_CAT(my, MUST_EXPAND) = 2;
	#undef MUST_EXPAND
	UNUSED(myVar);
END_TEST

START_TEST(test_CPP_COUNT_ARGS)
	ck_assert(CPP_COUNT_ARGS(nonsense()) == 1);
	ck_assert(CPP_COUNT_ARGS("Hello", "World") == 2);
	ck_assert(CPP_COUNT_ARGS(0, 1, 2, 3, 4, 5, 6, 7, 8, 9) == 10);
	ck_assert(CPP_COUNT_ARGS(
		 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
		30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
		40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
		50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
		60, 61, 62, 63) == 64);
END_TEST

Suite* cpp_suite(void)
{
	Suite* s;
	TCase* tc;
	
	s = suite_create("cpp");
	tc = tcase_create("core");
	
	suite_add_tcase(s, tc);
	tcase_add_test(tc, test_CPP_STR);
	tcase_add_test(tc, test_CPP_CAT);
	tcase_add_test(tc, test_CPP_COUNT_ARGS);
	
	return s;
}

int main(int argc, char* argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	
	int failures;
	Suite* s = cpp_suite();
	SRunner* sr = srunner_create(s);
#if !ENABLE_CHECK_FORK
	srunner_set_fork_status(sr, CK_NOFORK);
#endif
	srunner_run_all(sr, CK_NORMAL);
	failures = srunner_ntests_failed(sr);
	srunner_free(sr);
	return failures == 0? EXIT_SUCCESS: EXIT_FAILURE;
}

