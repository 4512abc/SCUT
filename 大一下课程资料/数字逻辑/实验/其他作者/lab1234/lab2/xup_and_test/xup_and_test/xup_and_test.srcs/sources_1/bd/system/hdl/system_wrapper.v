//Copyright 1986-2014 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2014.4 (win64) Build 1071353 Tue Nov 18 18:24:04 MST 2014
//Date        : Fri May 12 00:11:11 2023
//Host        : LAPTOP-I9ARGKMK running 64-bit major release  (build 9200)
//Command     : generate_target system_wrapper.bd
//Design      : system_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module system_wrapper
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

  wire a;
  wire [2:0]a_1;
  wire b;
  wire [2:0]b_1;
  wire y;
  wire [2:0]y_1;

system system_i
       (.a(a),
        .a_1(a_1),
        .b(b),
        .b_1(b_1),
        .y(y),
        .y_1(y_1));
endmodule
