# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yoda/polytech/[C]/ProjetC2/procsi_emul

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yoda/polytech/[C]/ProjetC2/procsi_emul

# Include any dependencies generated for this target.
include CMakeFiles/ProcSI.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ProcSI.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ProcSI.dir/flags.make

CMakeFiles/ProcSI.dir/main.c.o: CMakeFiles/ProcSI.dir/flags.make
CMakeFiles/ProcSI.dir/main.c.o: main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yoda/polytech/[C]/ProjetC2/procsi_emul/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/ProcSI.dir/main.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ProcSI.dir/main.c.o   -c /home/yoda/polytech/[C]/ProjetC2/procsi_emul/main.c

CMakeFiles/ProcSI.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ProcSI.dir/main.c.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_C_CREATE_PREPROCESSED_SOURCE

CMakeFiles/ProcSI.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ProcSI.dir/main.c.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_C_CREATE_ASSEMBLY_SOURCE

CMakeFiles/ProcSI.dir/main.c.o.requires:
.PHONY : CMakeFiles/ProcSI.dir/main.c.o.requires

CMakeFiles/ProcSI.dir/main.c.o.provides: CMakeFiles/ProcSI.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/ProcSI.dir/build.make CMakeFiles/ProcSI.dir/main.c.o.provides.build
.PHONY : CMakeFiles/ProcSI.dir/main.c.o.provides

CMakeFiles/ProcSI.dir/main.c.o.provides.build: CMakeFiles/ProcSI.dir/main.c.o

CMakeFiles/ProcSI.dir/parser.c.o: CMakeFiles/ProcSI.dir/flags.make
CMakeFiles/ProcSI.dir/parser.c.o: parser.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yoda/polytech/[C]/ProjetC2/procsi_emul/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/ProcSI.dir/parser.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ProcSI.dir/parser.c.o   -c /home/yoda/polytech/[C]/ProjetC2/procsi_emul/parser.c

CMakeFiles/ProcSI.dir/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ProcSI.dir/parser.c.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_C_CREATE_PREPROCESSED_SOURCE

CMakeFiles/ProcSI.dir/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ProcSI.dir/parser.c.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_C_CREATE_ASSEMBLY_SOURCE

CMakeFiles/ProcSI.dir/parser.c.o.requires:
.PHONY : CMakeFiles/ProcSI.dir/parser.c.o.requires

CMakeFiles/ProcSI.dir/parser.c.o.provides: CMakeFiles/ProcSI.dir/parser.c.o.requires
	$(MAKE) -f CMakeFiles/ProcSI.dir/build.make CMakeFiles/ProcSI.dir/parser.c.o.provides.build
.PHONY : CMakeFiles/ProcSI.dir/parser.c.o.provides

CMakeFiles/ProcSI.dir/parser.c.o.provides.build: CMakeFiles/ProcSI.dir/parser.c.o

CMakeFiles/ProcSI.dir/function.c.o: CMakeFiles/ProcSI.dir/flags.make
CMakeFiles/ProcSI.dir/function.c.o: function.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yoda/polytech/[C]/ProjetC2/procsi_emul/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/ProcSI.dir/function.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ProcSI.dir/function.c.o   -c /home/yoda/polytech/[C]/ProjetC2/procsi_emul/function.c

CMakeFiles/ProcSI.dir/function.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ProcSI.dir/function.c.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_C_CREATE_PREPROCESSED_SOURCE

CMakeFiles/ProcSI.dir/function.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ProcSI.dir/function.c.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_C_CREATE_ASSEMBLY_SOURCE

CMakeFiles/ProcSI.dir/function.c.o.requires:
.PHONY : CMakeFiles/ProcSI.dir/function.c.o.requires

CMakeFiles/ProcSI.dir/function.c.o.provides: CMakeFiles/ProcSI.dir/function.c.o.requires
	$(MAKE) -f CMakeFiles/ProcSI.dir/build.make CMakeFiles/ProcSI.dir/function.c.o.provides.build
.PHONY : CMakeFiles/ProcSI.dir/function.c.o.provides

CMakeFiles/ProcSI.dir/function.c.o.provides.build: CMakeFiles/ProcSI.dir/function.c.o

CMakeFiles/ProcSI.dir/interface.c.o: CMakeFiles/ProcSI.dir/flags.make
CMakeFiles/ProcSI.dir/interface.c.o: interface.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yoda/polytech/[C]/ProjetC2/procsi_emul/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/ProcSI.dir/interface.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ProcSI.dir/interface.c.o   -c /home/yoda/polytech/[C]/ProjetC2/procsi_emul/interface.c

CMakeFiles/ProcSI.dir/interface.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ProcSI.dir/interface.c.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_C_CREATE_PREPROCESSED_SOURCE

CMakeFiles/ProcSI.dir/interface.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ProcSI.dir/interface.c.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_C_CREATE_ASSEMBLY_SOURCE

CMakeFiles/ProcSI.dir/interface.c.o.requires:
.PHONY : CMakeFiles/ProcSI.dir/interface.c.o.requires

CMakeFiles/ProcSI.dir/interface.c.o.provides: CMakeFiles/ProcSI.dir/interface.c.o.requires
	$(MAKE) -f CMakeFiles/ProcSI.dir/build.make CMakeFiles/ProcSI.dir/interface.c.o.provides.build
.PHONY : CMakeFiles/ProcSI.dir/interface.c.o.provides

CMakeFiles/ProcSI.dir/interface.c.o.provides.build: CMakeFiles/ProcSI.dir/interface.c.o

# Object files for target ProcSI
ProcSI_OBJECTS = \
"CMakeFiles/ProcSI.dir/main.c.o" \
"CMakeFiles/ProcSI.dir/parser.c.o" \
"CMakeFiles/ProcSI.dir/function.c.o" \
"CMakeFiles/ProcSI.dir/interface.c.o"

# External object files for target ProcSI
ProcSI_EXTERNAL_OBJECTS =

ProcSI: CMakeFiles/ProcSI.dir/main.c.o
ProcSI: CMakeFiles/ProcSI.dir/parser.c.o
ProcSI: CMakeFiles/ProcSI.dir/function.c.o
ProcSI: CMakeFiles/ProcSI.dir/interface.c.o
ProcSI: /usr/lib/libcurses.so
ProcSI: /usr/lib/libform.so
ProcSI: CMakeFiles/ProcSI.dir/build.make
ProcSI: CMakeFiles/ProcSI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ProcSI"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ProcSI.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ProcSI.dir/build: ProcSI
.PHONY : CMakeFiles/ProcSI.dir/build

CMakeFiles/ProcSI.dir/requires: CMakeFiles/ProcSI.dir/main.c.o.requires
CMakeFiles/ProcSI.dir/requires: CMakeFiles/ProcSI.dir/parser.c.o.requires
CMakeFiles/ProcSI.dir/requires: CMakeFiles/ProcSI.dir/function.c.o.requires
CMakeFiles/ProcSI.dir/requires: CMakeFiles/ProcSI.dir/interface.c.o.requires
.PHONY : CMakeFiles/ProcSI.dir/requires

CMakeFiles/ProcSI.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ProcSI.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ProcSI.dir/clean

CMakeFiles/ProcSI.dir/depend:
	cd /home/yoda/polytech/[C]/ProjetC2/procsi_emul && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yoda/polytech/[C]/ProjetC2/procsi_emul /home/yoda/polytech/[C]/ProjetC2/procsi_emul /home/yoda/polytech/[C]/ProjetC2/procsi_emul /home/yoda/polytech/[C]/ProjetC2/procsi_emul /home/yoda/polytech/[C]/ProjetC2/procsi_emul/CMakeFiles/ProcSI.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ProcSI.dir/depend

