echo "--- Executing initialization force file for ../testcode/mp21test5.asm ---"

echo "Resetting processor for 5 ns."
force /reset_l 0 @0
force /reset_l 1 @5
echo "Initializing the processor."
force /start_h 0 @0
force /start_h 1 @10

-- Test case: lowering start_h should not impact the function of the processor
force /start_h 0 @ 100

echo "Done initializing processor, loading ../testcode/mp21test5.asm program code."
run 5
change /mp2_cpu/dram/vhdl_memory/mem(0) X"21"
change /mp2_cpu/dram/vhdl_memory/mem(1) X"12"
change /mp2_cpu/dram/vhdl_memory/mem(2) X"1C"
change /mp2_cpu/dram/vhdl_memory/mem(3) X"24"
change /mp2_cpu/dram/vhdl_memory/mem(4) X"5C"
change /mp2_cpu/dram/vhdl_memory/mem(5) X"26"
change /mp2_cpu/dram/vhdl_memory/mem(6) X"1E"
change /mp2_cpu/dram/vhdl_memory/mem(7) X"28"
change /mp2_cpu/dram/vhdl_memory/mem(8) X"5E"
change /mp2_cpu/dram/vhdl_memory/mem(9) X"2A"
change /mp2_cpu/dram/vhdl_memory/mem(10) X"0A"
change /mp2_cpu/dram/vhdl_memory/mem(11) X"E2"
change /mp2_cpu/dram/vhdl_memory/mem(12) X"40"
change /mp2_cpu/dram/vhdl_memory/mem(13) X"36"
change /mp2_cpu/dram/vhdl_memory/mem(14) X"41"
change /mp2_cpu/dram/vhdl_memory/mem(15) X"34"
change /mp2_cpu/dram/vhdl_memory/mem(16) X"08"
change /mp2_cpu/dram/vhdl_memory/mem(17) X"E2"
change /mp2_cpu/dram/vhdl_memory/mem(18) X"40"
change /mp2_cpu/dram/vhdl_memory/mem(19) X"3A"
change /mp2_cpu/dram/vhdl_memory/mem(20) X"41"
change /mp2_cpu/dram/vhdl_memory/mem(21) X"38"
change /mp2_cpu/dram/vhdl_memory/mem(22) X"10"
change /mp2_cpu/dram/vhdl_memory/mem(23) X"62"
change /mp2_cpu/dram/vhdl_memory/mem(24) X"11"
change /mp2_cpu/dram/vhdl_memory/mem(25) X"64"
change /mp2_cpu/dram/vhdl_memory/mem(26) X"FF"
change /mp2_cpu/dram/vhdl_memory/mem(27) X"0F"
change /mp2_cpu/dram/vhdl_memory/mem(28) X"0D"
change /mp2_cpu/dram/vhdl_memory/mem(29) X"61"
change /mp2_cpu/dram/vhdl_memory/mem(30) X"0E"
change /mp2_cpu/dram/vhdl_memory/mem(31) X"62"
change /mp2_cpu/dram/vhdl_memory/mem(32) X"00"
change /mp2_cpu/dram/vhdl_memory/mem(33) X"00"
change /mp2_cpu/dram/vhdl_memory/mem(34) X"00"
change /mp2_cpu/dram/vhdl_memory/mem(35) X"00"
run 5
echo "Done loading ../testcode/mp21test5.asm program code."
