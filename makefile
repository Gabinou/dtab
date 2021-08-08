

COMPILER:=gcc#tcc, gcc, clang
# Optimization increase code speed by 5X-6X for gcc and clang ONLY

# OS AND Processor detection 
ifeq ($(OS),Windows_NT)
    OS_FLAG := WIN32
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        PROCESSOR_FLAG = AMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            PROCESSOR_FLAG := AMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            PROCESSOR_FLAG := IA32
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        OS_FLAG := LINUX
    endif
    ifeq ($(UNAME_S),Darwin)
        PROCESSOR_FLAG := OSX
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        PROCESSOR_FLAG := AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        PROCESSOR_FLAG := IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        PROCESSOR_FLAG := ARM
    endif
endif

$(info $$OS_FLAG is [${OS_FLAG}])
$(info $$PROCESSOR_FLAG is [${PROCESSOR_FLAG}])
$(info $$COMPILER [$(COMPILER)])

LINUX_EXT := .bin
WIN_EXT := .exe
LINUX_PRE := ./
WIN_PRE := 

ifeq ($(COMPILER),gcc)
    FLAGS_COV = -fprofile-arcs -ftest-coverage #Debug
else
    FLAGS_COV = #Debug
endif

# FLAGS_BUILD_TYPE = -O3 -DNDEBUG #Release
FLAGS_BUILD_TYPE = -O0 -g #Debug

# FLAGS_ERROR := -Wall -pedantic-errors
FLAGS_ERROR := -w
INCLUDE_ALL := -I. 

# astyle detection: isASTYLE is empty unless astyle exists
ifeq ($(OS_FLAG),WIN32)
	EXTENSION := $(WIN_EXT)
    PREFIX := $(WIN_PRE)
	isASTYLE := $(shell where astyle)
    CFLAGS := ${INCLUDE_ALL} ${FLAGS_BUILD_TYPE} ${FLAGS_ERROR}
else
	EXTENSION := $(LINUX_EXT)
    PREFIX := $(LINUX_PRE)
	isASTYLE := $(shell type astyle)
    CFLAGS := ${INCLUDE_ALL} ${FLAGS_BUILD_TYPE} ${FLAGS_ERROR} -lm
endif

$(info $$isASTYLE is [$(isASTYLE)])
$(info $$EXTENSION is [$(EXTENSION)])

ifeq ($(isASTYLE),)
	ASTYLE :=
else
	ASTYLE := astyle 
endif

EXEC := $(PREFIX)test$(EXTENSION)
EXEC_ALL := ${EXEC}

.PHONY: all 
all: ${ASTYLE} $(EXEC) run 
SOURCES_TEST := test.c
SOURCES_DTAB := dtab.c
HEADERS := $(wildcard *.h)
SOURCES_ALL := $(SOURCES_TEST) $(SOURCES_DTAB)
TARGETS_DTAB := $(SOURCES_DTAB:.c=.o)
TARGETS_DTAB_GCC := $(SOURCES_DTAB:.c=_gcc.o)
TARGETS_DTAB_TCC := $(SOURCES_DTAB:.c=_tcc.o)
TARGETS_DTAB_CLANG := $(SOURCES_DTAB:.c=_clang.o)
EXEC_GCC := $(PREFIX)test_gcc$(EXTENSION)
EXEC_TCC := $(PREFIX)test_tcc$(EXTENSION)
EXEC_CLANG := $(PREFIX)test_clang$(EXTENSION)
.PHONY: compile_test
compile_test: ${ASTYLE} ${EXEC_TCC} ${EXEC_GCC} ${EXEC_CLANG} tcc gcc clang

.PHONY : cov
cov: $(EXEC) run ; lcov -c --no-external -d . -o main_coverage.info ; genhtml main_coverage.info -o out

.PHONY : run
run: $(EXEC); $(EXEC)
.PHONY : tcc
tcc: $(EXEC_TCC) ; $(EXEC_TCC)
.PHONY : gcc
gcc:$(EXEC_GCC) ; $(EXEC_GCC)
.PHONY : clang
clang: $(EXEC_CLANG) ; $(EXEC_CLANG)
.PHONY : astyle
astyle: $(HEADERS) $(SOURCES_ALL); astyle --style=java --indent=spaces=4 --indent-switches --pad-oper --pad-comma --pad-header --unpad-paren --align-pointer=middle --align-reference=middle --add-braces --add-one-line-braces --attach-return-type --convert-tabs --suffix=none *.h *.c

$(TARGETS_DTAB) : $(SOURCES_DTAB) ; $(COMPILER) $< -c -o $@ $(FLAGS_COV)
$(TARGETS_DTAB_CLANG) : $(SOURCES_DTAB) ; clang $< -c -o $@ 
$(TARGETS_DTAB_GCC) : $(SOURCES_DTAB) ; gcc $< -c -o $@
$(TARGETS_DTAB_TCC) : $(SOURCES_DTAB) ; tcc $< -c -o $@ 

$(EXEC): $(SOURCES_TEST) $(TARGETS_DTAB); ${COMPILER} $< $(TARGETS_DTAB) -o $@ $(CFLAGS) $(FLAGS_COV)
$(EXEC_TCC): $(SOURCES_TEST) $(TARGETS_DTAB_TCC); tcc $<$(TARGETS_DTAB_TCC) -o $@ $(CFLAGS)
$(EXEC_GCC): $(SOURCES_TEST) $(TARGETS_DTAB_GCC); gcc $<$(TARGETS_DTAB_GCC) -o $@ $(CFLAGS)
$(EXEC_CLANG): $(SOURCES_TEST) $(TARGETS_DTAB_CLANG); clang $< $(TARGETS_DTAB_CLANG) -o $@ $(CFLAGS)

.PHONY: clean
clean: ; @echo "Cleaning DTAB" & rm -frv $(EXEC)  out *.gcda *.gcno *.gcov *.info *.exe *.bin
