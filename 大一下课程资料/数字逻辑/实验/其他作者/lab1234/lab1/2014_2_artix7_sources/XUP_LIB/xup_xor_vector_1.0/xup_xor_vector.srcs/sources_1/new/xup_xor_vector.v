`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: xup_xor_vector
//////////////////////////////////////////////////////////////////////////////////
module xup_xor_vector #(parameter SIZE = 4 , DELAY = 3)(
    input [SIZE-1:0] a,
    input [SIZE-1:0] b,
    output [SIZE-1:0] y
    ); 
    
   genvar i;
    generate
       for (i=0; i < SIZE; i=i+1) 
       begin: xor_i
          xor #DELAY(y[i], a[i], b[i]);
       end
    endgenerate
   
endmodule
