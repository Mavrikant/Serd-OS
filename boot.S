.section ".text.boot" // Make sure the linker puts this at the start of the kernel image
.global _start // Execution starts here
	
_start:
	// Check processor ID is zero (executing on main core), else hang
	mrs x0, mpidr_el1
	and x0, x0, #3
	cmp x0, #0
	beq kernel_entry
	// We're not on the main core, so hang in an infinite wait loop
end:
	b end
	
kernel_entry:
	mrs x0, CurrentEl
	lsr x0, x0, #2
	cmp x0, #2
	bne end
	
	msr sctlr_el1, xzr
	mov x0, #(1 << 31)
	msr hcr_el2, x0
	
	mov x0, #0b1111000101
	msr spsr_el2, x0
	
	adr x0, el1_entry
	msr elr_el2, x0
	
	eret
	
el1_entry:
	ldr x1, =_start 	// Set stack to start below our code
	mov sp, x1
	
	// Clean the BSS section
	ldr x1, =__bss_start // Start address
	ldr w2, =__bss_size // Size of the section
loop: 
    cbz w2, kernel_main // Quit loop if zero
	str xzr, [x1], #8
	sub w2, w2, #1
	cbnz w2, loop // Loop if non - zero
	
kernel_main:
	ldr x0, = vector_table
	msr vbar_el1, x0
	
	bl Serd_OS_main //Jump to our Serd_OS_main() routine in C (make sure it doesn't return)
	
	b end //In case it does return, halt the master core too
