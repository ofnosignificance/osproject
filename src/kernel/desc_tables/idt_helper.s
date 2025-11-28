extern _int_handler

%macro global_int 1
    %rep %0
        global int%1
    %endrep 
%endmacro

%macro part_int 1
    %rep %0
        cli
        push byte 0
        push byte %1
        jmp _int_handler
    %endrep
%endmacro

global_int 31
part_int 31

