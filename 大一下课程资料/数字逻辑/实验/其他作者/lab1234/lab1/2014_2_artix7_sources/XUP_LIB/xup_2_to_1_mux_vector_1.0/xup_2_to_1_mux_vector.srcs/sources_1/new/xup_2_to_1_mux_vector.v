`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: xup_2_to_1_mux_vector
//////////////////////////////////////////////////////////////////////////////////
module xup_2_to_1_mux_vector #(parameter SIZE = 4 , DELAY = 3)(
   input [SIZE-1:0] a,
   input [SIZE-1:0] b,
   input sel,
   output [SIZE-1:0] y
   );
   
   assign #DELAY y[SIZE-1:0] = sel?b[SIZE-1:0] :a[SIZE-1:0];
       
endmodule
