@echo off
set xv_path=C:\\XILINX\\Vivado\\2014.4\\bin
call %xv_path%/xelab  -wto 81cf4bd223e3483e8ba2821a4810a767 -m64 --debug typical --relax --maxdelay -L xil_defaultlib -L simprims_ver -L secureip --snapshot tutorial_tb_time_impl -transport_int_delays -pulse_r 0 -pulse_int_r 0 xil_defaultlib.tutorial_tb xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
