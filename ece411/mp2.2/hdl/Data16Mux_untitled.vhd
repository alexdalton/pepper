--
-- VHDL Architecture ece411.Data16Mux.untitled
--
-- Created:
--          by - adalton2.ews (gelib-057-31.ews.illinois.edu)
--          at - 23:17:17 02/13/14
--
-- using Mentor Graphics HDL Designer(TM) 2012.1 (Build 6)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY Data16Mux IS
   PORT( 
      WayMuxData : IN     LC3b_oword;
      OFFSET     : IN     LC3B_C_OFFSET;
      DATAIN     : OUT    LC3b_word
   );

-- Declarations

END Data16Mux ;

--
ARCHITECTURE untitled OF Data16Mux IS
BEGIN
  PROCESS (WayMuxData, OFFSET)
    variable state : LC3b_word;
  BEGIN
    case OFFSET(3 downto 1) is
      when "000" =>
        state := WayMuxData(15 downto 0);
      when "001" =>
        state := WayMuxData(31 downto 16);
      when "010" =>
        state := WayMuxData(47 downto 32);
      when "011" =>
        state := WayMuxData(63 downto 48);
      when "100" =>
        state := WayMuxData(79 downto 64);
      when "101" =>
        state := WayMuxData(95 downto 80);
      when "110" =>
        state := WayMuxData(111 downto 96);
      when "111" =>
        state := WayMuxData(127 downto 112);
      when others =>
        state := (OTHERS => 'X');
    end case;
    DATAIN <= state after delay_MUX8;
  END PROCESS;
END ARCHITECTURE untitled;

