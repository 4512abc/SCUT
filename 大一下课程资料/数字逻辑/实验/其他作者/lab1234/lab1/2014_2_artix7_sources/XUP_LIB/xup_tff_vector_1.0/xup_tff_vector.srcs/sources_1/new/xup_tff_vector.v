`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: xup_tff_vector
//////////////////////////////////////////////////////////////////////////////////
module xup_tff_vector #(parameter SIZE = 4 , DELAY = 3)(
  input [SIZE-1:0] t,
  input clk,
  output [SIZE-1:0] q
  );
  reg [SIZE-1:0] q;
  initial q =0;
  
  always @(posedge clk)
  begin 
      q[SIZE-1:0] <= #DELAY t[SIZE-1:0]^q[SIZE-1:0] ;
  end
  
endmodule
