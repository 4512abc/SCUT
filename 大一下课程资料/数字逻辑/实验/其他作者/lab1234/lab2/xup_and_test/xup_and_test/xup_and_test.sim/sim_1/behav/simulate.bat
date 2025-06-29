@echo off
set xv_path=C:\\XILINX\\Vivado\\2014.4\\bin
call %xv_path%/xsim xup_and_tb_behav -key {Behavioral:sim_1:Functional:xup_and_tb} -tclbatch xup_and_tb.tcl -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
