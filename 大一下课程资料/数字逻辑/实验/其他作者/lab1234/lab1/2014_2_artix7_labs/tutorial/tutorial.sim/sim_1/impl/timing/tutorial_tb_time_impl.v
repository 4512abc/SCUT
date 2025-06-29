// Copyright 1986-2014 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2014.4 (win64) Build 1071353 Tue Nov 18 18:24:04 MST 2014
// Date        : Sun May 07 23:29:13 2023
// Host        : LAPTOP-I9ARGKMK running 64-bit major release  (build 9200)
// Command     : write_verilog -mode timesim -nolib -sdf_anno true -force -file
//               C:/XILINX/homework/2014_2_artix7_labs/tutorial/tutorial.sim/sim_1/impl/timing/tutorial_tb_time_impl.v
// Design      : design_1_wrapper
// Purpose     : This verilog netlist is a timing simulation representation of the design and should not be modified or
//               synthesized. Please ensure that this netlist is used with the corresponding SDF file.
// Device      : xc7a35tcpg236-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps
`define XIL_TIMING

module design_1
   (LD0,
    LD1,
    LD2,
    LD3,
    LD4,
    LD5,
    LD6,
    LD7,
    SW0,
    SW1,
    SW2,
    SW3,
    SW4,
    SW5,
    SW6,
    SW7);
  output LD0;
  output LD1;
  output LD2;
  output LD3;
  output LD4;
  output LD5;
  output LD6;
  output LD7;
  input SW0;
  input SW1;
  input SW2;
  input SW3;
  input SW4;
  input SW5;
  input SW6;
  input SW7;

  wire LD0;
  wire LD1;
  wire LD2;
  wire LD3;
  wire SW0;
  wire SW1;
  wire SW2;
  wire SW3;
  wire SW4;
  wire SW5;
  wire SW6;
  wire SW7;
  wire xup_inv_1_y;

  assign LD4 = SW4;
  assign LD5 = SW5;
  assign LD6 = SW6;
  assign LD7 = SW7;
(* CHECK_LICENSE_TYPE = "design_1_xup_and2_0_1,xup_and2,{}" *) 
   (* CORE_GENERATION_INFO = "design_1_xup_and2_0_1,xup_and2,{x_ipProduct=Vivado 2014.4,x_ipVendor=xilinx.com,x_ipLibrary=xup,x_ipName=xup_and2,x_ipVersion=1.0,x_ipCoreRevision=1,x_ipLanguage=VERILOG,x_ipSimLanguage=VERILOG,DELAY=3}" *) 
   (* DowngradeIPIdentifiedWarnings = "yes" *) 
   (* X_CORE_INFO = "xup_and2,Vivado 2014.4" *) 
   design_1_xup_and2_0_1 xup_and2_0
       (.a(SW1),
        .b(xup_inv_1_y),
        .y(LD1));
(* CHECK_LICENSE_TYPE = "design_1_xup_and2_0_2,xup_and2,{}" *) 
   (* CORE_GENERATION_INFO = "design_1_xup_and2_0_2,xup_and2,{x_ipProduct=Vivado 2014.4,x_ipVendor=xilinx.com,x_ipLibrary=xup,x_ipName=xup_and2,x_ipVersion=1.0,x_ipCoreRevision=1,x_ipLanguage=VERILOG,x_ipSimLanguage=VERILOG,DELAY=3}" *) 
   (* DowngradeIPIdentifiedWarnings = "yes" *) 
   (* X_CORE_INFO = "xup_and2,Vivado 2014.4" *) 
   design_1_xup_and2_0_2 xup_and2_1
       (.a(SW2),
        .b(SW3),
        .y(LD3));
(* CHECK_LICENSE_TYPE = "design_1_xup_inv_0_1,xup_inv,{}" *) 
   (* CORE_GENERATION_INFO = "design_1_xup_inv_0_1,xup_inv,{x_ipProduct=Vivado 2014.4,x_ipVendor=xilinx.com,x_ipLibrary=xup,x_ipName=xup_inv,x_ipVersion=1.0,x_ipCoreRevision=1,x_ipLanguage=VERILOG,x_ipSimLanguage=VERILOG,DELAY=3}" *) 
   (* DowngradeIPIdentifiedWarnings = "yes" *) 
   (* X_CORE_INFO = "xup_inv,Vivado 2014.4" *) 
   design_1_xup_inv_0_1 xup_inv_0
       (.a(SW0),
        .y(LD0));
(* CHECK_LICENSE_TYPE = "design_1_xup_inv_0_2,xup_inv,{}" *) 
   (* CORE_GENERATION_INFO = "design_1_xup_inv_0_2,xup_inv,{x_ipProduct=Vivado 2014.4,x_ipVendor=xilinx.com,x_ipLibrary=xup,x_ipName=xup_inv,x_ipVersion=1.0,x_ipCoreRevision=1,x_ipLanguage=VERILOG,x_ipSimLanguage=VERILOG,DELAY=3}" *) 
   (* DowngradeIPIdentifiedWarnings = "yes" *) 
   (* X_CORE_INFO = "xup_inv,Vivado 2014.4" *) 
   design_1_xup_inv_0_2 xup_inv_1
       (.a(SW2),
        .y(xup_inv_1_y));
(* CHECK_LICENSE_TYPE = "design_1_xup_or2_0_1,xup_or2,{}" *) 
   (* CORE_GENERATION_INFO = "design_1_xup_or2_0_1,xup_or2,{x_ipProduct=Vivado 2014.4,x_ipVendor=xilinx.com,x_ipLibrary=xup,x_ipName=xup_or2,x_ipVersion=1.0,x_ipCoreRevision=1,x_ipLanguage=VERILOG,x_ipSimLanguage=VERILOG,DELAY=3}" *) 
   (* DowngradeIPIdentifiedWarnings = "yes" *) 
   (* X_CORE_INFO = "xup_or2,Vivado 2014.4" *) 
   design_1_xup_or2_0_1 xup_or2_0
       (.a(LD1),
        .b(LD3),
        .y(LD2));
endmodule

(* ECO_CHECKSUM = "41e4b2" *) 
(* NotValidForBitStream *)
module design_1_wrapper
   (LD0,
    LD1,
    LD2,
    LD3,
    LD4,
    LD5,
    LD6,
    LD7,
    SW0,
    SW1,
    SW2,
    SW3,
    SW4,
    SW5,
    SW6,
    SW7);
  output LD0;
  output LD1;
  output LD2;
  output LD3;
  output LD4;
  output LD5;
  output LD6;
  output LD7;
  input SW0;
  input SW1;
  input SW2;
  input SW3;
  input SW4;
  input SW5;
  input SW6;
  input SW7;

  wire LD0;
  wire LD0_OBUF;
  wire LD1;
  wire LD1_OBUF;
  wire LD2;
  wire LD2_OBUF;
  wire LD3;
  wire LD3_OBUF;
  wire LD4;
  wire LD4_OBUF;
  wire LD5;
  wire LD5_OBUF;
  wire LD6;
  wire LD6_OBUF;
  wire LD7;
  wire LD7_OBUF;
  wire SW0;
  wire SW0_IBUF;
  wire SW1;
  wire SW1_IBUF;
  wire SW2;
  wire SW2_IBUF;
  wire SW3;
  wire SW3_IBUF;
  wire SW4;
  wire SW4_IBUF;
  wire SW5;
  wire SW5_IBUF;
  wire SW6;
  wire SW6_IBUF;
  wire SW7;
  wire SW7_IBUF;

initial begin
 $sdf_annotate("tutorial_tb_time_impl.sdf",,,,"tool_control");
end
OBUF LD0_OBUF_inst
       (.I(LD0_OBUF),
        .O(LD0));
OBUF LD1_OBUF_inst
       (.I(LD1_OBUF),
        .O(LD1));
OBUF LD2_OBUF_inst
       (.I(LD2_OBUF),
        .O(LD2));
OBUF LD3_OBUF_inst
       (.I(LD3_OBUF),
        .O(LD3));
OBUF LD4_OBUF_inst
       (.I(LD4_OBUF),
        .O(LD4));
OBUF LD5_OBUF_inst
       (.I(LD5_OBUF),
        .O(LD5));
OBUF LD6_OBUF_inst
       (.I(LD6_OBUF),
        .O(LD6));
OBUF LD7_OBUF_inst
       (.I(LD7_OBUF),
        .O(LD7));
IBUF SW0_IBUF_inst
       (.I(SW0),
        .O(SW0_IBUF));
IBUF SW1_IBUF_inst
       (.I(SW1),
        .O(SW1_IBUF));
IBUF SW2_IBUF_inst
       (.I(SW2),
        .O(SW2_IBUF));
IBUF SW3_IBUF_inst
       (.I(SW3),
        .O(SW3_IBUF));
IBUF SW4_IBUF_inst
       (.I(SW4),
        .O(SW4_IBUF));
IBUF SW5_IBUF_inst
       (.I(SW5),
        .O(SW5_IBUF));
IBUF SW6_IBUF_inst
       (.I(SW6),
        .O(SW6_IBUF));
IBUF SW7_IBUF_inst
       (.I(SW7),
        .O(SW7_IBUF));
design_1 design_1_i
       (.LD0(LD0_OBUF),
        .LD1(LD1_OBUF),
        .LD2(LD2_OBUF),
        .LD3(LD3_OBUF),
        .LD4(LD4_OBUF),
        .LD5(LD5_OBUF),
        .LD6(LD6_OBUF),
        .LD7(LD7_OBUF),
        .SW0(SW0_IBUF),
        .SW1(SW1_IBUF),
        .SW2(SW2_IBUF),
        .SW3(SW3_IBUF),
        .SW4(SW4_IBUF),
        .SW5(SW5_IBUF),
        .SW6(SW6_IBUF),
        .SW7(SW7_IBUF));
endmodule

(* X_CORE_INFO = "xup_and2,Vivado 2014.4" *) (* CHECK_LICENSE_TYPE = "design_1_xup_and2_0_1,xup_and2,{}" *) (* CORE_GENERATION_INFO = "design_1_xup_and2_0_1,xup_and2,{x_ipProduct=Vivado 2014.4,x_ipVendor=xilinx.com,x_ipLibrary=xup,x_ipName=xup_and2,x_ipVersion=1.0,x_ipCoreRevision=1,x_ipLanguage=VERILOG,x_ipSimLanguage=VERILOG,DELAY=3}" *) 
(* DowngradeIPIdentifiedWarnings = "yes" *) 
module design_1_xup_and2_0_1
   (a,
    b,
    y);
  input a;
  input b;
  output y;

  wire a;
  wire b;
  wire y;

LUT2 #(
    .INIT(4'h8)) 
     y_INST_0
       (.I0(a),
        .I1(b),
        .O(y));
endmodule

(* X_CORE_INFO = "xup_and2,Vivado 2014.4" *) (* CHECK_LICENSE_TYPE = "design_1_xup_and2_0_2,xup_and2,{}" *) (* CORE_GENERATION_INFO = "design_1_xup_and2_0_2,xup_and2,{x_ipProduct=Vivado 2014.4,x_ipVendor=xilinx.com,x_ipLibrary=xup,x_ipName=xup_and2,x_ipVersion=1.0,x_ipCoreRevision=1,x_ipLanguage=VERILOG,x_ipSimLanguage=VERILOG,DELAY=3}" *) 
(* DowngradeIPIdentifiedWarnings = "yes" *) 
module design_1_xup_and2_0_2
   (a,
    b,
    y);
  input a;
  input b;
  output y;

  wire a;
  wire b;
  wire y;

LUT2 #(
    .INIT(4'h8)) 
     y_INST_0
       (.I0(a),
        .I1(b),
        .O(y));
endmodule

(* X_CORE_INFO = "xup_inv,Vivado 2014.4" *) (* CHECK_LICENSE_TYPE = "design_1_xup_inv_0_1,xup_inv,{}" *) (* CORE_GENERATION_INFO = "design_1_xup_inv_0_1,xup_inv,{x_ipProduct=Vivado 2014.4,x_ipVendor=xilinx.com,x_ipLibrary=xup,x_ipName=xup_inv,x_ipVersion=1.0,x_ipCoreRevision=1,x_ipLanguage=VERILOG,x_ipSimLanguage=VERILOG,DELAY=3}" *) 
(* DowngradeIPIdentifiedWarnings = "yes" *) 
module design_1_xup_inv_0_1
   (a,
    y);
  input a;
  output y;

  wire a;
  wire y;

LUT1 #(
    .INIT(2'h1)) 
     y_INST_0
       (.I0(a),
        .O(y));
endmodule

(* X_CORE_INFO = "xup_inv,Vivado 2014.4" *) (* CHECK_LICENSE_TYPE = "design_1_xup_inv_0_2,xup_inv,{}" *) (* CORE_GENERATION_INFO = "design_1_xup_inv_0_2,xup_inv,{x_ipProduct=Vivado 2014.4,x_ipVendor=xilinx.com,x_ipLibrary=xup,x_ipName=xup_inv,x_ipVersion=1.0,x_ipCoreRevision=1,x_ipLanguage=VERILOG,x_ipSimLanguage=VERILOG,DELAY=3}" *) 
(* DowngradeIPIdentifiedWarnings = "yes" *) 
module design_1_xup_inv_0_2
   (a,
    y);
  input a;
  output y;

  wire a;
  wire y;

LUT1 #(
    .INIT(2'h1)) 
     y_INST_0
       (.I0(a),
        .O(y));
endmodule

(* X_CORE_INFO = "xup_or2,Vivado 2014.4" *) (* CHECK_LICENSE_TYPE = "design_1_xup_or2_0_1,xup_or2,{}" *) (* CORE_GENERATION_INFO = "design_1_xup_or2_0_1,xup_or2,{x_ipProduct=Vivado 2014.4,x_ipVendor=xilinx.com,x_ipLibrary=xup,x_ipName=xup_or2,x_ipVersion=1.0,x_ipCoreRevision=1,x_ipLanguage=VERILOG,x_ipSimLanguage=VERILOG,DELAY=3}" *) 
(* DowngradeIPIdentifiedWarnings = "yes" *) 
module design_1_xup_or2_0_1
   (a,
    b,
    y);
  input a;
  input b;
  output y;

  wire a;
  wire b;
  wire y;

LUT2 #(
    .INIT(4'hE)) 
     y_INST_0
       (.I0(a),
        .I1(b),
        .O(y));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (weak1, weak0) GSR = GSR_int;
    assign (weak1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
