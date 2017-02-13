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

#define UNIT_TESTING 1

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
		addr = mm_malloc(1001);
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
	void*	addr;
	if(mm_init() != -1){	
		addr = mm_malloc(0);
	}else{
		puts("mm_init failed!");
		exit(1);
	}

	//then
	assert_null(addr);
}


TEST(implicitFreeList, everyBlockSaveSizeInItsHeader){
	(void)state;	
	//skip();
	//given
	void*	base = NULL;
	size_t	size = 1024;

	//when
	if(mm_init() != -1){	
		base = mm_malloc(size);
	}else{
		puts("mm_init failed!");
		exit(1);
	}
				*(int*)base = -1;	// write in payload..
				printf("out malloc %d \n", GET(base));
				printf("out malloc %d \n", GET_SIZE( HDRP(base) ));
	//then
	int		savedsize = GET_SIZE( HDRP(base) );
	assert_int_equal(savedsize, size);
}

TEST(implicitFreeList, mallocSetsAllocBitInBlockHeaderWhenAllocation){
	(void)state;
	skip();
	//given
	void*	baseptr			= NULL;
	int		is_allocated	= 0;

	//when
	if(mm_init() != -1){	
		baseptr = mm_malloc(123);
	}else{
		puts("mm_init failed!");
		exit(1);
	}

	//then
	is_allocated = GET_ALLOC(baseptr);
	assert_true(is_allocated);
}
static int setUp(void** state){
	mem_init();// it must be called in TESTER!
	puts("	setup");
	return 0;
}

static int tearDown(void** state){
	mem_reset_brk();
	mem_deinit();
	puts("	teardown");
	return 0;
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(malloc__retAdrrMustBeAligned8byte, setUp, tearDown),
		cmocka_unit_test_setup_teardown(malloc__argIsZeroThenReturnNULL, setUp, tearDown),
		// implicit free list
		cmocka_unit_test_setup_teardown(implicitFreeList__everyBlockSaveSizeInItsHeader, setUp, tearDown),
		cmocka_unit_test_setup_teardown(implicitFreeList__mallocSetsAllocBitInBlockHeaderWhenAllocation, setUp, tearDown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
