# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hermann/Ucu/OS_2019/Project/bfs/rpc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hermann/Ucu/OS_2019/Project/bfs/rpc/build

# Include any dependencies generated for this target.
include CMakeFiles/rpc.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rpc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rpc.dir/flags.make

CMakeFiles/rpc.dir/main.cpp.o: CMakeFiles/rpc.dir/flags.make
CMakeFiles/rpc.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hermann/Ucu/OS_2019/Project/bfs/rpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rpc.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rpc.dir/main.cpp.o -c /home/hermann/Ucu/OS_2019/Project/bfs/rpc/main.cpp

CMakeFiles/rpc.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rpc.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hermann/Ucu/OS_2019/Project/bfs/rpc/main.cpp > CMakeFiles/rpc.dir/main.cpp.i

CMakeFiles/rpc.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rpc.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hermann/Ucu/OS_2019/Project/bfs/rpc/main.cpp -o CMakeFiles/rpc.dir/main.cpp.s

CMakeFiles/rpc.dir/rpc.cpp.o: CMakeFiles/rpc.dir/flags.make
CMakeFiles/rpc.dir/rpc.cpp.o: ../rpc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hermann/Ucu/OS_2019/Project/bfs/rpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/rpc.dir/rpc.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rpc.dir/rpc.cpp.o -c /home/hermann/Ucu/OS_2019/Project/bfs/rpc/rpc.cpp

CMakeFiles/rpc.dir/rpc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rpc.dir/rpc.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hermann/Ucu/OS_2019/Project/bfs/rpc/rpc.cpp > CMakeFiles/rpc.dir/rpc.cpp.i

CMakeFiles/rpc.dir/rpc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rpc.dir/rpc.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hermann/Ucu/OS_2019/Project/bfs/rpc/rpc.cpp -o CMakeFiles/rpc.dir/rpc.cpp.s

# Object files for target rpc
rpc_OBJECTS = \
"CMakeFiles/rpc.dir/main.cpp.o" \
"CMakeFiles/rpc.dir/rpc.cpp.o"

# External object files for target rpc
rpc_EXTERNAL_OBJECTS =

rpc: CMakeFiles/rpc.dir/main.cpp.o
rpc: CMakeFiles/rpc.dir/rpc.cpp.o
rpc: CMakeFiles/rpc.dir/build.make
rpc: /usr/lib64/libboost_locale.so.1.71.0
rpc: /usr/lib/libcryptopp.so
rpc: /usr/lib64/libboost_chrono.so.1.71.0
rpc: /usr/lib64/libboost_system.so.1.71.0
rpc: /usr/lib64/libboost_thread.so.1.71.0
rpc: CMakeFiles/rpc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hermann/Ucu/OS_2019/Project/bfs/rpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable rpc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rpc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rpc.dir/build: rpc

.PHONY : CMakeFiles/rpc.dir/build

CMakeFiles/rpc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rpc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rpc.dir/clean

CMakeFiles/rpc.dir/depend:
	cd /home/hermann/Ucu/OS_2019/Project/bfs/rpc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hermann/Ucu/OS_2019/Project/bfs/rpc /home/hermann/Ucu/OS_2019/Project/bfs/rpc /home/hermann/Ucu/OS_2019/Project/bfs/rpc/build /home/hermann/Ucu/OS_2019/Project/bfs/rpc/build /home/hermann/Ucu/OS_2019/Project/bfs/rpc/build/CMakeFiles/rpc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rpc.dir/depend
