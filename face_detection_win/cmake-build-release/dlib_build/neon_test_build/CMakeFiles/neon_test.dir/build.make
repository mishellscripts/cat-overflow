# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.3.4\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.3.4\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\dlib\dlib\cmake_utils\test_for_neon

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\OneDrive\CS\CS160\cs160_stackoverflow\face_detection_win\cmake-build-release\dlib_build\neon_test_build

# Include any dependencies generated for this target.
include CMakeFiles\neon_test.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\neon_test.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\neon_test.dir\flags.make

CMakeFiles\neon_test.dir\neon_test.cpp.obj: CMakeFiles\neon_test.dir\flags.make
CMakeFiles\neon_test.dir\neon_test.cpp.obj: C:\dlib\dlib\cmake_utils\test_for_neon\neon_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=D:\OneDrive\CS\CS160\cs160_stackoverflow\face_detection_win\cmake-build-release\dlib_build\neon_test_build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/neon_test.dir/neon_test.cpp.obj"
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1410~1.250\bin\HostX86\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\neon_test.dir\neon_test.cpp.obj /FdCMakeFiles\neon_test.dir\neon_test.pdb /FS -c C:\dlib\dlib\cmake_utils\test_for_neon\neon_test.cpp
<<

CMakeFiles\neon_test.dir\neon_test.cpp.i: cmake_force
	@echo Preprocessing CXX source to CMakeFiles/neon_test.dir/neon_test.cpp.i
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1410~1.250\bin\HostX86\x64\cl.exe > CMakeFiles\neon_test.dir\neon_test.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\dlib\dlib\cmake_utils\test_for_neon\neon_test.cpp
<<

CMakeFiles\neon_test.dir\neon_test.cpp.s: cmake_force
	@echo Compiling CXX source to assembly CMakeFiles/neon_test.dir/neon_test.cpp.s
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1410~1.250\bin\HostX86\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\neon_test.dir\neon_test.cpp.s /c C:\dlib\dlib\cmake_utils\test_for_neon\neon_test.cpp
<<

CMakeFiles\neon_test.dir\neon_test.cpp.obj.requires:

.PHONY : CMakeFiles\neon_test.dir\neon_test.cpp.obj.requires

CMakeFiles\neon_test.dir\neon_test.cpp.obj.provides: CMakeFiles\neon_test.dir\neon_test.cpp.obj.requires
	$(MAKE) -f CMakeFiles\neon_test.dir\build.make /nologo -$(MAKEFLAGS) CMakeFiles\neon_test.dir\neon_test.cpp.obj.provides.build
.PHONY : CMakeFiles\neon_test.dir\neon_test.cpp.obj.provides

CMakeFiles\neon_test.dir\neon_test.cpp.obj.provides.build: CMakeFiles\neon_test.dir\neon_test.cpp.obj


# Object files for target neon_test
neon_test_OBJECTS = \
"CMakeFiles\neon_test.dir\neon_test.cpp.obj"

# External object files for target neon_test
neon_test_EXTERNAL_OBJECTS =

neon_test.lib: CMakeFiles\neon_test.dir\neon_test.cpp.obj
neon_test.lib: CMakeFiles\neon_test.dir\build.make
neon_test.lib: CMakeFiles\neon_test.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=D:\OneDrive\CS\CS160\cs160_stackoverflow\face_detection_win\cmake-build-release\dlib_build\neon_test_build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library neon_test.lib"
	$(CMAKE_COMMAND) -P CMakeFiles\neon_test.dir\cmake_clean_target.cmake
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1410~1.250\bin\HostX86\x64\link.exe /lib /nologo /machine:x64 /out:neon_test.lib @CMakeFiles\neon_test.dir\objects1.rsp 

# Rule to build all files generated by this target.
CMakeFiles\neon_test.dir\build: neon_test.lib

.PHONY : CMakeFiles\neon_test.dir\build

CMakeFiles\neon_test.dir\requires: CMakeFiles\neon_test.dir\neon_test.cpp.obj.requires

.PHONY : CMakeFiles\neon_test.dir\requires

CMakeFiles\neon_test.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\neon_test.dir\cmake_clean.cmake
.PHONY : CMakeFiles\neon_test.dir\clean

CMakeFiles\neon_test.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\dlib\dlib\cmake_utils\test_for_neon C:\dlib\dlib\cmake_utils\test_for_neon D:\OneDrive\CS\CS160\cs160_stackoverflow\face_detection_win\cmake-build-release\dlib_build\neon_test_build D:\OneDrive\CS\CS160\cs160_stackoverflow\face_detection_win\cmake-build-release\dlib_build\neon_test_build D:\OneDrive\CS\CS160\cs160_stackoverflow\face_detection_win\cmake-build-release\dlib_build\neon_test_build\CMakeFiles\neon_test.dir\DependInfo.cmake
.PHONY : CMakeFiles\neon_test.dir\depend

