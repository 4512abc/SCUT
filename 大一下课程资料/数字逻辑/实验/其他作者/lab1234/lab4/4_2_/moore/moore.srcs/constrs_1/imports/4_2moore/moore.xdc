set_property PACKAGE_PIN V17 [get_ports {ain[0]}]	
set_property IOSTANDARD LVCMOS33 [get_ports {ain[0]}]

set_property PACKAGE_PIN V16 [get_ports {ain[1]}]	
set_property IOSTANDARD LVCMOS33 [get_ports {ain[1]}]

set_property PACKAGE_PIN U16 [get_ports yout]
set_property IOSTANDARD LVCMOS33 [get_ports yout]

set_property PACKAGE_PIN T18 [get_ports reset]
set_property IOSTANDARD LVCMOS33 [get_ports reset]

set_property PACKAGE_PIN R2 [get_ports clk]
set_property IOSTANDARD LVCMOS33 [get_ports clk]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets {clk}]	