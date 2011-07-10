
#include <check.h>

#include <config.h>
#include <cutie.h>

START_TEST(test_strdup)
	char* original = "0123456789";
	char* duplicate = strdup(original);
	fail_unless(strcmp(original, duplicate) == 0);
	memfree(duplicate);
	fail_unless(strdup(NULL) == NULL);
END_TEST

START_TEST(test_strndup)
	char* duplicate = NULL;
	char* original = "0123456789";
	duplicate = strndup(original, 5);
	fail_unless(strcmp("01234", duplicate) == 0);
	memfree(duplicate);
	duplicate = strndup(original, 256);
	fail_unless(strcmp(original, duplicate) == 0);
	memfree(duplicate);
	fail_unless(strndup(NULL, 0) == NULL);
	fail_unless(strndup(NULL, 128) == NULL);
END_TEST

Suite* str_suite(void)
{
	Suite* s;
	TCase* tc;
	
	s = suite_create("str");
	tc = tcase_create("core");
	
	suite_add_tcase(s, tc);
	tcase_add_test(tc, test_strdup);
	tcase_add_test(tc, test_strndup);
	
	return s;
}

int main(int argc, char* argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	
	int failures;
	Suite* s = str_suite();
	SRunner* sr = srunner_create(s);
#if !ENABLE_CHECK_FORK
	srunner_set_fork_status(sr, CK_NOFORK);
#endif
	srunner_run_all(sr, CK_NORMAL);
	failures = srunner_ntests_failed(sr);
	srunner_free(sr);
	return failures == 0? EXIT_SUCCESS: EXIT_FAILURE;
}

