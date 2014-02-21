--
-- VHDL Architecture ece411.LD_align.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-03.ews.illinois.edu)
--          at - 00:36:23 02/07/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY LD_align IS
   PORT( 
      ADDRESS : IN     LC3b_word;
      MDROUT  : IN     LC3b_word;
      clk     : IN     std_logic;
      HighLow : OUT    std_logic;
      byteOut : OUT    LC3b_byte
   );

-- Declarations

END LD_align ;

--
ARCHITECTURE untitled OF LD_align IS
BEGIN
  byteOut <= MDROUT(15 downto 8) when ADDRESS(0) = '1' else
             MDROUT(7 downto 0);
  HighLow <= ADDRESS(0);
END ARCHITECTURE untitled;

