# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\user\Desktop\SP'21\C291 (C and Unix)\C291-CLION-CODE\assignment4"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\user\Desktop\SP'21\C291 (C and Unix)\C291-CLION-CODE\assignment4\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/assignment4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/assignment4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/assignment4.dir/flags.make

CMakeFiles/assignment4.dir/fibprime.c.obj: CMakeFiles/assignment4.dir/flags.make
CMakeFiles/assignment4.dir/fibprime.c.obj: ../fibprime.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\user\Desktop\SP'21\C291 (C and Unix)\C291-CLION-CODE\assignment4\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/assignment4.dir/fibprime.c.obj"
	C:\Users\user\Desktop\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\assignment4.dir\fibprime.c.obj   -c "C:\Users\user\Desktop\SP'21\C291 (C and Unix)\C291-CLION-CODE\assignment4\fibprime.c"

CMakeFiles/assignment4.dir/fibprime.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/assignment4.dir/fibprime.c.i"
	C:\Users\user\Desktop\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\user\Desktop\SP'21\C291 (C and Unix)\C291-CLION-CODE\assignment4\fibprime.c" > CMakeFiles\assignment4.dir\fibprime.c.i

CMakeFiles/assignment4.dir/fibprime.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/assignment4.dir/fibprime.c.s"
	C:\Users\user\Desktop\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\user\Desktop\SP'21\C291 (C and Unix)\C291-CLION-CODE\assignment4\fibprime.c" -o CMakeFiles\assignment4.dir\fibprime.c.s

# Object files for target assignment4
assignment4_OBJECTS = \
"CMakeFiles/assignment4.dir/fibprime.c.obj"

# External object files for target assignment4
assignment4_EXTERNAL_OBJECTS =

assignment4.exe: CMakeFiles/assignment4.dir/fibprime.c.obj
assignment4.exe: CMakeFiles/assignment4.dir/build.make
assignment4.exe: CMakeFiles/assignment4.dir/linklibs.rsp
assignment4.exe: CMakeFiles/assignment4.dir/objects1.rsp
assignment4.exe: CMakeFiles/assignment4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\user\Desktop\SP'21\C291 (C and Unix)\C291-CLION-CODE\assignment4\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable assignment4.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\assignment4.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/assignment4.dir/build: assignment4.exe

.PHONY : CMakeFiles/assignment4.dir/build

CMakeFiles/assignment4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\assignment4.dir\cmake_clean.cmake
.PHONY : CMakeFiles/assignment4.dir/clean

CMakeFiles/assignment4.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\user\Desktop\SP'21\C291 (C and Unix)\C291-CLION-CODE\assignment4" "C:\Users\user\Desktop\SP'21\C291 (C and Unix)\C291-CLION-CODE\assignment4" "C:\Users\user\Desktop\SP'21\C291 (C and Unix)\C291-CLION-CODE\assignment4\cmake-build-debug" "C:\Users\user\Desktop\SP'21\C291 (C and Unix)\C291-CLION-CODE\assignment4\cmake-build-debug" "C:\Users\user\Desktop\SP'21\C291 (C and Unix)\C291-CLION-CODE\assignment4\cmake-build-debug\CMakeFiles\assignment4.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/assignment4.dir/depend

