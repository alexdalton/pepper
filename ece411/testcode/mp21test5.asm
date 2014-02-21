SEGMENT  CodeSegment:	
    ADD R1, R0, 1

    LDB R2, R0, VAL1   ; R2 <= Lowbyte Val1
    LDB R3, R1, VAL1   ; R3 <= Highbyte Val1

    LDB R4, R0, VAL2   ; R4 <= Lowbyte Val2
    LDB R5, R1, VAL2   ; R5 <= Highbyte Val2
    
    LEA R1, RES1   ; R1 <= Address(RES1)
    STB R3, R1, 0      ; RES1(lowbyte) <= R3
    STB R2, R1, 1      ; RES1(highbyte) <= R2

    LEA R1, RES2   ; R1 <= Address(RES2)
    STB R5, R1, 0      ; RES2(lowbyte) <= R5
    STB R4, R1, 1      ; RES2(highbyte) <= R4

    LDR R1, R0, RES1   ; R1 <= Mem(RES1) = 0D61
    LDR R2, R0, RES2   ; R2 <= Mem(RES2) = 0E62
     
   
HALT: BRnzp HALT

VAL1:   DATA2 4x610D
VAL2:   DATA2 4x620E
RES1:   DATA2 4x0000
RES2:   DATA2 4x0000



