    ; Program calculates the value of 5!
SEGMENT CodeSegment:
    ; R4 is variable that holds multiplicand
    LDR R4, R0, FIVE         ; R4 <= 5

    ; Set R3 to -1 this will be used to decrement in loops
    LDR R1, R0, ONE          ; R1 <= 1
    NOT R3, R1               ; R3 <= not(R1)
    ADD R3, R3, R1           ; R3 <= R3 + R1

    ; R1 is the variable that will hold the result of each
    ; multiplication
    ADD R1, R4, R0           ; R1 <= R4 + R0 (R1 <= 5)

; outer loop that iteratively calculates factorial
LOOP1:
    ; R2 is the variable that will hold the return value from
    ; the MULTIPLY loop (R1)
    ADD R2, R0, R1             ; R2 <= R0 + R1
    ADD R4, R4, R3             ; R4 <= R4 - 1
    ADD R5, R4, R0             ; R5 <= R4 + R0
    ; R5 now holds the multiplicand and R2 the multiplier
    ; Branch to multiply loop
    BRp MULTIPLY
    ; Factorial calculated store in RESULT
    STR R1, R0, RESULT

; Infinitely loop
HALT:
    BRnzp HALT

; loop that simply performs R1 = R2 * R5
MULTIPLY:
    ADD R5, R5, R3             ; R5 <= R5 - 1
    BRnz LOOP1                 ; no more additions need be performed

    ADD R1, R1, R2             ; R1 <= R1 + R2
    BRnzp MULTIPLY

 

FIVE:   DATA2 4x0005         ; constant = 5
ONE:    DATA2 4x0001         ; constant = 1
RESULT: DATA2 4x0000         ; place holder for result
