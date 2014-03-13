echo "--- Executing initialization force file for ../testcode/fivefact.asm ---"

echo "Resetting processor for 5 ns."
force /reset_l 0 @0
force /reset_l 1 @5
echo "Initializing the processor."
force /start_h 0 @0
force /start_h 1 @10

-- Test case: lowering start_h should not impact the function of the processor
force /start_h 0 @ 100

echo "Done initializing processor, loading ../testcode/fivefact.asm program code."
run 5
change /mp2_cpu/dram/vhdl_memory/mem(0) X"0F"
change /mp2_cpu/dram/vhdl_memory/mem(1) X"68"
change /mp2_cpu/dram/vhdl_memory/mem(2) X"10"
change /mp2_cpu/dram/vhdl_memory/mem(3) X"62"
change /mp2_cpu/dram/vhdl_memory/mem(4) X"7F"
change /mp2_cpu/dram/vhdl_memory/mem(5) X"96"
change /mp2_cpu/dram/vhdl_memory/mem(6) X"C1"
change /mp2_cpu/dram/vhdl_memory/mem(7) X"16"
change /mp2_cpu/dram/vhdl_memory/mem(8) X"00"
change /mp2_cpu/dram/vhdl_memory/mem(9) X"13"
change /mp2_cpu/dram/vhdl_memory/mem(10) X"01"
change /mp2_cpu/dram/vhdl_memory/mem(11) X"14"
change /mp2_cpu/dram/vhdl_memory/mem(12) X"03"
change /mp2_cpu/dram/vhdl_memory/mem(13) X"19"
change /mp2_cpu/dram/vhdl_memory/mem(14) X"00"
change /mp2_cpu/dram/vhdl_memory/mem(15) X"1B"
change /mp2_cpu/dram/vhdl_memory/mem(16) X"02"
change /mp2_cpu/dram/vhdl_memory/mem(17) X"02"
change /mp2_cpu/dram/vhdl_memory/mem(18) X"11"
change /mp2_cpu/dram/vhdl_memory/mem(19) X"72"
change /mp2_cpu/dram/vhdl_memory/mem(20) X"FF"
change /mp2_cpu/dram/vhdl_memory/mem(21) X"0F"
change /mp2_cpu/dram/vhdl_memory/mem(22) X"43"
change /mp2_cpu/dram/vhdl_memory/mem(23) X"1B"
change /mp2_cpu/dram/vhdl_memory/mem(24) X"F8"
change /mp2_cpu/dram/vhdl_memory/mem(25) X"0D"
change /mp2_cpu/dram/vhdl_memory/mem(26) X"42"
change /mp2_cpu/dram/vhdl_memory/mem(27) X"12"
change /mp2_cpu/dram/vhdl_memory/mem(28) X"FC"
change /mp2_cpu/dram/vhdl_memory/mem(29) X"0F"
change /mp2_cpu/dram/vhdl_memory/mem(30) X"05"
change /mp2_cpu/dram/vhdl_memory/mem(31) X"00"
change /mp2_cpu/dram/vhdl_memory/mem(32) X"01"
change /mp2_cpu/dram/vhdl_memory/mem(33) X"00"
change /mp2_cpu/dram/vhdl_memory/mem(34) X"00"
change /mp2_cpu/dram/vhdl_memory/mem(35) X"00"
run 5
echo "Done loading ../testcode/fivefact.asm program code."
