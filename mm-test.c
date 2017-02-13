/*
 * my malloc package unit test
 *
 * @t: write test case vim macro
 * @h: get name from test case
 *
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
	static void suite##__##name(void** state)\


TEST(malloc, retAdrrMustBeAligned8byte){
	(void)state;

	void* addr;

	if(mm_init() != -1){	
		addr = mm_malloc(2040);
	}else{
		puts("mm_init failed!");
		exit(1);
	}

	assert_non_null(addr);
	assert_true( ((int32_t)addr % (int32_t)8 == 0) );
}

TEST(malloc, argIsZeroThenReturnNULL){
	(void)state;

	//given
	void* addr;
	if(mm_init() != -1){	
		addr = mm_malloc(0);
	}else{
		puts("mm_init failed!");
		exit(1);
	}

	//then
	assert_null(addr);
}

static int setUp(void** state){
	mem_init();// it must be called in TESTER!
	return 0;
}

static int tearDown(void** state){
	mem_reset_brk();
	mem_deinit();
	return 0;
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(malloc__retAdrrMustBeAligned8byte),
		cmocka_unit_test(malloc__argIsZeroThenReturnNULL),
    };
    return cmocka_run_group_tests(tests, setUp, tearDown);
}
