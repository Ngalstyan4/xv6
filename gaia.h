#ifndef __ASSEMBLER__
#include "memlayout.h"
#endif

#define PL_USER 3
#define PL_KERN 0

#define HEADER_SIZE 4

#ifndef __ASSEMBLER__
// copy
// Routines to let C code use special GAIA instructions.
static inline uchar
inb(ushort port)
{
  __asm("\
      halt\n\
      mov r2, [rbp+4] \n\
      ld  r1, r2, 0   \n\
      ret             \n\
  ");
}

static inline void
insl(int port, void *addr, int cnt)
{
  __asm("\
      halt\n\
      mov r1, [rbp+4]     \n\
      mov r2, [rbp+8]     \n\
      mov r3, [rbp+12]    \n\
    insl_L1:              \n\
      blt r3, 0, insl_L2  \n\
      sub r3, r3, 1       \n\
      ld  r4, r1, 0       \n\
      st  r4, r2, 0       \n\
      add r2, r2, 4       \n\
      add r3, r3, 4       \n\
      br  insl_L1         \n\
    insl_L2:              \n\
      ret                 \n\
  ");
}

static inline void
outb(ushort port, uchar data)
{
  __asm("\
      halt\n\
      mov r1, [rbp+4]   \n\
      mov r2, [rbp+8]   \n\
      st  r2, r1, 0     \n\
      ret               \n\
  ");
}

static inline void
outw(ushort port, ushort data)
{
  __asm("\
      halt\n\
      mov r1, [rbp+4]   \n\
      mov r2, [rbp+8]   \n\
      st  r2, r1, 0     \n\
      ret               \n\
  ");
}

static inline void
outsl(int port, const void *addr, int cnt)
{
  __asm("\
      halt\n\
      mov r1, [rbp+4]       \n\
      mov r2, [rbp+8]       \n\
      mov r3, [rbp+12]      \n\
    outsl_L1:               \n\
      blt r3, 0, outsl_L2   \n\
      sub r3, r3, 1         \n\
      ld  r4, r2, 0         \n\
      st  r4, r1, 0         \n\
      add r2, r2, 4         \n\
      add r3, r3, 4         \n\
      br  outsl_L1          \n\
    outsl_L2:               \n\
      ret                   \n\
  ");
}

static inline void
stosb(void *addr, int data, int cnt)
{
  int i;
  for (i = 0; i < cnt; i++) {
    *(((char *) addr) + i) = (char) data;
  }
}

static inline void
stosl(void *addr, int data, int cnt)
{
  int i;
  for (i = 0; i < cnt; i++) {
    *(((int *) addr) + i) = data;
  }
}

static inline void
cli(void)
{
  *(int*)INTENABLE = 0;
}

static inline void
sti(void)
{
  *(int*)INTENABLE = 1;
}

// read interrupt flag
static inline uchar
readiflg(void)
{
  return *(int*)INTENABLE;
}


static inline void
setpde(uint val)
{
  *(int*)PDADDR = val;
}

// read trap no
static inline uint
readtrapno()
{
  return *(int*)CAUSE;
}
// read trap return address
static inline uint 
readtreturn()
{
  return *(int*)EPC - 4; // GAIA stores interrupted address + 4.
}

// Layout of the trap frame built on the stack by the
// hardware and by trapasm.S, and passed to trap().
struct trapframe {
  uint privilege;
  // trapno: set in trap.c
  uint trapno;
  uint retaddr;

  // general registers
  uint r31;
  uint r30;
  uint r29;
  uint r28;
  uint r27;
  uint r26;
  uint r25;
  uint r24;
  uint r23;
  uint r22;
  uint r21;
  uint r20;
  uint r19;
  uint r18;
  uint r17;
  uint r16;
  uint r15;
  uint r14;
  uint r13;
  uint r12;
  uint r11;
  uint r10;
  uint r9;
  uint r8;
  uint r7;
  uint r6;
  uint r5;
  uint r4;
  uint r3;
  uint r2;
  uint r1;
};
#endif
