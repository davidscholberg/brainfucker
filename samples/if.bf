Brainfuck implementation of an if statement

specifically:
    if a is greater than zero then increment b

memory layout:
    | a | check flag | extra 0 | greater than flag | b |
    ====================================================
     0   1            2         3
    
+++++       initialize a
>
+           set check flag which is used to exit check block
<
[
    >>>
    +       set "greater than" flag
    <<
    -       exit check block
]
>
[           if a is 0 then this block will bring the data pointer to the
    -       same location it would be if a was greater than 0
    >
]
>
[           this block will only be entered if a is greater than 0
    >
    +++++ +++++ +++++ +++++ +++++ +++++ ++
    <
    -
]
