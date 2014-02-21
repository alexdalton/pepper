--
-- VHDL Architecture ece411.WayMux.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-16.ews.illinois.edu)
--          at - 23:43:35 02/19/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY WayMux IS
   PORT( 
      DataOut0    : IN     LC3b_oword;
      DataOut1    : IN     LC3b_oword;
      DirtyOut0   : IN     std_logic;
      DirtyOut1   : IN     std_logic;
      TagOut0     : IN     LC3B_C_TAG;
      TagOut1     : IN     LC3B_C_TAG;
      TagAND0 : IN     std_logic;
      TagAND1 : IN     std_logic;
      ValidOut0   : IN     std_logic;
      ValidOut1   : IN     std_logic;
      WayMuxData  : OUT    LC3b_oword;
      WayMuxDirty : OUT    std_logic;
      WayMuxTag   : OUT    LC3B_C_TAG;
      WayMuxValid : OUT    std_logic
   );

-- Declarations

END WayMux ;

--
ARCHITECTURE untitled OF WayMux IS
BEGIN
  WayMuxData  <= DataOut0  when TagAND0 = '1' and TagAND1 = '0' else
                 DataOut1  when TagAND1 = '1' and TagAND0 = '0' else
                 (OTHERS => 'X') after delay_MUX2;
                 
  WayMuxDirty <= DirtyOut0 when TagAND0 = '1' and TagAND1 = '0' else
                 DirtyOut1 when TagAND1 = '1' and TagAND0 = '0' else
                 '0' after delay_MUX2;
                 
  WayMuxTag   <= TagOut0   when TagAND0 = '1' and TagAND1 = '0' else
                 TagOut1   when TagAND1 = '1' and TagAND0 = '0' else
                 (OTHERS => 'X') after delay_MUX2;
                 
  WayMuxValid <= ValidOut0 when TagAND0 = '1' and TagAND1 = '0' else
                 ValidOut1 when TagAND1 = '1' and TagAND0 = '0' else
                 '0' after delay_MUX2;
                 
END ARCHITECTURE untitled;

