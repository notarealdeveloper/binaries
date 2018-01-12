ENTRY(the_beginning)
SECTIONS {
    . = 0xc0de0000;
    .code : {
        * (.code)
    }
    . = 0xdada0000;
    .vars : {
        * (.vars)
    }
}
