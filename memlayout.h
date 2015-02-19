// Memory layout

#define EXTMEM   0x3000             // Start of extended memory
#define PHYSTOP  (4*1024*1024)      // Top physical memory
#define DEVSPACE 0xFE000000         // Other devices are at high addresses

// Key addresses for address space layout (see kmap in vm.c for layout)
#define KERNBASE 0x80000000         // First kernel virtual address
#define KERNLINK (KERNBASE+EXTMEM)  // Address where kernel is linked

//
#define VAENABLE   0x2200
#define PDEADDR    0x2204
#define INTHANDLER 0x2100
#define INTENABLE  0x2104
#define EPC        0x2108
#define CAUSE      0x210C
#define SERIAL     0x2000

#ifndef __ASSEMBLER__
#ifndef V2P_P2V
#define V2P_P2V

static inline uint v2p(void *a) { return ((uint) (a))  - KERNBASE; }
static inline void *p2v(uint a) { return (void *) ((a) + KERNBASE); }

#endif
#endif

#define V2P(a) (((uint) (a)) - KERNBASE)
#define P2V(a) ((void*)((uint)(a) + KERNBASE))

#define V2P_WO(x) ((x) - KERNBASE)    // same as V2P, but without casts
#define P2V_WO(x) ((x) + KERNBASE)    // same as V2P, but without casts
