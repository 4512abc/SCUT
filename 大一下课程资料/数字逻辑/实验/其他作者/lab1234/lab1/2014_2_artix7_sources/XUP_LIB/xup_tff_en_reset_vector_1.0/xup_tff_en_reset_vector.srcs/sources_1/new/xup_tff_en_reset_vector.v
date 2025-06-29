`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: xup_tff_en_reset_vector
//////////////////////////////////////////////////////////////////////////////////
module xup_tff_en_reset_vector#(parameter SIZE = 4 , DELAY = 3)(
   input [SIZE-1:0] t,
   input clk,
   input en,
   input reset,
   output [SIZE-1:0] q
   );
   reg [SIZE-1:0] q;
   initial q = 0;
   
   always @(posedge clk)
   begin 
       if(reset)
           q[SIZE-1:0] <= #DELAY 0;
       else if(en)
           q[SIZE-1:0] <= #DELAY t[SIZE-1:0]^q[SIZE-1:0];            
   end
   
endmodule
