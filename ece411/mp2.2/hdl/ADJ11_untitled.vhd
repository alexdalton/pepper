--
-- VHDL Architecture ece411.ADJ11.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-03.ews.illinois.edu)
--          at - 20:26:03 02/06/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY ADJ11 IS
   PORT( 
      clk      : IN     std_logic;
      offset11 : IN     LC3B_OFFSET11;
      ADJ11out : OUT    LC3B_word
   );

-- Declarations

END ADJ11 ;

--
ARCHITECTURE untitled OF ADJ11 IS
BEGIN
    	ADJ11OUT <= offset11(10) & offset11(10) & offset11(10) & offset11(10)& offset11 & '0' AFTER DELAY_MUX2;
END ARCHITECTURE untitled;

