//Copyright 1986-2014 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2014.4 (win64) Build 1071353 Tue Nov 18 18:24:04 MST 2014
//Date        : Sun May 07 21:14:08 2023
//Host        : LAPTOP-I9ARGKMK running 64-bit major release  (build 9200)
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

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
  wire LD1;
  wire LD2;
  wire LD3;
  wire LD4;
  wire LD5;
  wire LD6;
  wire LD7;
  wire SW0;
  wire SW1;
  wire SW2;
  wire SW3;
  wire SW4;
  wire SW5;
  wire SW6;
  wire SW7;

design_1 design_1_i
       (.LD0(LD0),
        .LD1(LD1),
        .LD2(LD2),
        .LD3(LD3),
        .LD4(LD4),
        .LD5(LD5),
        .LD6(LD6),
        .LD7(LD7),
        .SW0(SW0),
        .SW1(SW1),
        .SW2(SW2),
        .SW3(SW3),
        .SW4(SW4),
        .SW5(SW5),
        .SW6(SW6),
        .SW7(SW7));
endmodule
