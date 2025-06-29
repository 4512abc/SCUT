`timescale 1ns / 1ps
/////////////////////////////////////////////////////////////////
// Module Name: tutorial_tb
/////////////////////////////////////////////////////////////////
module tutorial_tb(
    ); 
    reg [7:0] switches;
    wire [7:0] leds;
    reg [7:0] e_led;    
    integer i;    
    design_1_wrapper tut1(
            .LD0(leds[0]),
            .LD1(leds[1]),
            .LD2(leds[2]),
            .LD3(leds[3]),
            .LD4(leds[4]),
            .LD5(leds[5]),
            .LD6(leds[6]),
            .LD7(leds[7]),
            .SW0(switches[0]),
            .SW1(switches[1]),
            .SW2(switches[2]),
            .SW3(switches[3]),
            .SW4(switches[4]),
            .SW5(switches[5]),
            .SW6(switches[6]),
            .SW7(switches[7]));
 
    function [7:0] expected_led;
       input [7:0] swt;
    begin      
       expected_led[0] = ~swt[0];
       expected_led[1] = swt[1] & ~swt[2];
       expected_led[3] = swt[2] & swt[3];
       expected_led[2] = expected_led[1] | expected_led[3];
       expected_led[7:4] = swt[7:4];
    end   
    endfunction   
    
    initial
    begin
        for (i=0; i < 255; i=i+2)
        begin
            #50 switches=i;
            #10 e_led = expected_led(switches);
            if(leds == e_led)
                $display("LED output matched at", $time);
            else
                $display("LED output mis-matched at ",$time,": expected: %b, actual: %b", e_led, leds);
        end
    end
      
endmodule
