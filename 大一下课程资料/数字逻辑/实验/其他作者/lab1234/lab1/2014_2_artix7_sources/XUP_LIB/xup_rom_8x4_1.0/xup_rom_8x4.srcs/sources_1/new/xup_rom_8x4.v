`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: xup_rom_8x4
//////////////////////////////////////////////////////////////////////////////////
module xup_rom_8x4 #(parameter DELAY=3,rom_content=32'h12345678)(
    input [2:0] addr,
    output [3:0] dout
    );
    
    parameter N=4;//no. of bits rom word
    parameter N_WORDS=8;//no. of words in rom
    reg [N-1:0] rom [0:N_WORDS-1];
    //parameter rom_content=32'h12345678; left index of data
    parameter IXLEFT=N*N_WORDS-1;
    integer i;
    
    initial
    begin
        for(i=0;i<N_WORDS;i=i+1)
            rom[i]=rom_content[(IXLEFT-N*i)-:N];
    end
    
    assign #DELAY dout=rom[addr];  
endmodule
