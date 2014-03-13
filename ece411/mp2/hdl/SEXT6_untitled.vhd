--
-- VHDL Architecture ece411.SEXT6.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-03.ews.illinois.edu)
--          at - 20:03:29 02/06/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY SEXT6 IS
   PORT( 
      clk      : IN     std_logic;
      index6   : IN     LC3b_index6;
      SEXT6out : OUT    LC3b_word
   );

-- Declarations

END SEXT6 ;

--
ARCHITECTURE untitled OF SEXT6 IS
BEGIN
  	SEXT6OUT <= index6(5) & index6(5) & index6(5) & index6(5) & index6(5) & index6(5) & index6(5) & index6(5) & index6(5) & index6(5) & index6 AFTER DELAY_MUX2;
END ARCHITECTURE untitled;

