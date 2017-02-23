/*
 * my malloc package unit test
 *
 * @t:   write test case vim macro
 * @h,j: get name from test case
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

#define UNIT_TESTING 1

#ifdef UNIT_TESTING
extern void mock_assert(const int result, const char* const expression,
                        const char * const file, const int line);
#undef assert
#define assert(expression) \
    mock_assert((int)(expression), #expression, __FILE__, __LINE__);
#endif


// useful print functions
// they never cast!: DON'T input number that need casting!
#define i32uPRINT(num)      printf("%X ", (num));
#define i64uPRINT(num)      printf("%lX ", (num));

#define i32uPRINTn(num)     printf("%X \n", (num));
#define i64uPRINTn(num)     printf("%lX \n", (num));

#define i32sPRINT(num)      printf("%d ", (num));
#define i64sPRINT(num)      printf("%ld ", (num));

#define i32sPRINTn(num)     printf("%d: \n", (num));
#define i64sPRINTn(num)     printf("%ld: \n", (num));

#define pPRINTn(str,ptr)    printf(str": %p \n",(ptr))
#define dPRINTn(str,num)    printf(str": %d \n",(num))

// simple [suite__case] function generator
// need to manually insert: (void)state;
#define TEST(suite, name)   \
    static void suite##__##name(void** state)\


TEST(macros, getBlockHeaderInfo){
    (void)state;

    //given
    size_t  arr[8]  = { -1, 0x2, 0, };
    void*   baseptr  = (void*)(arr + 1);

    //when
    size_t  size     = GET_SIZE(baseptr);
    size_t  allocBit = IS_ALLOC(baseptr);

    //then
    assert_int_equal( size, (size_t)-1 & ~0x7 );
    assert_int_equal( allocBit, (size_t)-1 & 0x1 );
}

TEST(macros, setBlockHeaderInfo){
    (void)state;
    skip();
    //given
    size_t  old_size     = 8;
    size_t  new_size     = 16;

    size_t  old_allocbit = 0;
    size_t  new_allocbit = 1;
    
    size_t  header       = PACK(old_size, old_allocbit); 
    size_t  arr[8]       = { header, 0, };
    void*   baseptr      = (void*)(arr + 1);

    //when
    SET_SIZE(baseptr, new_size);
        //SET_SIZE must check input validity!

    //then
    assert_int_not_equal(GET_SIZE(baseptr), old_size);
    assert_int_not_equal(IS_ALLOC(baseptr), old_allocbit);

    assert_int_equal(GET_SIZE(baseptr), new_size);
    assert_int_equal(IS_ALLOC(baseptr), new_allocbit);
}

TEST(macros, SET_SIZEdontWriteAllocBit){
    (void)state;
    skip();
    //given
    size_t  old_size  = 8;
    size_t  new_size  = 16;

    size_t  allocbit  = 1;
    
    size_t  header    = PACK(old_size, allocbit); 
    size_t  arr[8]    = { header, 0, };
    void*   baseptr   = (void*)(arr + 1);

    //expect_assert_failure(setAllocWrapper("new_size %% ALIGNMENT == 0",
                //new_size % ALIGNMENT == 0));
    //expect_mock_assert(new_size % ALIGNMENT == 0 && "new_size %% ALIGNMENT == 0" );
    //when
    SET_SIZE(baseptr, new_size);
            dPRINTn("alloc?",IS_ALLOC(baseptr));
    //then
    assert_int_equal(IS_ALLOC(baseptr), allocbit);
}

void setAllocWrapper(void* bp, size_t val){
    SET_ALLOC(bp,val);
    //assert(condition);
}

TEST(macros, ifSET_ALLOC_BITvalIsNot0or1thenAssertionFailed){
    (void)state;
    //given
    size_t  arr[8]  = { -1, 0, };
    void*   baseptr = (void*)(arr + 1);

    //then
    SET_ALLOC(baseptr,0);   //expect NO assertion fail!
    SET_ALLOC(baseptr,1);   //expect NO assertion fail!
    expect_assert_failure( setAllocWrapper(baseptr,2) );
}

void setSizeWrapper(void* bp, size_t size){
    SET_SIZE(bp,size);
}

TEST(macros, ifSET_SIZEvalIsNotAligendThenAssertionFailed){
    (void)state;
    //given
    size_t  arr[8]      = { -1, 0, };
    void*   baseptr     = (void*)(arr + 1);
    size_t  unaligned   = 1;
    size_t  aligned     = 8;

    //then
    SET_SIZE(baseptr, aligned); //expect NO assertion fail!
    expect_assert_failure( setSizeWrapper(baseptr,unaligned) );
}

TEST(malloc, retAdrrMustBeAligned8byte){
    (void)state;
    //skip();

    //given
    void*   addr;
    int32_t remainder;
    Mm_init();

    //when
    addr = mm_malloc(7);

    //then
    assert_non_null(addr);
    remainder = (int32_t)addr % (int32_t)8;
    assert_int_equal(remainder,0);
}

TEST(malloc, argIsZeroThenReturnNULL){
    (void)state;

    //given
    void*   addr;
    Mm_init();

    //when
    addr = mm_malloc(0);
    
    //then
    assert_null(addr);
}


TEST(implicitFreeList, everyBlockSaveSizeInItsHeader){
    (void)state;    
    //skip();
    //given
    void*   base         = NULL;
    size_t  payload_size = 1004; 
    size_t  block_size   = ALIGN(payload_size + WSIZE); 
    Mm_init();

    //when
    base = mm_malloc(payload_size);
    *(int*)base = -1;   // write in payload..
            //dPRINTn("block base word val", GET(base));
            //pPRINTn("       base address", base);
            //pPRINTn("     header address", HDRP(base));
            //dPRINTn("    this block size", GET_SIZE_BITS( HDRP(base) ));
    //then
    int     savedsize = GET_SIZE_BITS( HDRP(base) );
    assert_int_equal(savedsize, block_size);
}

TEST(implicitFreeList, mallocSetsAllocBitInBlockHeaderWhenAllocation){
    (void)state;
    //skip();
    //given
    void*   baseptr      = NULL;
    int     is_allocated = 0;
    char*   headerptr; 
    Mm_init();

    //when
    baseptr = mm_malloc(123);

    //then
    headerptr = HDRP(baseptr);
    is_allocated = GET_ALLOC_BIT(headerptr);
    assert_int_equal(is_allocated, 1);
}

TEST(implicitFreeList, mm_initInsertAlignBlockInFronOfFreeList){
    (void)state;
    //given
    void*   oldmem_brk  = NULL;
    void*   mem_brk     = NULL;
    int32_t remainder4  = 1;

    oldmem_brk = mem_sbrk(0);  // it return now mem_brk.

    //when
    Mm_init();  // mm_init have to increment mem_brk!
    mem_brk = mem_sbrk(0);  

    //then
        //pPRINTn("mem_brk",mem_brk);
        //i32uPRINTn(mem_brk);
    remainder4 = (int32_t)mem_brk % (int32_t)4;
    assert_int_equal(remainder4, 0);

    int32_t oldaddr = (int32_t)oldmem_brk;
    int32_t nowaddr = (int32_t)mem_brk;
    assert_int_equal(oldaddr+WSIZE, nowaddr);
}

TEST(implicitFreeList, mm_freeSetHeaderAllocBitZero){
    (void)state;
    skip();
    //given
    Mm_init();
    void*   baseptr      = mm_malloc(1023);
    size_t  old_allocbit = IS_ALLOC(baseptr);
 
    //when
    mm_free(baseptr);
    size_t  new_allocbit = IS_ALLOC(baseptr);

    //then
    assert_int_not_equal(old_allocbit, new_allocbit);
    assert_int_equal(new_allocbit, 0);
}

static int setUp(void** state){
    mem_init();// it must be called in TESTER!
    //printf("  mem_brk = %p is already aligned? why? \n", mem_sbrk(0));
    return 0;
}

static int tearDown(void** state){
    mem_reset_brk();
    mem_deinit();
    return 0;
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(macros__getBlockHeaderInfo),
        cmocka_unit_test(macros__setBlockHeaderInfo),
        cmocka_unit_test(macros__ifSET_ALLOC_BITvalIsNot0or1thenAssertionFailed),
        cmocka_unit_test(macros__ifSET_SIZEvalIsNotAligendThenAssertionFailed),
        cmocka_unit_test(macros__SET_SIZEdontWriteAllocBit),
        cmocka_unit_test_setup_teardown(malloc__retAdrrMustBeAligned8byte, setUp, tearDown),
        cmocka_unit_test_setup_teardown(malloc__argIsZeroThenReturnNULL, setUp, tearDown),
        // implicit free list
        cmocka_unit_test_setup_teardown(implicitFreeList__everyBlockSaveSizeInItsHeader, setUp, tearDown),
        cmocka_unit_test_setup_teardown(implicitFreeList__mallocSetsAllocBitInBlockHeaderWhenAllocation, setUp, tearDown),
        cmocka_unit_test_setup_teardown(implicitFreeList__mm_initInsertAlignBlockInFronOfFreeList, setUp, tearDown),
        cmocka_unit_test_setup_teardown(implicitFreeList__mm_freeSetHeaderAllocBitZero, setUp, tearDown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
