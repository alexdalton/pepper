--
-- VHDL Architecture ece411.BRadd.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-01.ews.illinois.edu)
--          at - 17:51:02 01/26/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY BRadd IS
   PORT( 
      ADJ9out  : IN     LC3b_word;
      PCout    : IN     LC3b_word;
      clk      : IN     std_logic;
      BRaddout : OUT    LC3b_word
   );

-- Declarations

END BRadd ;

--
ARCHITECTURE untitled OF BRadd IS
BEGIN
  BRaddout <= LC3b_word(unsigned(ADJ9out) + unsigned(PCout));
END ARCHITECTURE untitled;

