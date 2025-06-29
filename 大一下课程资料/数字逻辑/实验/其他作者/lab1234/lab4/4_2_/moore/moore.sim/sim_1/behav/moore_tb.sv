`timescale 1ns / 1ps
module div3_tb ();

logic [1:0] ain;
logic clk, reset,yout;

  div3  div3 (              
        . clk(clk),                      
        . ain(ain),
        . reset(reset),
        . yout(yout)
        );  


    always    
begin
  clk = 0; #5; clk = 1; #5;
end

initial begin
    ain = 2'b00;
    reset = 1;
    #5;
    assert (yout === 0) else $error("001 failed.");
    #15;

    reset = 0; #20;
    assert (yout === 0) else $error("002 failed.");

    ain = 2'b11; #10;
    assert (yout === 0) else $error("003 failed.");
    
    ain = 2'b10; #10;
    ain = 2'b00; #10;
    assert (yout === 1) else $error("004 failed.");
    #10;
    
    ain = 2'b10; #10;
    ain = 2'b00; #10;
    assert (yout === 0) else $error("005 failed.");
    
    ain = 2'b11; #10;
    ain = 2'b00; #10;
    assert (yout === 1) else $error("006 failed.");
    
    ain = 2'b01; #10;
    ain = 2'b00; #10;
    assert (yout === 0) else $error("007 failed.");
    
    ain = 2'b10; #10;
    ain = 2'b11; #10;
    ain = 2'b00; #10;
    assert (yout === 1) else $error("008 failed.");
    
    reset = 1; #5;
    assert (yout === 0) else $error("009 failed.");
    #5;
    reset = 0; #10
    assert (yout === 0) else $error("010 failed.");

    ain = 2'b10; #30;
    ain = 2'b00;
    #10;
    assert (yout === 1) else $error("011 failed.");
end

endmodule 