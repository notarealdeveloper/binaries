ENTRY(_start)
SECTIONS {

    . = 0x004000b0;

    .text : {
        * (.text);
    }

    . = 0x006000cc;

    .data : {
        * (.data);
    }

    _edata = .; PROVIDE (edata = .);
    __bss_start = .;

   .bss : {
        * (.bss);
    }

    _end = .; PROVIDE (end = .);
}
