module ian_dff #(
    parameter WIDTH_PARAM = 1
)(
    input logic clk,
    input logic rst,
    input logic en_i,
    input logic [WIDTH_PARAM-1:0] d_i,
    output logic [WIDTH_PARAM-1:0] q_o
);

always_ff @(posedge clk) begin
    if (rst) begin
        q_o <= '0;
    end
    else begin
        if (en_i) begin
            q_o <= d_i;
        end
    end
end

endmodule : ian_dff
