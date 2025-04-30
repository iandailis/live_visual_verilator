module vga_controller (
    input logic clk,
    input logic rst,

    output logic [9:0] draw_x,
    output logic [9:0] draw_y,

    output logic hs_n,
    output logic vs_n,

    output logic blank
);

localparam H_ACTIVE_PARAM = 640;
localparam H_FRONT_PARAM = 16;
localparam H_SYNC_PARAM = 96;
localparam H_BACK_PARAM = 48;
localparam H_TOTAL_PARAM = H_ACTIVE_PARAM + H_FRONT_PARAM + H_SYNC_PARAM + H_BACK_PARAM;

localparam V_ACTIVE_PARAM = 480;
localparam V_FRONT_PARAM = 11;
localparam V_SYNC_PARAM = 2;
localparam V_BACK_PARAM = 31;
localparam V_TOTAL_PARAM = V_ACTIVE_PARAM + V_FRONT_PARAM + V_SYNC_PARAM + V_BACK_PARAM;

logic [9:0] h_count_q;
logic [9:0] h_count_d;

logic [9:0] v_count_q;
logic [9:0] v_count_d;
logic v_count_en;

assign h_count_d = (h_count_q == (H_TOTAL_PARAM-1))
    ? '0
    : h_count_q + 'd1;

assign v_count_d = (v_count_q == (V_TOTAL_PARAM-1))
    ? '0
    : v_count_q + 'd1;

assign v_count_en = (h_count_q == (H_TOTAL_PARAM-1));

assign blank = (h_count_q >= H_ACTIVE_PARAM) | (v_count_q >= V_ACTIVE_PARAM);

assign hs_n = ~(
    (h_count_q >= (H_ACTIVE_PARAM + H_FRONT_PARAM))
    & (h_count_q < (H_ACTIVE_PARAM + H_FRONT_PARAM + H_SYNC_PARAM))
);

assign vs_n = ~(
    (v_count_q >= (V_ACTIVE_PARAM + V_FRONT_PARAM))
    & (v_count_q < (V_ACTIVE_PARAM + V_FRONT_PARAM + V_SYNC_PARAM))
);

assign draw_x = h_count_q;
assign draw_y = v_count_q;

ian_dff #(
    .WIDTH_PARAM(10)
) u_h_count_dff (
    .clk(clk),
    .rst(rst),
    .en_i(1'b1),
    .d_i(h_count_d),
    .q_o(h_count_q)
);

ian_dff #(
    .WIDTH_PARAM(10)
) u_draw_y_dff (
    .clk(clk),
    .rst(rst),
    .en_i(v_count_en),
    .d_i(v_count_d),
    .q_o(v_count_q)
);

endmodule : vga_controller
