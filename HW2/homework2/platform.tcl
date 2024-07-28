# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\FPGA\HW2\homework2\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\FPGA\HW2\homework2\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {homework2}\
-hw {D:\FPGA\self\design_2_wrapper.xsa}\
-proc {microblaze_0} -os {standalone} -out {D:/FPGA/HW2}

platform write
platform generate -domains 
platform active {homework2}
platform generate
