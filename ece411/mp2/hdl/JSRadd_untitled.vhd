--
-- VHDL Architecture ece411.JSRadd.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-03.ews.illinois.edu)
--          at - 20:32:51 02/06/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY JSRadd IS
   PORT( 
      ADJ11out  : IN     LC3B_word;
      clk       : IN     std_logic;
      PCout     : IN     LC3b_word;
      JSRaddout : OUT    LC3b_word
   );

-- Declarations

END JSRadd ;

--
ARCHITECTURE untitled OF JSRadd IS
BEGIN
  JSRaddout <= LC3b_word(unsigned(ADJ11out) + unsigned(PCout));
END ARCHITECTURE untitled;

