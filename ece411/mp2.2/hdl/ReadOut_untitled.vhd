--
-- VHDL Architecture ece411.ReadOut.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-31.ews.illinois.edu)
--          at - 23:20:47 02/13/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY ReadOut IS
   PORT( 
      Data16Out : IN     LC3b_word;
      MREAD_L   : IN     std_logic;
      OROut     : IN     std_logic;
      DATAIN    : OUT    LC3b_word;
      MRESP_H   : OUT    std_logic
   );

-- Declarations

END ReadOut ;

--
ARCHITECTURE untitled OF ReadOut IS
BEGIN
  -- TODO
END ARCHITECTURE untitled;

