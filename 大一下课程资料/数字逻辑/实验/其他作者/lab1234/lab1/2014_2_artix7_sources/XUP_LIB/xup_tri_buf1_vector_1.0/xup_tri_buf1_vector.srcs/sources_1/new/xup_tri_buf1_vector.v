`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: xup_tri_buf1_vector
//////////////////////////////////////////////////////////////////////////////////
module xup_tri_buf1_vector #(parameter SIZE = 4 , DELAY = 3)(
    input [SIZE-1:0] a,
    input enable,
    output [SIZE-1:0] y
    );
    
   genvar i;
    generate
       for (i=0; i < SIZE; i=i+1) 
       begin: buf0_i
    		assign #DELAY y[i] = (enable) ? a[i] : 'bz;
       end
    endgenerate
    
endmodule

