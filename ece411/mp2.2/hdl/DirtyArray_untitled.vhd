--Modification of the example code for the DataArray for DirtyArray

LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY DirtyArray IS
  PORT(
    RESET_L : IN std_logic;
    DirtyWrite : IN std_logic;
    Index : IN LC3b_c_index;
    DirtyIn  : IN std_logic;
    DirtyOut : OUT std_logic
    );
-- Declarations
END DirtyArray ;

--
ARCHITECTURE untitled OF DirtyArray IS
  SIGNAL Dirty : std_logic_vector(7 downto 0);
BEGIN
  --------------------------------------------------------------
  ReadFromDirtyArray : PROCESS (Dirty, Index)
  --------------------------------------------------------------
  VARIABLE DirtyIndex : integer;
  BEGIN
    DirtyIndex := to_integer(unsigned(Index));
    DirtyOut <= Dirty(DirtyIndex) after DELAY_256B;
  END PROCESS ReadFromDirtyArray;
  --------------------------------------------------------------
  WriteToDirtyArray : PROCESS (RESET_L, Index, DirtyWrite, DirtyIn)
  --------------------------------------------------------------
  VARIABLE DirtyIndex : integer;
  BEGIN
    DirtyIndex := to_integer(unsigned(Index));
    IF RESET_L = '0' THEN
      Dirty(0) <= '0';
      Dirty(1) <= '0';
      Dirty(2) <= '0';
      Dirty(3) <= '0';
      Dirty(4) <= '0';
      Dirty(5) <= '0';
      Dirty(6) <= '0';
      Dirty(7) <= '0';
    END IF;
    IF (DirtyWrite = '1') THEN
      Dirty(DirtyIndex) <= DirtyIn;
    END IF;
  END PROCESS WriteToDirtyArray;
END ARCHITECTURE untitled;