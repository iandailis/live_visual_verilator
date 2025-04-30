VERILATOR := verilator
VERILATOR_OUTPUT_DIR := verilator_output
VERILATOR_CONFIG_FILE :=
# VERILATOR_CONFIG_FILE := verilator_config.vlt
SDL2_FLAGS := $(shell sdl2-config --cflags --libs)
VERILATOR_MISC_ARGS := -O3 --x-assign fast --x-initial fast --noassert -CFLAGS "-Ofast" -LDFLAGS "$(SDL2_FLAGS)"
VERILATOR_DUMP_ARG :=
# VERILATOR_DUMP_ARG := --trace-fst --trace-structs --trace-threads 2 --no-trace-top
VERILATOR_WHITELIST := -Wall
# VERILATOR_WHITELIST := -Wall -Wno-UNUSEDSIGNAL

TOP_TB := top_tb
WORK_DIR := work
DUMP_FILE := dump.fst

PKG_DIR := $(PWD)/../pkg
RTL_DIR := $(PWD)/../rtl
TB_DIR := $(PWD)/../tb

PKG_SRCS := $(shell find $(PKG_DIR) -name '*.svh')
RTL_SRCS := $(shell find $(RTL_DIR) -name '*.sv' -o -name '*.v')
TB_H := $(shell find $(TB_DIR) -name '*.h')
TB_SRCS := $(shell find $(TB_DIR) -name '*.sv' -o -name '*.cpp')

SRCS := $(PKG_SRCS) $(RTL_SRCS) $(TB_SRCS)
# VERILATOR_FLAGS := --binary -j 0 $(VERILATOR_MISC_ARGS) $(VERILATOR_WHITELIST) $(VERILATOR_DUMP_ARG) $(VERILATOR_CONFIG_FILE) -I$(PKG_DIR)
VERILATOR_FLAGS := --cc --build --exe -j 0 $(VERILATOR_MISC_ARGS) $(VERILATOR_WHITELIST) $(VERILATOR_DUMP_ARG) $(VERILATOR_CONFIG_FILE) -I$(PKG_DIR)

.PHONY: all
all: run

.PHONY: run
run: compile_sim
	cd $(WORK_DIR) && ./$(VERILATOR_OUTPUT_DIR)/V$(TOP_TB)

.PHONY: compile_sim
compile_sim: Makefile
	mkdir -p $(WORK_DIR)
	mkdir -p $(WORK_DIR)/$(VERILATOR_OUTPUT_DIR)
	cp $(TB_H) $(WORK_DIR)/$(VERILATOR_OUTPUT_DIR)
	$(VERILATOR) -Mdir $(WORK_DIR)/$(VERILATOR_OUTPUT_DIR) -top $(TOP_TB) --clk clk $(VERILATOR_FLAGS) $(SRCS)

.PHONY: clean
clean:
	rm -rf $(WORK_DIR)
