module top (input clk, output reg led1, led2, led3);
	parameter COUNTER_BITS = 26;
	reg [COUNTER_BITS-1:0] counter = 0;
	always @(posedge clk) begin
		counter <= counter + 1;
		{led1, led2, led3} <= counter[COUNTER_BITS-1 -: 3] ^ (counter[COUNTER_BITS-1 -: 3] >> 1);
	end
endmodule
