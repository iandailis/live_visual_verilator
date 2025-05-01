module top_tb (
    input logic clk,
    input logic rst,

    output logic [9:0] draw_x,
    output logic [9:0] draw_y,

    input logic evt,

    output logic [3:0] VGA_R,
    output logic [3:0] VGA_G,
    output logic [3:0] VGA_B,
    output logic VGA_HS,
    output logic VGA_VS
);
    // initial begin
    //     $dumpfile("dump.fst");
    //     $dumpvars(0, "+all");
    // end

    assign draw_x = dut.draw_x;
    assign draw_y = dut.draw_y;

    top_rtl dut (
        .clk(clk),
        .rst(rst),

        .evt(evt),

        .VGA_R(VGA_R),
        .VGA_G(VGA_G),
        .VGA_B(VGA_B),
        .VGA_HS(VGA_HS),
        .VGA_VS(VGA_VS)
    );

endmodule : top_tb
