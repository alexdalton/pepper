SEGMENT  CodeSegment:
   LDR  R1, R0, VAL1   ; R1 <= 1	
   LDR  R2, R0, VAL2   ; R2 <= 5
   LDR  R3, R0, VAL3   ; R3 <= 31	
        
   ADD R4, R3, R2	   ; R4 <= R3 + R2
   ADD R5, R4, 6       ; R5 <= R4 + 6 
   ADD R6, R5, -8      ; R6 <= R5 -8
   STR R4, R0, RESULT1
   STR R5, R0, RESULT2
   STR R6, R0, RESULT3

   AND R3, R3, R2      ; R3 <= R3 & R2
   AND R3, R3, 7       ; R3 <= R3 & 7
   STR R3, R0, RESULT4
                        

HALT:
    BRnzp HALT
VAL1:	DATA2 4x0001
VAL2:	DATA2 4x0005
VAL3:	DATA2 4x001F
GOOD:	DATA2 4x600D
BAD:    DATA2 4x0BAD
RESULT1:	DATA2 4x0000
RESULT2:	DATA2 4x0000
RESULT3:	DATA2 4x0000
RESULT4:	DATA2 4x0000

