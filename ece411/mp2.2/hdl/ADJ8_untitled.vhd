--
-- VHDL Architecture ece411.ADJ8.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-03.ews.illinois.edu)
--          at - 23:55:45 02/06/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY ADJ8 IS
   PORT( 
      clk       : IN     std_logic;
      trapvect8 : IN     LC3B_TRAPVECT8;
      zextrap8  : OUT    LC3b_word
   );

-- Declarations

END ADJ8 ;

--
ARCHITECTURE untitled OF ADJ8 IS
BEGIN
  zextrap8 <= "0000000" & trapvect8 & '0';
END ARCHITECTURE untitled;

