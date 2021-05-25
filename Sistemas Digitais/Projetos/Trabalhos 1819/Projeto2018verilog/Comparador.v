`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:21:20 11/07/2018 
// Design Name: 
// Module Name:    Comparador 
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
module Comparador(i,p);
	input [3:0] i;
	output p;
	
	reg [3:0]c;
	reg [3:0]g;
	
	
	always @ (i)
		begin
		
			if (i==4'b0001 || i==4'b0010 || i==4'b0011 || i==4'b0100 )
				begin
					g=4'b0001; c=4'b1001; //falta corrigir os numeros em binario !
				end

			else if (i==4'b0101 || i==4'b0110 || i==4'b0111 || i==4'b1000)
				begin
					g=4'b0010; c=4'b1010; //falta corrigir os numeros em binario !
				end

			else if (i==4'b1001 || i==4'b1010 || i==4'b1011)
				begin
					g=4'b0011; c=4'b1011; //falta corrigir os numeros em binario !
				end
			else
					g=4'bxxxx; c=4'bxxxx; 
					
		end	
endmodule
