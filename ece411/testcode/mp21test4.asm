SEGMENT  CodeSegment:	
   LDR R1, R0, LDI1     ; R1 <= x600d
   LDR R2, R0, LDI2     ; R2 <= x600e
   LDR R3, R0, LDI3     ; R3 <= x600f

   LEA R4, RES4     ; R4 <= Address(RES4)
   LEA R5, RES5     ; R5 <= Address(RES5)
   LEA R6, RES6     ; R6 <= Address(RES6)

   STR R4, R0, RES1  ; RES1 <= Address(RES4)
   STR R5, R0, RES2  ; RES2 <= Address(RES5)
   STR R6, R0, RES3  ; RES3 <= Address(RES6)

   STI R1, R0, RES1  ; RES4 <= R1
   STI R2, R0, RES2  ; RES5 <= R2
   STI R3, R0, RES3  ; RES6 <= R3

   LDI R4, R0, RES1  ; R4 <= x600d
   LDI R5, R0, RES2  ; R5 <= x600e
   LDI R6, R0, RES3  ; R6 <= x600f
   
HALT: BRnzp HALT

LDI1:   DATA2 4x600D
LDI2:   DATA2 4x600E
LDI3:   DATA2 4x600F

RES1:   DATA2 4x0000
RES2:   DATA2 4x0000
RES3:   DATA2 4x0000

RES4:   DATA2 4x0000
RES5:   DATA2 4x0000
RES6:   DATA2 4x0000



