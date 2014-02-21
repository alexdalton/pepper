--
-- VHDL Architecture ece411.ADJ5.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-01.ews.illinois.edu)
--          at - 17:34:43 01/26/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY SEXT5 IS
   PORT( 
      clk      : IN     std_logic;
      imm5     : IN     LC3b_imm5;
      SEXT5out : OUT    LC3b_word
   );

-- Declarations

END SEXT5 ;

--
ARCHITECTURE UNTITLED OF SEXT5 IS
BEGIN
	SEXT5OUT <= IMM5(4) & IMM5(4) & IMM5(4) & IMM5(4) & IMM5(4) & IMM5(4) & IMM5(4) & IMM5(4) & IMM5(4) & IMM5(4) & IMM5(4) & IMM5 AFTER DELAY_MUX2;
END UNTITLED;


