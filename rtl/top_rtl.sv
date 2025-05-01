module top_rtl (
    input logic clk,
    input logic rst,

    input logic evt,

    output logic [3:0] VGA_R,
    output logic [3:0] VGA_G,
    output logic [3:0] VGA_B,
    output logic VGA_HS,
    output logic VGA_VS
);

logic [9:0] draw_x;
logic [9:0] draw_y;

logic [9:0] frame_count_q;
logic [9:0] frame_count_d;
logic frame_count_en;

logic blank;

assign frame_count_d = frame_count_q + 'd1;
assign frame_count_en = (draw_x == 0) & (draw_y == 'd480);

vga_controller u_vga_controller (
    .clk(clk),
    .rst(rst),

    .draw_x(draw_x),
    .draw_y(draw_y),

    .hs_n(VGA_HS),
    .vs_n(VGA_VS),

    .blank(blank)
);

ian_dff #(
    .WIDTH_PARAM(10)
) u_h_count_dff (
    .clk(clk),
    .rst(rst),
    .en_i(frame_count_en),
    .d_i(frame_count_d),
    .q_o(frame_count_q)
);

assign VGA_R = (blank) ? '0 : (evt) ? '1 : draw_x[4:1];
assign VGA_G = (blank) ? '0 : draw_y[4:1];
assign VGA_B = (blank) ? '0 : 4'(frame_count_q + draw_x + draw_y);

endmodule : top_rtl
