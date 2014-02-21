--
-- VHDL Architecture ece411.Memory.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-01.ews.illinois.edu)
--          at - 17:32:15 01/26/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY Memory IS
   PORT( 
      ADDRESS   : IN     LC3b_word;
      CLK       : IN     STD_LOGIC;
      DATAOUT   : IN     LC3b_word;
      MREAD_L   : IN     std_logic;
      MWRITEH_L : IN     std_logic;
      MWRITEL_L : IN     std_logic;
      RESET_L   : IN     STD_LOGIC;
      DATAIN    : OUT    LC3b_word;
      MRESP_H   : OUT    std_logic
   );

-- Declarations

END Memory ;
