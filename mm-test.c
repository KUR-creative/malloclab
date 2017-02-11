/*
 * my malloc package unit test
 */

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka/cmocka.h>
/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

static void t1(void** state){
    (void) state; /* unused */
	printf("1");
	printf("2");
	printf("3");
	printf("4\n");
	void* addr = mm_malloc(1024);
	assert_int_equal(1,2);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test(t1),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
