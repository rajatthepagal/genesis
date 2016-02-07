#ifndef KERNEL_DESCRIPTORS_H
#define KERNEL_DESCRIPTORS_H
#include <stdint.h>
//#include "include/stdtypes.h"
/*Define GDT table
 * limit lower 0-15	 	  16bit
 * base lower field 0-15   	  16bit
 * base midle 16-23	  	   8bit
 * Access flag : Ring level,prvlg  8bit
 * limit 16-19 			   4bit
 * flag 4bit gr,d_size,00	   4bit
 * base high :last 8 bit	   8bit
 */
struct gdt_entry{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	/* access : 7,65,4,3,2,1,0 bits
	 * 7  : Present bit ,must be 1 for valid selector.
	 * 65 : privillage -> ring0,ring1,ring2
	 * 4  : set to 1.
	 * 3  : 1 if executable(code), 0 for data
	 * 2  : Direcrion bit or confirming bit.
	 * 1  : R/W C/D
	 * 0  :Access, set to 0, cpu set its to 1 when data is accessed
	 * */
	uint8_t access;
	uint8_t limit_up:4;
	uint8_t flags:4;
	uint8_t base_high;
} __attribute__((packed));

typedef struct gdt_entry gdt_t;

/* 32 bit address of base and selector 
 * to register our gdt
 * Attributes:
 * 	Upper 16 bit of selector limit(gdt_t-->limit_low;
 * 	Address of first gdt table.
 * */
typedef struct{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

// public accessible func to setup gdt entry
void init_gdt();
#endif /*DESCRIPTORS_H */
