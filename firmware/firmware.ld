/**
 * Linker script for the KE04 device
 */

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_startup)


MEMORY
{
    sram(WX) : ORIGIN = 0x1FFFFF00, LENGTH = 1K
    flash : org = 0x00000000, len = 6k
}

/**
 * The top of the stack is the end of SRAM
 */
TOTAL_RESERVED_STACK = 128; /* On a system with 64K ram, we saw 8K used */
_top_stack = (0x1fffff00+1K);

EXTERN(__interrupt_vector_table);

SECTIONS
{
    .flashonly :
    {
        __interrupt_vector_table = .;
        *(.interrupt_vector_table)
        *(.unsecured_config)
        . = ALIGN(4);
        *(.startup)
        /* Rest of the code */
        *(.text)
        *(.text.*)
        *(.glue_7)
        *(.glue_7t)
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
    } > flash

    .flash_at_rest_ram_at_run :
    {
        . = ALIGN(4);
        _start_data = .;
        *(.data)
        *(.data.*)
        *(.shdata)
        _end_data = .;
    } > sram AT>flash

    .ram_only :
    {
        . = ALIGN(4);
        _start_bss = .;
        *(.bss)
        *(.bss.*)
        _end_bss = .;
    } > sram

    _bss_size = _end_bss - _start_bss;
    /* TODO: Copy DATA section into RAM */
    _data_size = _end_data - _start_data;
    _data_flash_addr = LOADADDR(.flash_at_rest_ram_at_run);

    _start_stack = _top_stack - TOTAL_RESERVED_STACK;
    _top_stack = _top_stack;			/* just to make the map file easier to read */
}
