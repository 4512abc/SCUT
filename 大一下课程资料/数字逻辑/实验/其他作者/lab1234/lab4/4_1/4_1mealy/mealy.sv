`timescale 1ns / 1ps

module div3( input logic clk,
             input logic reset,
             input logic ain,
             output logic yout,
             output logic [3:0]count );
 
 typedef enum logic [1:0]{S0,S1,S2} statetype;
 statetype  state,nextstate;
 
reg re;

 always@(posedge clk) 
 begin
 
 if(reset)       
 begin
 count <= 4'b0000;  re<=0;
 end
 
 else if (ain)   
  begin
  count <= count + 4'b0001;   re<=1;
  end
 
 end
 
 always@(posedge clk)
 if(reset) state<=S0;
 else      state<=nextstate;
 
 always_comb 
 case(state)
 S0:if(ain) nextstate=S1;
    else    nextstate=S0;
 S1:if(ain) nextstate=S2;
    else    nextstate=S1;
 S2:if(ain) nextstate=S0;
    else    nextstate=S2;  
   default: nextstate=S0;
 endcase

 assign yout=(reset)? 0:(  ( (count==4'b000)&(ain==0) ) | ( (re==1)&(ain==1)&(state==S0) ) );
 
 endmodule
 