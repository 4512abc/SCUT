@echo off
set xv_path=C:\\XILINX\\Vivado\\2014.4\\bin
call %xv_path%/xsim tutorial_tb_behav -key {Behavioral:sim_1:Functional:tutorial_tb} -tclbatch tutorial_tb.tcl -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
