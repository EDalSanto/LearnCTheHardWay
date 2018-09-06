# %: -> target-patten to match anything
# 	each target is associated with target-pattern to extract name from stem for prereqs and executable file generated
# %.c -> prereq-pattern
# $< -> automatic variable that holds name of prereq
# $@ -> automatic variable that holds name of target
# more info: https://www.gnu.org/software/make/manual/html_node/Static-Usage.html#Static-Usage

CC = cc
CFLAGS = -g -Wall
PROGRAMS = ex1 ex3

.PHONY: all clean

all: $(PROGRAMS)

$(PROGRAMS): %: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	$(RM) $(PROGRAMS)

re: clean all
