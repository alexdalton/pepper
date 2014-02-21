--
-- VHDL Architecture ece411.ZEXT4.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-03.ews.illinois.edu)
--          at - 19:19:39 02/06/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY ZEXT4 IS
   PORT( 
      clk      : IN     std_logic;
      imm4     : IN     LC3b_nibble;
      ZEXT4Out : OUT    LC3b_word
   );

-- Declarations

END ZEXT4 ;

--
ARCHITECTURE untitled OF ZEXT4 IS
BEGIN
  ZEXT4Out <= "000000000000" & imm4;
END ARCHITECTURE untitled;

