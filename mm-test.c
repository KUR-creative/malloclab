/*
 * my malloc package unit test
 */

// headers for cmocka
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka/cmocka.h>

// headers for my malloc mapckage
#include <stdlib.h>
#include "memlib.h"
#include "mm.h"


// simple [suite__case] function generator
// need to manually insert: (void)state;
#define TEST(suite, name)	\
	static void suite##__##name(void** state)	


static void t1(void** state){
    (void) state; /* unused */

	mem_init(); // it must be called in TESTER!

	void* addr;

	if(mm_init() != -1){	
		addr = mm_malloc(2040);
	}else{
		puts("mm_init failed!");
		exit(1);
	}

	assert_non_null(addr);
	//assert_int_equal(1,2);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(t1),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
