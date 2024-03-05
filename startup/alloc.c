#include <stdlib.h>
#include "alloc.h"

typedef struct _Header Header;

struct _Header {
	struct _Header *	next;
};

#define SIZE(p) 	((char*)((unsigned int)p->next & (~1)) - (char*)(p) - sizeof(Header))
#define NEXT(p)		((Header*)((unsigned int)p->next & (~1)))
#define IS_FREE(p)	(((unsigned int)p->next & 1)==0)
#define IS_BUSY(p)  ((unsigned int)p->next & 1)
#define SET_FREE(p)	((unsigned int)p->next &= (~1))
#define SET_BUSY(p)	((unsigned int)p->next |= 1)

extern char __heap_start[];
extern char __heap_end[];


//	memory allocator init
void minit()
{
    Header *ps = (Header*)__heap_start;
    Header *pe = (Header*)(__heap_end-sizeof(Header));
    
    ps->next = pe;
    pe->next = (Header*)1;
}

void* malloc(unsigned int req)
{
    if (req) {
        req = 4*(((req-1)/4)+1);
        Header* p = (Header*)__heap_start;
	
		while (p) {
			if (IS_FREE(p)) {
				unsigned int s=SIZE(p);
				if ((s == req) || (s == req + sizeof(Header))) {	// prefer exact requested size or allocate an extra 4 bytes (can't do anything with it)
					p->next=(Header*)((unsigned int)p->next | 1);
					return (void*)((char*)p+sizeof(Header));
				}
				if (s >= req + 2*sizeof(Header)) {				// else get a bigger one
					Header *nh=(Header*)((char*)p+req+sizeof(Header));			// allocate a new header
					nh->next=p->next;
					p->next=(Header*)((unsigned int)nh | 1);								// bit0==1 ==> busy
					return (void*)((char*)p+sizeof(Header));
				}
			}
			p = NEXT(p);
		}
	}
    return NULL;
}

void free(void* mem)
{
	Header *p=(Header*)__heap_start;
	Header *p1=NULL;
	if (mem) {
		// find the block and set it free
		while (p!=NULL) {
			if ((char*)mem==(char*)p+sizeof(Header)) {
				p->next = (Header*)((unsigned int)p->next & (~1));
				break;
			}
			p1=p;
			p=NEXT(p);
		}
		if (p) {
			// try to merge blocks forward
			if (IS_FREE(p) && IS_FREE(NEXT(p))) {
				Header *p2 = NEXT(p);
				p->next=NEXT(p)->next;
				p2->next=(Header*)0xCCCCCCFF;

			}
			// try to merge blocks backward
			if (p1 && IS_FREE(p1)) {
				p1->next=p->next;
				p->next=(Header*)0xCCCCCCBB;
			}

		}
	}
}


