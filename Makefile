#=============================
#
# Author      : Lasercata
# Last update : 2024.03.11
# Version     : v1.0.3
#
# This is a C makefile.
#
#=============================

# ====== Target ======{{{1
TARGET = main
SEARCH_NB = 50000
# }}}1

# ====== Initialisation ======{{{1
# ------ Compiler ------{{{2
CC = gcc
CFLAGS = -W -Wall -Wconversion -Werror -std=gnu99
DEBUG_FLAGS = -O0 -g
PROD_FLAGS = -O2
# }}}2

# ------ Linker ------{{{2
LD_FLAGS =
# LD_FLAGS = -lm -W -Wall -pedantic -pthread
# }}}2

# ------ Directories ------{{{2
SRC_DIR = src
INCL_DIR = include
BUILD_DIR = build
BIN_DIR = bin
LOGS_DIR = logs
DATA_DIR = data
PLOTS_DIR = plots

DIR_LST = $(SRC_DIR) $(INCL_DIR) $(BUILD_DIR) $(BIN_DIR) $(LOGS_DIR) $(DATA_DIR) $(PLOTS_DIR)

# ------ Lists ------
SRC_LST = ${wildcard src/*.c}
OBJ_LST = ${SRC_LST:src/%.c=$(BUILD_DIR)/%.o}
# BIN_LST = ${SRC_LST:src/%.c=$(BIN_DIR)/%}

DATA_SIZE_LST = 10 1000 2000 4000 10000 20000 40000 100000 200000 400000 1000000
DATA_LST = ${DATA_SIZE_LST:%=$(DATA_DIR)/title_%.tsv}
# }}}2
# }}}1

# ====== Rules ======{{{1
# ------ All ------{{{2
.PHONY: all
all: debug_or_prod_flags = $(PROD_FLAGS)
all: dirs $(BIN_DIR)/$(TARGET)

.PHONY: debug
debug: debug_or_prod_flags = $(DEBUG_FLAGS)
debug: dirs $(BIN_DIR)/$(TARGET)
# }}}2

# ------ Target ------{{{2
$(BIN_DIR)/%: $(BUILD_DIR)/%.o $(OBJ_LST)
	@echo ====== Linking $@ ======
	$(CC) \
		$^ \
		-o $@ \
		$(LD_FLAGS)

# ------ Objects ------
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCL_DIR)/%.h
	@echo ====== Compiling $@ ======
	$(CC) \
		$(CFLAGS) $(debug_or_prod_flags) \
		-c \
		$< \
		-o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo ====== Compiling $@ ======
	$(CC) \
		$(CFLAGS) $(debug_or_prod_flags) \
		-c \
		$< \
		-o $@
# }}}2

# ------ Remake ------{{{2
.PHONY: remake
remake: clean all

# ------ Remake debug ------
.PHONY: remake-debug
remake: clean debug
# }}}2

# ------ Run ------{{{2
.PHONY: run
run: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET)
# }}}2

# ------ Data ------{{{2
$(DATA_DIR)/title.basics.tsv:
	cd $(DATA_DIR); \
		7z x data.zip

$(DATA_DIR)/title_%.tsv: $(DATA_DIR)/title.basics.tsv
	head -n $* $< | sort -R > $@

.PHONY: parallelized_data
parallelized_data: $(DATA_DIR)/title.basics.tsv
	for k in $(DATA_SIZE_LST); do ((head -n $$k $< | sort -R > $(DATA_DIR)/title_"$$k".tsv) && echo $(DATA_DIR)/title_"$$k".tsv made) & done; wait
# }}}2

# ------ Logs ------{{{2
# $(LOGS_DIR)/all.log: $(BIN_DIR)/$(TARGET) parallelized_data
$(LOGS_DIR)/all.log: $(BIN_DIR)/$(TARGET) $(DATA_LST)
	nb_search=$(SEARCH_NB) ./make_logs.sh
	cat $(LOGS_DIR)/*.log > $@

.PHONY: graphs
graphs: $(LOGS_DIR)/all.log
	python3 make_graphs.py $<
#  }}}2

# ------ Make directories ------{{{2
.PHONY: dirs
dirs: $(DIR_LST)
# dirs:
# 	@echo ====== Creating directories ======
# 	@for dir in $(DIR_LST); do \
# 		if [ ! -d $${dir} ]; then \
# 			echo Creating $${dir}; \
# 			mkdir -p $${dir}; \
# 		fi; \
# 	done

$(SRC_DIR):
	@echo ====== Creating $(SRC_DIR) directory ======
	@mkdir -p $(SRC_DIR)

$(INCL_DIR):
	@echo ====== Creating $(INCL_DIR) directory ======
	@mkdir -p $(INCL_DIR)

$(BIN_DIR):
	@echo ====== Creating $(BIN_DIR) directory ======
	@mkdir -p $(BIN_DIR)
	@echo "*" > $(BIN_DIR)/.gitignore

$(BUILD_DIR):
	@echo ====== Creating $(BUILD_DIR) directory ======
	@mkdir -p $(BUILD_DIR)
	@echo "*" > $(BUILD_DIR)/.gitignore

$(LOGS_DIR):
	@echo ====== Creating $(LOGS_DIR) directory ======
	@mkdir -p $(LOGS_DIR)
	@echo "*" > $(LOGS_DIR)/.gitignore

$(DATA_DIR):
	@echo ====== Creating $@ directory ======
	@mkdir -p $(DATA_DIR)
	@echo "*" > $(DATA_DIR)/.gitignore

$(PLOTS_DIR):
	@echo ====== Creating $@ directory ======
	@mkdir -p $(PLOTS_DIR)
# }}}2

# ------ Clean ------{{{2
.PHONY: clean
clean: clean-obj clean-bin clean-logs clean-plots clean-data

# ------ Clean obj ------
.PHONY: clean-obj
clean-obj:
	@echo ====== Cleaning *.o ======
	# rm -f $(OBJ_LST)
	rm -f $(BUILD_DIR)/*

# ------ Clean bin ------
.PHONY: clean-bin
clean-bin:
	@echo ====== Cleaning $(BIN_DIR)/ ======
	rm -f $(BIN_DIR)/*

.PHONY: clean-logs
clean-logs:
	@echo ====== Cleaning $(LOGS_DIR)/ ======
	rm -f $(LOGS_DIR)/*.log

.PHONY: clean-plots
clean-plots:
	@echo ====== Cleaning $(PLOTS_DIR)/ ======
	rm -f $(PLOTS_DIR)/*.png

.PHONY: clean-data
clean-data:
	@echo ====== Cleaning $(DATA_DIR)/ ======
	rm -f $(DATA_LST)
	rm -f $(DATA_DIR)/data_full.zip
	rm -f $(DATA_DIR)/title.basics.tsv
# }}}2
# }}}1

# vim:foldmethod=marker:foldlevel=0
