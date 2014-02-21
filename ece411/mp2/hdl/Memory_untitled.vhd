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
      DATAOUT   : IN     LC3b_word;
      MREAD_L   : IN     std_logic;
      MWRITEH_L : IN     std_logic;
      MWRITEL_L : IN     std_logic;
      RESET_L   : IN     std_logic;
      clk       : IN     std_logic;
      DATAIN    : OUT    LC3b_word;
      MRESP_H   : OUT    std_logic
   );

-- Declarations

END Memory ;

--
ARCHITECTURE UNTITLED OF MEMORY IS
SIGNAL PRE_MRESP_H : STD_LOGIC;
SIGNAL PRE_DATAIN : LC3B_WORD;
BEGIN
  -------------------------------------------------------------------
  VHDL_MEMORY : PROCESS (RESET_L, MREAD_L, MWRITEH_L, MWRITEL_L) 
  -------------------------------------------------------------------
  VARIABLE MEM : MEMORY_ARRAY_64K;
  VARIABLE INT_ADDRESS : INTEGER;
  BEGIN
    INT_ADDRESS := TO_INTEGER(UNSIGNED('0' & ADDRESS(11 DOWNTO 1) & '0'));
  
    -- Reset
    IF (RESET_L = '0') THEN
      PRE_MRESP_H <= '0';
      MYDRAMINIT_64K(MEM);
    ELSE
      -- Read
      IF (MREAD_L = '0' AND MWRITEL_L = '1' AND MWRITEH_L = '1') THEN
        PRE_DATAIN(7 DOWNTO 0)  <= MEM(INT_ADDRESS);
        PRE_DATAIN(15 DOWNTO 8) <= MEM(INT_ADDRESS + 1);
        PRE_MRESP_H <= '1' AFTER 0 NS, '0' AFTER CLOCK_PERIOD;
      
      -- Write
      ELSIF ((MWRITEL_L = '0' OR MWRITEH_L = '0') AND MREAD_L = '1') THEN

        -- Write low byte
        IF (MWRITEL_L = '0') THEN
          MEM(INT_ADDRESS) := DATAOUT(7 DOWNTO 0);
        END IF;

        -- Write high byte
        IF (MWRITEH_L = '0') THEN
          MEM(INT_ADDRESS + 1) := DATAOUT(15 DOWNTO 8);
        END IF;
        PRE_MRESP_H <= '1' AFTER 0 NS, '0' AFTER CLOCK_PERIOD;
      END IF;
    END IF;
  END PROCESS VHDL_MEMORY;

  MRESP_H <= PRE_MRESP_H'DELAYED(DELAY_MP2_MEM);
  DATAIN <= PRE_DATAIN'DELAYED(DELAY_MP2_MEM);
END ARCHITECTURE untitled;

