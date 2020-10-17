GROUPID=ACS

CC=g++
CPPFLAGS=-I$(INC_DIR) -MMD -MP

# FIXME
# CFLAGS=-Wall -Werror -Wpedantic -std=c++14 -O -g
CFLAGS=-Wall -Wpedantic -std=c++14 -O -g

INC_DIR=include
SRC_DIR=src
OBJ_DIR=obj
TEST_DIR=tests/save_files
TEST_OUTPUT_DIR=tests/output
BIN_DIR=.

SRCS=$(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
OBJS=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
TESTS=$(wildcard $(TEST_DIR)/*.azul)
TEST_OUTPUTS=$(subst .azul,.out,$(TESTS))

.PHONY: all clean test test-outputs check zip force-zip run memtest build-memtest run-memtest

.default: all

all: azul

azul: $(OBJS)
	$(CC) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(TEST_DIR) $(TEST_OUTPUT_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(OBJ_DIR) $(TEST_OUTPUT_DIR) azul **/*.d **/*.dSYM *.plist **/*.plist ~*.xlsx $(GROUPID).zip

%.out: %.azul azul | $(TEST_OUTPUT_DIR)
	./azul -t $< > $(TEST_OUTPUT_DIR)/$(notdir $(subst .azul,.out,$<))

test: $(TEST_OUTPUTS) | $(TEST_DIR) $(TEST_OUTPUT_DIR)
	@set -e; for test in $^; do \
		printf "$$(basename $$test .out): "; \
		diff -u $$test $(TEST_OUTPUT_DIR)/$$(basename $$test); \
		printf "pass\n"; \
	done

run: azul
	./azul

check:
	cppcheck --enable=all --inconclusive --std=c++14 . && \
	clang --analyze -I$(INC_DIR) **/*.cpp --std=c++14

build-memtest: Dockerfile.memtest
	docker build \
	    -f Dockerfile.memtest \
		-t apt-a2-memory-test \
		.

run-memtest: azul
	# TODO: use more extensive test file
	valgrind --leak-check=full ./azul -t tests/save_files/05-completed.azul

memtest: build-memtest
	@# Runs in a container because valgrind doesn't currently work under macOS
	docker run \
		-ti \
		-v "$(PWD):/memtest" \
		apt-a2-memory-test

zip: test check force-zip

force-zip: clean
	zip -r $(GROUPID).zip *.md $(SRCS) $(INC_DIR) tests/ Makefile *.xlsx

-include $(OBJS:.o=.d)