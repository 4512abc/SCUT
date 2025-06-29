`timescale 1ns / 1ps

module div3_tb();
    logic yout;
    logic [3:0] count;
    logic clk, reset, ain;
    
div3   div3 (              
          . clk(clk), 
          . yout(yout),                      
          . ain(ain),
          . reset(reset),
          . count(count)
          );  
   
    always   
    begin
      clk = 0; #5; clk = 1; #5;
    end

    initial  begin
     ain = 0;
     reset = 1;
     #20 reset = 0;
     #20 ain = 1;
     #20 ain = 0;
     #60 ain = 1;
     #40 ain = 0;
     #20 ain = 1;
     #10 reset = 1;
     #10 reset = 0;
     #10 ain = 0;
     #30 ain = 1;
    end
    
endmodule
