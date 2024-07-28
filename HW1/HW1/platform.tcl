# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\FPGA\HW1\HW1\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\FPGA\HW1\HW1\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {HW1}\
-hw {D:\FPGA\self\design_1_wrapper.xsa}\
-proc {microblaze_0} -os {standalone} -out {D:/FPGA/HW1}

platform write
platform generate -domains 
platform active {HW1}
platform generate
