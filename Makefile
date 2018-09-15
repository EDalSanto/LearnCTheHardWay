# %: -> target-pattern to match anything
# 	each target is associated with target-pattern to extract name from stem for prereqs and executable file generated
# %.c -> prereq-pattern
# $< -> automatic variable that holds name of prereq
# $@ -> automatic variable that holds name of target
# more info: https://www.gnu.org/software/make/manual/html_node/Static-Usage.html#Static-Usage

CC = cc
CFLAGS = -g -Wall
BIN_DIR = bin
PROGRAMS = ex1 ex3 ex11 ex13 ex15 ex16 ex17 ex18 ex19
LIST=$(addprefix $(BIN_DIR)/, $(PROGRAMS))

.PHONY: all clean

all: $(LIST)

$(LIST): bin/%: src/%.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	$(RM) $(LIST)

re: clean all
