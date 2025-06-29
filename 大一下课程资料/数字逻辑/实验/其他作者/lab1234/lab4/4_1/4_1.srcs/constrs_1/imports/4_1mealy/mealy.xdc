set_property PACKAGE_PIN W18 [get_ports {count[0]}]	
set_property IOSTANDARD LVCMOS33 [get_ports {count[0]}]

set_property PACKAGE_PIN U15 [get_ports {count[1]}]	
set_property IOSTANDARD LVCMOS33 [get_ports {count[1]}]

set_property PACKAGE_PIN U14 [get_ports {count[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {count[2]}]

set_property PACKAGE_PIN V14 [get_ports {count[3]}]	
set_property IOSTANDARD LVCMOS33 [get_ports {count[3]}]


set_property PACKAGE_PIN U16 [get_ports yout]
set_property IOSTANDARD LVCMOS33 [get_ports yout]

set_property PACKAGE_PIN V17 [get_ports ain]
set_property IOSTANDARD LVCMOS33 [get_ports ain]

set_property PACKAGE_PIN T18 [get_ports reset]
set_property IOSTANDARD LVCMOS33 [get_ports reset]

set_property PACKAGE_PIN R2 [get_ports clk]
set_property IOSTANDARD LVCMOS33 [get_ports clk]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets {clk}]		