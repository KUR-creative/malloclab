#include <stdio.h>
#include <assert.h>

extern int      mm_init(void);
extern void*    mm_malloc(size_t size);
extern void     mm_free(void* ptr);
extern void*    mm_realloc(void* ptr, size_t size);
//mine
extern void     Mm_init(void);
#define WSIZE       4
#define DSIZE       8

/* single word (4) or double word (8) alignment */
#define ALIGNMENT   8

/* Pack a size and allocated bit int a word */
#define PACK(size, alloc)   ((size) | (alloc))

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size)     (((size) + (ALIGNMENT-1)) & ~0x7)

/* Read and write a word at address p */
#define GET(p)          (*(unsigned int*)(p)) 
#define PUT(p, val)     (*(unsigned int*)(p) = (val))

/* Read the size and allocated fields from addres's p (NOT from HEAD!)*/
#define GET_SIZE_BITS(p)    (GET(p) & ~0x7)
#define GET_ALLOC_BIT(p)    (GET(p) & 0x1) 

/* Get the size and allocated fields from baseptr's HEADER */
#define GET_SIZE(bp)    GET_SIZE_BITS( HDRP(bp) )
#define IS_ALLOC(bp)    GET_ALLOC_BIT( HDRP(bp) )

/* Set block size 
 * NOTE: size must be ALIGNED! */
#define SET_SIZE(bp, size)  do{                            \
                                assert(size % ALIGNMENT == 0);   \
                            }while(0);
//PUT(HDRP(bp), size);

#define SET_ALLOC(bp,val)   do{                                 \
                                assert(val == 0 || val == 1);   \
                            }while(0);
                                    

/* Ginven block ptr bp, compute address of its header and footer*/
#define HDRP(bp)        ((char*)(bp) - WSIZE)

#define SIZE_T_SIZE     (ALIGN(sizeof(size_t)))

/* 
 * Students work in teams of one or two.  Teams enter their team name, 
 * personal names and login IDs in a struct of this
 * type in their bits.c file.
 */
typedef struct {
    char*   teamname; /* ID1+ID2 or ID1 */
    char*   name1;    /* full name of first member */
    char*   id1;      /* login ID of first member */
    char*   name2;    /* full name of second member (if any) */
    char*   id2;      /* login ID of second member */
} team_t;

extern team_t team;
   
