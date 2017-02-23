objective: high score malloc/free

impl free list -> expl flist -> segregated flist -> more optimzation

more: pro-like development!
    use git to version control!
    pro-like testing
    consistent naming convention
        parameter, local variables use snake_case, 
        and short words and abbreviation

        more permanant thing, use carmelCase.
        function name, struct member name.

*:
    //separate test file mm-test.c

    make my own general purpose test/debug package: kur-test.h, kur-test.c
        TEST(suite,case) cmocka function wrapper macro

        kur-print.c/.h contatins useful print functions.
            on/off kprint(color, flaglist, ...) function macro(colored)
                you can on/off to set the flaglist(global var)

        and kur-test.c/.h 
            include kur-print.h and
            include my helper functions for cmocka 

    //auto-grader: FAIL / SUCCESS

must know:
    how to alloc memory?
        use mem_sbrk(incr)

    how to dealloc memory?
        actually don't free anything unless it call mem_deinit

    this app is -m32. so size of pointer = 4!

    very FIRST RETURN VALUE of mem_sbrk always ALIGNED in 8.
    because it was return value of malloc.

    block header save allocated BLOCK size. not payload size!
    because header exist for implicit free list!!!!!
 
    if mem_sbrk take UNALIGNED size, then it return unaligned size!
    and then every retrun value of mem_sbrk will be UNALIGNED!

read book carefully. and collect Requriements.

//TODO:

1. implicit free list: first, let's see SUCCESS!
    //why my unit test always fail?
        //because not mm_init but TESTER need to call mem_init(). 
    //ret val of malloc(0) must be NULL.

    ret val of malloc must be aligned in 8 byte.
        //지금 헤더를 쓸데 없이 8 byte(2 block)로 잡는 거 같다?
        //헤더를 4 byte로 잡으면 아마 HDRP가 올바른 주소를 잡게되고
        //그러면 GET_SIZE가 0이 안 되서 테스트를 통과할거야.

        //align을 위해서, flist의 가장 앞쪽에 4byte 블럭을 하나 둬야한다.
        //refactor mm_init error handling: Mm_init!

        //write block header correctly.
    implement free -> let's see SUCCESS!

    then mm_malloc SEARCH free list before it allocate new block.

    implement heap checker

    //write getBlockHeaderInfo macros
    write setBlockHeaderInfo macros
        size setter never set allocbit. and vice versa.
        use assert, and check that input size value are aligned by 8
            //need to know test c assertion with cmocka.
            simplify assertion test.

    every setXXX macros(setFooter...) must check input using assert(...)
        and test assertion with unit test!
        also, pack doesn't check input.

    //c assertion test        








