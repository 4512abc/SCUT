`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: xup_tff_en
//////////////////////////////////////////////////////////////////////////////////
module xup_tff_en#(parameter DELAY = 3)(
    input t,
    input clk,
    input en,
    output q
    );
    
    reg q;
    initial q=0;
    always @(posedge clk)
    begin 
        if(en)
            q<= #DELAY t^q;
    end
endmodule
