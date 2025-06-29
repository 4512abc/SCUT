`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////// 
// Module Name: xup_4_to_1_mux
//////////////////////////////////////////////////////////////////////////////////
module xup_4_to_1_mux #(parameter DELAY = 3)(
    input a,
    input b,
    input c,
    input d,
    input [1:0] select,
    output y
    );
    reg data;
    
    always @(*) begin
        case(select)
            2'b00 : data <= a;
            2'b01 : data <= b;
            2'b10 : data <= c;
            2'b11 : data <= d;
            default : data <= a;
        endcase
    end
    
    assign #DELAY y = data;
        
endmodule
