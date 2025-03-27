COMPILER = g++
DEBUGGER = gdb

OUTPUT_FILE = test.out
RUN_ARGS = 127.0.0.1
COMPILATION_DIR = ./

FILES := ./main.cpp 
DEPENDENCIES := ./src/*/*.cpp ./src/*/*.h ./src/*/*.c ./src/*.h -lraylib

MEMTESTER := valgrind
MEMTEST_OPT := --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=memtest.log

build:
	$(COMPILER) $(FILES) $(DEPENDENCIES) -o $(OUTPUT_FILE)

run:
	$(COMPILATION_DIR)$(OUTPUT_FILE) $(RUN_ARGS)

server:
	$(COMPILATION_DIR)$(OUTPUT_FILE)

debug:
	$(COMPILER) $(FILES) $(DEPENDENCIES) -o $(OUTPUT_FILE) -p 
	$(DEBUGGER) --args $(COMPILATION_DIR)$(OUTPUT_FILE) $(RUN_ARGS)

memtest: build
	$(MEMTESTER) $(MEMTEST_OPT) $(COMPILATION_DIR)$(OUTPUT_FILE) $(RUN_ARGS) 
	cat memtest.log

lines:
	echo "Header files lines: ";\
	find . -name '*.h' | sed 's/.*/"&"/' | xargs wc -l;\
	echo "C files lines: ";\
	find . -name '*.c' | sed 's/.*/"&"/' | xargs wc -l;\
	echo "C++ files lines: ";\
	find . -name '*.cpp' | sed 's/.*/"&"/' | xargs wc -l
