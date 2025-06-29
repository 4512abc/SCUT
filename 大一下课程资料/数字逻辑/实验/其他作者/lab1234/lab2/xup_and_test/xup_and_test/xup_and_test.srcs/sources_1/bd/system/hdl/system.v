//Copyright 1986-2014 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2014.4 (win64) Build 1071353 Tue Nov 18 18:24:04 MST 2014
//Date        : Fri May 12 00:11:11 2023
//Host        : LAPTOP-I9ARGKMK running 64-bit major release  (build 9200)
//Command     : generate_target system.bd
//Design      : system
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module system
   (a,
    a_1,
    b,
    b_1,
    y,
    y_1);
  input a;
  input [2:0]a_1;
  input b;
  input [2:0]b_1;
  output y;
  output [2:0]y_1;

  wire \^a_1 ;
  wire [2:0]a_1_1;
  wire \^b_1 ;
  wire [2:0]b_1_1;
  wire xup_and2_0_y;
  wire [2:0]xup_and_vector_0_y;

  assign \^a_1  = a;
  assign \^b_1  = b;
  assign a_1_1 = a_1[2:0];
  assign b_1_1 = b_1[2:0];
  assign y = xup_and2_0_y;
  assign y_1[2:0] = xup_and_vector_0_y;
system_xup_and2_0_0 xup_and2_0
       (.a(\^a_1 ),
        .b(\^b_1 ),
        .y(xup_and2_0_y));
system_xup_and_vector_0_0 xup_and_vector_0
       (.a(a_1_1),
        .b(b_1_1),
        .y(xup_and_vector_0_y));
endmodule
