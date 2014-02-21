--
-- VHDL Architecture ece411.WordMux8.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-03.ews.illinois.edu)
--          at - 23:48:35 02/06/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY WordMux8 IS
   PORT( 
      A   : IN     lc3b_word;
      B   : IN     lc3b_word;
      C   : IN     lc3b_word;
      D   : IN     lc3b_word;
      E   : IN     lc3b_word;
      F   : IN     lc3b_word;
      G   : IN     lc3b_word;
      H   : IN     lc3b_word;
      Sel : IN     lc3b_8mux_sel;
      I   : OUT    lc3b_word
   );

-- Declarations

END WordMux8 ;

--
ARCHITECTURE untitled OF WordMux8 IS
BEGIN
  I <= A when sel = "000" else
       B when sel = "001" else
       C when sel = "010" else
       D when sel = "011" else
       E when sel = "100" else
       F when sel = "101" else
       G when sel = "110" else
       H after DELAY_MUX8;
       
END ARCHITECTURE untitled;

