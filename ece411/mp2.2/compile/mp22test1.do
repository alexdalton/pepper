echo "--- Executing initialization force file for ../testcode/mp22test1.asm ---"

echo "Resetting processor for 5 ns."
force /reset_l 0 @0
force /reset_l 1 @5
echo "Initializing the processor."
force /start_h 0 @0
force /start_h 1 @10

-- Test case: lowering start_h should not impact the function of the processor
force /start_h 0 @ 100

echo "Done initializing processor, loading ../testcode/mp22test1.asm program code."
run 5
change /mp2_cpu/dram/pdram/vhdl_memory/mem(0) X"06"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(1) X"62"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(2) X"08"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(3) X"64"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(4) X"09"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(5) X"66"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(6) X"81"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(7) X"12"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(8) X"83"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(9) X"12"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(10) X"C4"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(11) X"12"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(12) X"01"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(13) X"00"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(14) X"02"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(15) X"00"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(16) X"03"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(17) X"00"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(18) X"04"
change /mp2_cpu/dram/pdram/vhdl_memory/mem(19) X"00"
run 5
echo "Done loading ../testcode/mp22test1.asm program code."
