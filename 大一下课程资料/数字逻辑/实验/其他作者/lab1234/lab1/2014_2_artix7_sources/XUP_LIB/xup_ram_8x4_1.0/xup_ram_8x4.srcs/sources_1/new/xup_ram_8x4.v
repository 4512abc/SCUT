`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: xup_ram_8x4
//////////////////////////////////////////////////////////////////////////////////
module xup_ram_8x4 #(parameter DELAY = 3)(
	input [3:0] d,
	input [2:0] read_addr, write_addr,
	input wr, clk,
	output reg [3:0] dout
);
	// Declare the RAM variable
	reg [3:0] ram[7:0];

	always @ (posedge clk)
	begin
		// Write
		if (wr)
			ram[write_addr] <= d;//if read_addr == write_addr, return OLD data
		dout <= #DELAY ram[read_addr];
	end

endmodule

