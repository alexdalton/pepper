--
-- VHDL Architecture ece411.DRMux.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-03.ews.illinois.edu)
--          at - 23:13:47 02/06/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY DRMux IS
   PORT( 
      DRMuxSel : IN     std_logic;
      clk      : IN     std_logic;
      dest1    : IN     LC3b_reg;
      dest     : OUT    LC3b_reg
   );

-- Declarations

END DRMux ;

--
ARCHITECTURE untitled OF DRMux IS
BEGIN
  dest <= "111" when DRMuxSel = '1' else
           dest1;
           
END ARCHITECTURE untitled;

