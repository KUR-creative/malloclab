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
	separate test file mm-test.c

	make my own general purpose test/debug package: kur-test.h, kur-test.c
		TEST(suite,case) cmocka function wrapper macro
		on/off kprint(color, flaglist, ...) function macro(colored)
			you can on/off to set the flaglist(global var)

	//auto-grader: FAIL / SUCCESS

must know:
	how to alloc memory?
		use mem_sbrk(incr)

	how to dealloc memory?
		actually don't free anything unless it call mem_deinit

//TODO:

1. implicit free list: first, let's see SUCCESS!
	//why my unit test always fail?
		//because not mm_init but TESTER need to call mem_init(). 








