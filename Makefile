CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99
CFLAGS_orig = -O0
CFLAGS_opt  = -O0

EXEC = phonebook_orig phonebook_opt_struct phonebook_opt_hash
all: $(EXEC)

SRCS_common_hash = main_hash.c
SRCS_common_orig = main_orig.c
SRCS_common_struct = main_struct.c

phonebook_orig: $(SRCS_common_orig) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common_orig) $@.c

phonebook_opt_struct: $(SRCS_common_struct) phonebook_opt_struct.c phonebook_opt_struct.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common_struct) $@.c

phonebook_opt_hash: $(SRCS_common_hash) phonebook_opt_hash.c phonebook_opt_hash.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common_hash) $@.c

run: $(EXEC)
	echo 3 | sudo tee /proc/sys/vm/drop_caches
	watch -d -t "./phonebook_orig && echo 3 | sudo tee /proc/sys/vm/drop_caches"

cache-test: $(EXEC)
	perf stat --repeat 10 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_orig
	perf stat --repeat 10 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_opt_struct
	perf stat --repeat 10 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_opt_hash


output.txt: cache-test calculate
	./calculate

plot: output.txt
	gnuplot scripts/runtime.gp

calculate: calculate.c
	$(CC) $(CFLAGS_common) $^ -o $@

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.* \
	      	calculate orig.txt opt.txt output.txt runtime.png opt_hash.txt opt_struct.txt
