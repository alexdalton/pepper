--
-- VHDL Architecture ece411.StoreMux.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-01.ews.illinois.edu)
--          at - 17:54:48 01/26/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY StoreMux IS
   PORT( 
      SrcA        : IN     LC3b_reg;
      StoreSR     : IN     lc3b_4MUX_SEL;
      clk         : IN     std_logic;
      StoreMuxout : OUT    LC3b_reg;
      dest1       : IN     LC3b_reg
   );

-- Declarations

END StoreMux ;

--
ARCHITECTURE untitled OF StoreMux IS
BEGIN
  StoreMuxout <= dest1 when StoreSR = "00" else
                 SrcA when StoreSR = "01";
END ARCHITECTURE untitled;

