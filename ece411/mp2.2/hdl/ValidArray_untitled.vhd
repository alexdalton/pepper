--Modification of the example code for the DataArray for ValidArray

LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY ValidArray IS
  PORT(
    RESET_L : IN std_logic;
    ValidWrite : IN std_logic;
    Index : IN LC3b_c_index;
    ValidOut : OUT std_logic
  );
-- Declarations
END ValidArray ;

--
ARCHITECTURE untitled OF ValidArray IS
  SIGNAL Valid : std_logic_vector(7 downto 0);
BEGIN
  --------------------------------------------------------------
  ReadFromValidArray : PROCESS (Valid, Index)
  --------------------------------------------------------------
  VARIABLE ValidIndex : integer;
  BEGIN
    ValidIndex := to_integer(unsigned(Index));
    ValidOut <= Valid(ValidIndex) after DELAY_256B;
  END PROCESS ReadFromValidArray;
  --------------------------------------------------------------
  WriteToValidArray : PROCESS (RESET_L, Index, ValidWrite)
  --------------------------------------------------------------
  VARIABLE ValidIndex : integer;
  BEGIN
    ValidIndex := to_integer(unsigned(Index));
    IF RESET_L = '0' THEN
      Valid(0) <= '0';
      Valid(1) <= '0';
      Valid(2) <= '0';
      Valid(3) <= '0';
      Valid(4) <= '0';
      Valid(5) <= '0';
      Valid(6) <= '0';
      Valid(7) <= '0';
    END IF;
    IF (ValidWrite = '1') THEN
      Valid(ValidIndex) <= '1';
    END IF;
  END PROCESS WriteToValidArray;
END ARCHITECTURE untitled;