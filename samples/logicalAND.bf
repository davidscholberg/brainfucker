Brainfuck implementation of logical AND

specifically:
    if a and b are both greater than zero then increment c

memory layout:
    | a | b | check flag | extra 0^b | extra 0^a | if a flag | if b flag | c |
    ==========================================================================
     0   1   2            3           4           5           6           7
    
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
[
    >
    [       this block will only be entered if a and b are both greater than 0
        >
        +++++ +++++ +++++ +++++ +++++ +++++ +++++ +++++ +++++ +++++ +++++ ++++
        <
        -
    ]
    <
    -
]
