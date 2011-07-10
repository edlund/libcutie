
#include <check.h>
#include <signal.h>
#include <stdio.h>

#include <config.h>
#include <cutie.h>

START_TEST(test_panic)
	panic("test_panic");
END_TEST

Suite* panic_suite(void)
{
	Suite* s;
	TCase* tc;
	
	s = suite_create("panic");
	tc = tcase_create("Core");
	
	suite_add_tcase(s, tc);
	tcase_add_test_raise_signal(tc, test_panic, SIGKILL);
	
	return s;
}

int main(int argc, char* argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	
	int failures;
	Suite* s = panic_suite();
	SRunner* sr = srunner_create(s);
#if !ENABLE_CHECK_FORK
	fprintf(stderr, "check_panic must fork since it checks for SIGKILL\n");
#endif
	srunner_run_all(sr, CK_NORMAL);
	failures = srunner_ntests_failed(sr);
	srunner_free(sr);
	return failures == 0? EXIT_SUCCESS: EXIT_FAILURE;
}

