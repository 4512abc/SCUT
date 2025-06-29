`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: xup_clk_divider
//////////////////////////////////////////////////////////////////////////////////
module xup_clk_divider #(parameter SIZE = 2)(
    input clkin,
    output reg clkout
    );
    
    reg [31:0] count = 0;
    reg [31:0] N = SIZE/2-1;
    initial clkout = 0;

    always @(posedge clkin) begin
        if(count >= N)begin
            count <= 0;
            clkout <= ~clkout;
        end
        else begin
            count <= count + 1;
        end
    end

endmodule
