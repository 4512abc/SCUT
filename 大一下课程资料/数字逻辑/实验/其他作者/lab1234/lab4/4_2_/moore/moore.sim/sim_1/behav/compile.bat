@echo off
set xv_path=C:\\XILINX\\Vivado\\2014.4\\bin
echo "xvlog -m64 -prj div3_tb_vlog.prj"
call %xv_path%/xvlog  -m64 -prj div3_tb_vlog.prj -log compile.log
if "%errorlevel%"=="1" goto END
if "%errorlevel%"=="0" goto SUCCESS
:END
exit 1
:SUCCESS
exit 0
