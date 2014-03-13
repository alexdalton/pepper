--
-- VHDL Architecture ece411.feedbackLogic.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-16.ews.illinois.edu)
--          at - 23:04:06 02/19/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY feedbackLogic IS
   PORT( 
      MWRITEH_L : IN     std_logic;
      MWRITEL_L : IN     std_logic;
      read      : OUT    std_logic;
      write     : OUT    std_logic;
      MREAD_L   : IN     std_logic
   );

-- Declarations

END feedbackLogic ;

--
ARCHITECTURE untitled OF feedbackLogic IS
BEGIN
  read  <= NOT(MREAD_L) after DELAY_LOGIC2;
  write <= NOT(MWRITEH_L) or NOT(MWRITEL_L) after DELAY_LOGIC2;
END ARCHITECTURE untitled;

