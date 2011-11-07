
#include <check.h>

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
	// Normal concat
	CPP_CAT(my, Var) = 1;
	// Concat with macro expansion
	#define MUST_EXPAND Var
	CPP_CAT(my, MUST_EXPAND) = 2;
	#undef MUST_EXPAND
	UNUSED(myVar);
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

