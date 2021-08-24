`timescale 1ns / 1ps

module simtop;

wire[0:7] din = 8'ha3; // input

reg[16:1] sr = 0;

event e;
integer i;
initial begin
for(i=0; i<8; i=i+1) begin
    #1;
    ->e;
    #1;
end
$display("0x%04x", sr); // output: 8589 expected
$finish();
end

wire feedback = sr[16] ^ din[i];

always @ (e) begin
    sr<={
        sr[15:13],
        sr[12]^feedback,
        sr[11:6],
        sr[5]^feedback,
        sr[4:1],
        feedback
    };
end

endmodule
