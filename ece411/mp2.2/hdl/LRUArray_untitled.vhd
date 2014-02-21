--Modification of the example code for the DataArray for LRUArray

LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.NUMERIC_STD.all;

LIBRARY ece411;
USE ece411.LC3b_types.all;

ENTITY LRUArray IS
  PORT(
    RESET_L : IN std_logic;
    LRUWrite : IN std_logic;
    Index : IN LC3b_c_index;
    LRUIn : IN std_logic;
    LRUOut : OUT std_logic
  );
-- Declarations
END LRUArray ;

--
ARCHITECTURE untitled OF LRUArray IS
  SIGNAL LRU : std_logic_vector(7 downto 0);
BEGIN
  --------------------------------------------------------------
  ReadFromLRUArray : PROCESS (LRU, Index)
  --------------------------------------------------------------
  VARIABLE LRUIndex : integer;
  BEGIN
    LRUIndex := to_integer(unsigned(Index));
    LRUOut <= LRU(LRUIndex) after DELAY_256B;
  END PROCESS ReadFromLRUArray;
  --------------------------------------------------------------
  WriteToLRUArray : PROCESS (RESET_L, Index, LRUWrite, LRUIn)
  --------------------------------------------------------------
  VARIABLE LRUIndex : integer;
  BEGIN
    LRUIndex := to_integer(unsigned(Index));
    IF RESET_L = '0' THEN
      LRU(0) <= '0';
      LRU(1) <= '0';
      LRU(2) <= '0';
      LRU(3) <= '0';
      LRU(4) <= '0';
      LRU(5) <= '0';
      LRU(6) <= '0';
      LRU(7) <= '0';
    END IF;
    IF (LRUWrite = '1') THEN
      LRU(LRUIndex) <= LRUIn;
    END IF;
  END PROCESS WriteToLRUArray;
END ARCHITECTURE untitled;