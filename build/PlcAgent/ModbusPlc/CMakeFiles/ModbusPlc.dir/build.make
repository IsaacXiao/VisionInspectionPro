# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = E:/Programming/CMake/bin/cmake.exe

# The command to remove a file.
RM = E:/Programming/CMake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:/WorkSpace/VsCode-Cpp/Test/Inspection/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:/WorkSpace/VsCode-Cpp/Test/Inspection/build

# Include any dependencies generated for this target.
include PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/depend.make

# Include the progress variables for this target.
include PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/progress.make

# Include the compile flags for this target's objects.
include PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/flags.make

PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/ModbusPlc.cpp.obj: PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/flags.make
PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/ModbusPlc.cpp.obj: PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/includes_CXX.rsp
PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/ModbusPlc.cpp.obj: D:/WorkSpace/VsCode-Cpp/Test/Inspection/src/PlcAgent/ModbusPlc/ModbusPlc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/WorkSpace/VsCode-Cpp/Test/Inspection/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/ModbusPlc.cpp.obj"
	cd D:/WorkSpace/VsCode-Cpp/Test/Inspection/build/PlcAgent/ModbusPlc && E:/Programming/mingw-w64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ModbusPlc.dir/ModbusPlc.cpp.obj -c D:/WorkSpace/VsCode-Cpp/Test/Inspection/src/PlcAgent/ModbusPlc/ModbusPlc.cpp

PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/ModbusPlc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ModbusPlc.dir/ModbusPlc.cpp.i"
	cd D:/WorkSpace/VsCode-Cpp/Test/Inspection/build/PlcAgent/ModbusPlc && E:/Programming/mingw-w64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/WorkSpace/VsCode-Cpp/Test/Inspection/src/PlcAgent/ModbusPlc/ModbusPlc.cpp > CMakeFiles/ModbusPlc.dir/ModbusPlc.cpp.i

PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/ModbusPlc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ModbusPlc.dir/ModbusPlc.cpp.s"
	cd D:/WorkSpace/VsCode-Cpp/Test/Inspection/build/PlcAgent/ModbusPlc && E:/Programming/mingw-w64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/WorkSpace/VsCode-Cpp/Test/Inspection/src/PlcAgent/ModbusPlc/ModbusPlc.cpp -o CMakeFiles/ModbusPlc.dir/ModbusPlc.cpp.s

PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/ModbusDll.cpp.obj: PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/flags.make
PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/ModbusDll.cpp.obj: PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/includes_CXX.rsp
PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/ModbusDll.cpp.obj: D:/WorkSpace/VsCode-Cpp/Test/Inspection/src/PlcAgent/ModbusPlc/ModbusDll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/WorkSpace/VsCode-Cpp/Test/Inspection/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/ModbusDll.cpp.obj"
	cd D:/WorkSpace/VsCode-Cpp/Test/Inspection/build/PlcAgent/ModbusPlc && E:/Programming/mingw-w64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ModbusPlc.dir/ModbusDll.cpp.obj -c D:/WorkSpace/VsCode-Cpp/Test/Inspection/src/PlcAgent/ModbusPlc/ModbusDll.cpp

PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/ModbusDll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ModbusPlc.dir/ModbusDll.cpp.i"
	cd D:/WorkSpace/VsCode-Cpp/Test/Inspection/build/PlcAgent/ModbusPlc && E:/Programming/mingw-w64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/WorkSpace/VsCode-Cpp/Test/Inspection/src/PlcAgent/ModbusPlc/ModbusDll.cpp > CMakeFiles/ModbusPlc.dir/ModbusDll.cpp.i

PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/ModbusDll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ModbusPlc.dir/ModbusDll.cpp.s"
	cd D:/WorkSpace/VsCode-Cpp/Test/Inspection/build/PlcAgent/ModbusPlc && E:/Programming/mingw-w64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/WorkSpace/VsCode-Cpp/Test/Inspection/src/PlcAgent/ModbusPlc/ModbusDll.cpp -o CMakeFiles/ModbusPlc.dir/ModbusDll.cpp.s

# Object files for target ModbusPlc
ModbusPlc_OBJECTS = \
"CMakeFiles/ModbusPlc.dir/ModbusPlc.cpp.obj" \
"CMakeFiles/ModbusPlc.dir/ModbusDll.cpp.obj"

# External object files for target ModbusPlc
ModbusPlc_EXTERNAL_OBJECTS =

PlcAgent/ModbusPlc/libModbusPlc.dll: PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/ModbusPlc.cpp.obj
PlcAgent/ModbusPlc/libModbusPlc.dll: PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/ModbusDll.cpp.obj
PlcAgent/ModbusPlc/libModbusPlc.dll: PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/build.make
PlcAgent/ModbusPlc/libModbusPlc.dll: D:/WorkSpace/VsCode-Cpp/Test/Inspection/3rd_lib/tinyxml/libtinyxml.a
PlcAgent/ModbusPlc/libModbusPlc.dll: PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/linklibs.rsp
PlcAgent/ModbusPlc/libModbusPlc.dll: PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:/WorkSpace/VsCode-Cpp/Test/Inspection/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libModbusPlc.dll"
	cd D:/WorkSpace/VsCode-Cpp/Test/Inspection/build/PlcAgent/ModbusPlc && E:/Programming/CMake/bin/cmake.exe -E rm -f CMakeFiles/ModbusPlc.dir/objects.a
	cd D:/WorkSpace/VsCode-Cpp/Test/Inspection/build/PlcAgent/ModbusPlc && E:/Programming/mingw-w64/bin/ar.exe cr CMakeFiles/ModbusPlc.dir/objects.a @CMakeFiles/ModbusPlc.dir/objects1.rsp
	cd D:/WorkSpace/VsCode-Cpp/Test/Inspection/build/PlcAgent/ModbusPlc && E:/Programming/mingw-w64/bin/c++.exe  -Wall -g -ggdb -shared -o libModbusPlc.dll -Wl,--out-implib,libModbusPlc.dll.a -Wl,--major-image-version,0,--minor-image-version,0 -Wl,--whole-archive CMakeFiles/ModbusPlc.dir/objects.a -Wl,--no-whole-archive @CMakeFiles/ModbusPlc.dir/linklibs.rsp

# Rule to build all files generated by this target.
PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/build: PlcAgent/ModbusPlc/libModbusPlc.dll

.PHONY : PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/build

PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/clean:
	cd D:/WorkSpace/VsCode-Cpp/Test/Inspection/build/PlcAgent/ModbusPlc && $(CMAKE_COMMAND) -P CMakeFiles/ModbusPlc.dir/cmake_clean.cmake
.PHONY : PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/clean

PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/WorkSpace/VsCode-Cpp/Test/Inspection/src D:/WorkSpace/VsCode-Cpp/Test/Inspection/src/PlcAgent/ModbusPlc D:/WorkSpace/VsCode-Cpp/Test/Inspection/build D:/WorkSpace/VsCode-Cpp/Test/Inspection/build/PlcAgent/ModbusPlc D:/WorkSpace/VsCode-Cpp/Test/Inspection/build/PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : PlcAgent/ModbusPlc/CMakeFiles/ModbusPlc.dir/depend

