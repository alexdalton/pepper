--
-- VHDL Architecture ece411.TagCompare.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-31.ews.illinois.edu)
--          at - 21:58:28 02/13/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY TagCompare IS
  PORT(
    TagA : IN LC3B_C_TAG;
    TagB : IN LC3B_C_TAG;
    isEqual : OUT std_logic
  );
END ENTITY TagCompare;

--
ARCHITECTURE untitled OF TagCompare IS
BEGIN
  isEqual <= '1' when (to_integer(unsigned(TagA)) = to_integer(unsigned(TagB))) else
             '0' after DELAY_COMPARE16;
END ARCHITECTURE untitled;

