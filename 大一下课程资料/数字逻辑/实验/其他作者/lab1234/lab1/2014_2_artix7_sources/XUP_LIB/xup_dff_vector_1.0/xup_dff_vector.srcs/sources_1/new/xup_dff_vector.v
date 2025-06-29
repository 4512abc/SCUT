`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////// 
// Module Name: xup_dff_vector
//////////////////////////////////////////////////////////////////////////////////
module xup_dff_vector #(parameter SIZE = 4 , DELAY = 3)(
   input [SIZE-1:0] d,
   input clk,
   output [SIZE-1:0] q
   );
   reg [SIZE-1:0] q;
   
   always @(posedge clk)
   begin 
      q[SIZE-1:0] <= #DELAY d[SIZE-1:0];
   end
   
endmodule
