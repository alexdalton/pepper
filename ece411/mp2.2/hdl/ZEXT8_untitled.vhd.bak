--
-- VHDL Architecture ece411.ZEXT8.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-03.ews.illinois.edu)
--          at - 00:35:22 02/07/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY ZEXT8 IS
   PORT( 
      byteOut  : IN     LC3b_byte;
      clk      : IN     std_logic;
      ZEXT8Out : OUT    LC3b_word
   );

-- Declarations

END ZEXT8 ;

--
ARCHITECTURE untitled OF ZEXT8 IS
BEGIN
  ZEXT8Out <= "00000000" & byteOut;
END ARCHITECTURE untitled;

