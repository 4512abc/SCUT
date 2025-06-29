`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: xup_dff_en
//////////////////////////////////////////////////////////////////////////////////
module xup_dff_en #(parameter DELAY = 3)(
    input d,
    input clk,
    input en,
    output q
    );
    
    reg q;
    always @(posedge clk)
    begin 
        if(en)
            q<= #DELAY d;
    end
endmodule
