`timescale 1ns / 1ps

module div3 (clk,ain,reset,yout);              
input  clk,reset;
input  [1:0] ain;
output logic yout;

 typedef enum logic [1:0]{S0,S1,S2,S3} statetype;
 statetype  state,nextstate;

always@(posedge clk) 
if(reset) state<=S0;
else      state<=nextstate;

always_comb
case(state)        
 S0:        if(ain==2'b11)  nextstate=S1;
      else if(ain==2'b10)   nextstate=S1;
      else if(ain==2'b00)   nextstate=S0;
      else if(ain==2'b01)   nextstate=S0;

 S1:        if(ain==2'b00)  nextstate=S2;
      else if(ain==2'b01)   nextstate=S0;
      else if(ain==2'b11)   nextstate=S1;
      else if(ain==2'b10)   nextstate=S1;

 S2:       if(ain==2'b01)   nextstate=S3;
      else if(ain==2'b10)   nextstate=S3;
      else if(ain==2'b11)   nextstate=S2;
      else if(ain==2'b00)   nextstate=S2;

 S3:       if(ain==2'b11)   nextstate=S2;
      else if(ain==2'b00)   nextstate=S0;
      else if(ain==2'b01)   nextstate=S3;
      else if(ain==2'b10)   nextstate=S3;
      
default:                   nextstate=S0;
endcase

assign yout=~reset&((state==S3)|(state==S2));

endmodule