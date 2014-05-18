Brainfuck implementation of logical OR

specifically:
    if a or b or both are both greater than zero then increment c

memory layout:
    | a | b | check flag | extra 0^b | extra 0^a | if a flag | if b flag |
    ======================================================================
     0   1   2            3           4           5           6
     
    | if a or b flag | c |
    ======================
     7                8
    
+++++       initialize a
>
++          initialize b
>
+           set check flag which is used to exit check blocks
<<
[
    >>>>>
    +       set "a greater than 0" flag
    <<<
    -       exit check block
]
>>
[           if a is 0 then this block will bring the data pointer to the
    -       same location it would be if a was greater than 0
    >>
]
<<
+
<
[
    >>>>>
    +       set "b greater than 0" flag
    <<<<
    -       exit check block
]
>
[           if b is 0 then this block will bring the data pointer to the
    -       same location it would be if b was greater than 0
    >
]
>>
[           if a is greater than 0 set ab flag and unset b flag if set
    >>
    +
    <
    [
        -
    ]
    <
    -
]
>
[           if b is greater than 0 then set ab flag
    >
    +
    <
    -
]
>
[           this block is only entered if a or b or both are greater than 0
    >
    +++++ +
    <
    -
]
