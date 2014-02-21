onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /mp2_cpu/DRAM/PDRAM/PMADDRESS
add wave -noupdate /mp2_cpu/DRAM/PDRAM/PMDATAIN
add wave -noupdate /mp2_cpu/DRAM/PDRAM/PMREAD_L
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/ADDRESS
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/TAG
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/INDEX
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/OFFSET
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/ValidOut0
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/DirtyOut0
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/TagOut0
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/DataOut0
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/ValidOut1
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/DirtyOut1
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/TagOut1
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/DataOut1
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/hit
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/read
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/write
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/TagisEqual0
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/TagisEqual1
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/TagAND0
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/TagAND1
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/MREAD_L
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/WayMuxTag
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/WayMuxData
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/WayMuxValid
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/WayMuxDirty
add wave -noupdate /mp2_cpu/DATAIN
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/Way0Write
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/Way1Write
add wave -noupdate /mp2_cpu/DRAM/Cache_DP/MRESP_H
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {784 ns} 0}
quietly wave cursor active 1
configure wave -namecolwidth 294
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {695 ns} {887 ns}
