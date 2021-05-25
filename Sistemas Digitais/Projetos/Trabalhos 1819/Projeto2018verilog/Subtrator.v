`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    17:27:22 11/07/2018 
// Design Name: 
// Module Name:    Subtrator 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module Subtrator(a,res);
	//input sub;
	input [3:0] a;
	output [3:0] res;
	assign res=(a- 4'b0011);
endmodule
   
