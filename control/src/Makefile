# Name: Makefile
# Project: B15F (Board 15 Famulus Edition)
# Author: Tristan Krause
# Creation Date: 2019-03-22

# Änderungen veröffentlichen, vorher nochmal: make clean && make && make doc && make clean && make doc && make

# Environment
PATH_COMPILER = g++
PATH_DOXYGEN = ../bin/doxygen

# install paths
PATH_BIN     = /usr/bin/
PATH_LIB     = /usr/lib/
PATH_INCLUDE = /usr/include/b15f/

# tmp paths
PATH_TMP_BIN = ../bin/
PATH_TMP_LIB = ../lib/

# outputs
OUT_TMP_DRV    = $(PATH_TMP_LIB)/libb15fdrv.so
OUT_TMP_CLI    = $(PATH_TMP_BIN)/b15fcli
OUT_TMP_PLOTTY = $(PATH_TMP_BIN)/plotty
OUT_DRV        = $(PATH_LIB)/libb15fdrv.so
OUT_CLI        = $(PATH_BIN)/b15fcli
OUT_PLOTTY     = $(PATH_BIN)/plotty
OUT_DOC        = ../../docs/html

# compiling & linking parameters
CFLAGS   = -std=c++14 -O3 -Wall -Wextra -fPIC
LDFLAGS_DRV  = -lcurses -lpthread
LDFLAGS_CLI  = $(LDFLAGS_DRV) -lb15fdrv

# objects
OBJECTS_DRV  = drv/usart.o drv/b15f.o drv/plottyfile.o drv/dot.o
OBJECTS_CLI   = cli.o ui/view.o ui/view_selection.o ui/view_promt.o ui/view_info.o ui/view_monitor.o ui/ui.o



# *** TARGETS ***

.PHONY: $(OUT_TMP_DRV) clean help

all: drv cli

drv: commit_hash $(OBJECTS_DRV) $(OUT_TMP_DRV)
	

cli: drv $(OBJECTS_CLI)
	@echo "Linking cli..."
	@mkdir -p ../bin
	$(PATH_COMPILER) $(CFLAGS) $(OBJECTS_CLI) -L $(PATH_TMP_LIB) -o $(OUT_TMP_CLI) $(LDFLAGS_CLI)
	@bash -c 'if [ ! -f "$(OUT_DRV)" ]; then echo -e "\n*** Warning ***: driver not installed\nType \"sudo make install\" to install or update b15fdrv."; fi'

doc: style
	@echo "Creating documentation with doxygen..."
	$(PATH_DOXYGEN) doxygen-cfg
	@echo problems found: `($(PATH_DOXYGEN) doxygen-cfg 3>&2 2>&1 1>&3) 2>/dev/null | wc -l`

$(OUT_TMP_DRV):
	@echo "Linking driver library..."
	@mkdir -p ../lib
	$(PATH_COMPILER) $(CFLAGS) $(OBJECTS_DRV) -shared -o $(OUT_TMP_DRV) $(LDFLAGS_CLI_DRV)
	
style:
	@echo "Formatting source code with astyle..."
	-astyle --recursive --style=allman *.cpp,*.h,*.c,*.hpp
	
install:
	@echo "Installing driver..."
	@mkdir -p $(PATH_INCLUDE)
	cp $(OUT_TMP_DRV) $(OUT_DRV)
	cp $(OUT_TMP_CLI) $(OUT_CLI)
	cp $(OUT_TMP_PLOTTY) $(OUT_PLOTTY)
	cp drv/*.h $(PATH_INCLUDE)
	
uninstall:
	@echo "Uninstalling driver..."
	rm -rf $(OUT_DRV) $(OUT_CLI) $(OUT_PLOTTY) $(PATH_INCLUDE)
	
help:
	@echo "This Makefile compiles the b15f driver lib and command line interface (CLI):"
	@echo "make ......... to compile all (no install)"
	@echo "make drv ..... to compile the b15f driver lib"
	@echo "make cli ..... to compile the cli"
	@echo "make install . to install or update the lib and headers on this machine"
	@echo "make uninstall to remove the lib and headers on this machine"
	@echo "make clean ... to delete objects and executables"

clean:
	@echo "Cleaning..."
	-rm -f $(OBJECTS_DRV) $(OBJECTS_CLI) $(OUT_TMP_CLI) $(OUT_TMP_DRV)
	-rm -rf $(OUT_DOC)
	-find . -type f -name '*.orig' -delete

commit_hash:
	@echo "Updating commit hash..."
	@bash -c 'echo -e "#ifndef COMMIT_HASH_H\n#define COMMIT_HASH_H\nconst char COMMIT_HASH[] = \"`git log --pretty=format:'%H' -n 1`\";\n#endif // COMMIT_HASH_H" > drv/commit_hash.h'
	
.cpp.o:
	$(PATH_COMPILER) $(CFLAGS) -c $< -o $@
