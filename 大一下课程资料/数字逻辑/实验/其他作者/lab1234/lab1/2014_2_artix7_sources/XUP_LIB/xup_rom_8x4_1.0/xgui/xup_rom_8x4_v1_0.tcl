#Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
	set Page0 [ ipgui::add_page $IPINST  -name "Page 0" -layout vertical]
	set Component_Name [ ipgui::add_param  $IPINST  -parent  $Page0  -name Component_Name ]
	set rom_content [ipgui::add_param $IPINST -parent $Page0 -name rom_content]
	set DELAY [ipgui::add_param $IPINST -parent $Page0 -name DELAY ]
}

proc update_PARAM_VALUE.rom_content { PARAM_VALUE.rom_content } {
	# Procedure called to update rom_content when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.rom_content { PARAM_VALUE.rom_content } {
	# Procedure called to validate rom_content
	return true
}

proc update_PARAM_VALUE.DELAY { PARAM_VALUE.DELAY } {
	# Procedure called to update DELAY when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.DELAY { PARAM_VALUE.DELAY } {
	# Procedure called to validate DELAY
	return true
}


proc update_MODELPARAM_VALUE.DELAY { MODELPARAM_VALUE.DELAY PARAM_VALUE.DELAY } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.DELAY}] ${MODELPARAM_VALUE.DELAY}
}

proc update_MODELPARAM_VALUE.rom_content { MODELPARAM_VALUE.rom_content PARAM_VALUE.rom_content } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.rom_content}] ${MODELPARAM_VALUE.rom_content}
}

