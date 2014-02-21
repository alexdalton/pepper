--
-- VHDL Architecture ece411.LRUDecode.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-31.ews.illinois.edu)
--          at - 22:32:41 02/13/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY LRUDecode IS
   PORT( 
      LRUOut    : IN     std_logic;
      Way0Write : OUT    STD_LOGIC;
      Way1Write : OUT    STD_LOGIC;
      LD_Cache  : IN     std_logic;
      LRUIn     : OUT    STD_LOGIC;
      TagAND0   : IN     std_logic;
      TagAND1   : IN     std_logic
   );

-- Declarations

END LRUDecode ;

--
ARCHITECTURE untitled OF LRUDecode IS
BEGIN
  Way0Write <= '1' when (LRUOut = '0' and LD_Cache = '1') else '0' after delay_decode3;
  Way1Write <= '1' when (LRUOut = '1' and LD_Cache = '1') else '0' after delay_decode3;
  LRUIn <= '1' when TagAND0 = '1' and TagAND1 = '0' else
           '0' when TagAND0 = '0' and TagAND1 = '1' else
           '0' after delay_decode3;
END ARCHITECTURE untitled;

