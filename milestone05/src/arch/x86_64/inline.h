#ifndef __INLINE_H__
#define __INLINE_H__

#include <stdint-gcc.h>
#include <stdbool.h>

#define CLI __asm__ volatile ("cli");        // used to disable interrupts
#define STI __asm__ volatile ("sti");        // used to enable interrupts

// Used to load a new Global Descriptor Table
static inline void lgdt(void *base, uint16_t size){
   struct {
      uint16_t length;
      void *base;
   } __attribute__ ((packed)) GDTR;

   GDTR.length = size;
   GDTR.base = base;

   asm ("lgdt %0" : : "m"(GDTR));
}

// Used to load a new Interrupt Descriptor Table
static inline void lidt(void* base, uint16_t size){   
   // This function works in 32 and 64bit mode
    struct {
        uint16_t length;
        void*    base;
    } __attribute__((packed)) IDTR = { size, base };

    asm ( "lidt %0" : : "m"(IDTR) );  // let the compiler choose an addressing mode
}

// Used to reload a new TSS using the TSS Descriptor in the GDT
static inline void ltr(uint16_t offset){
   // offset is the index of the TSS entry in the GDT
   asm ("ltr %0" : : "Nd"(offset));
}

// Port based IO write
static inline void outb(uint16_t port, uint8_t val){
   asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

// Port based IO read
static inline uint8_t inb(uint16_t port){
   uint8_t ret;
   asm volatile ("inb %1, %0"
                     : "=a"(ret)
                     : "Nd"(port));
   return ret;
}

static inline void io_wait(void){
    outb(0x80, 0);
}

static inline bool are_interrupts_enabled()
{
    unsigned long flags;
    asm volatile ( "pushf\n\t"
                   "pop %0"
                   : "=g"(flags) );
    return flags & (1 << 9);
}
                                             //
#endif
