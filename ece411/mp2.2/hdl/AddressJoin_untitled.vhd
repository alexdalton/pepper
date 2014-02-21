--
-- VHDL Architecture ece411.AddressJoin.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-16.ews.illinois.edu)
--          at - 01:08:16 02/20/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY AddressJoin IS
   PORT( 
      INDEX        : IN     LC3B_C_INDEX;
      WayMuxTag    : IN     LC3B_C_TAG;
      WriteAddress : OUT    LC3b_word
   );

-- Declarations

END AddressJoin ;

--
ARCHITECTURE untitled OF AddressJoin IS
BEGIN
  WriteAddress <= WayMuxTag & INDEX & "0000";
END ARCHITECTURE untitled;

