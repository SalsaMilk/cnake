# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\mitch\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\212.5284.51\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\mitch\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\212.5284.51\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\mitch\Documents\GitHub\cnake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\mitch\Documents\GitHub\cnake\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\cnake.dir\depend.make
# Include the progress variables for this target.
include CMakeFiles\cnake.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\cnake.dir\flags.make

CMakeFiles\cnake.dir\main.c.obj: CMakeFiles\cnake.dir\flags.make
CMakeFiles\cnake.dir\main.c.obj: ..\main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\mitch\Documents\GitHub\cnake\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cnake.dir/main.c.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\cnake.dir\main.c.obj /FdCMakeFiles\cnake.dir\ /FS -c C:\Users\mitch\Documents\GitHub\cnake\main.c
<<

CMakeFiles\cnake.dir\main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cnake.dir/main.c.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe > CMakeFiles\cnake.dir\main.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\mitch\Documents\GitHub\cnake\main.c
<<

CMakeFiles\cnake.dir\main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cnake.dir/main.c.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\cnake.dir\main.c.s /c C:\Users\mitch\Documents\GitHub\cnake\main.c
<<

# Object files for target cnake
cnake_OBJECTS = \
"CMakeFiles\cnake.dir\main.c.obj"

# External object files for target cnake
cnake_EXTERNAL_OBJECTS =

cnake.exe: CMakeFiles\cnake.dir\main.c.obj
cnake.exe: CMakeFiles\cnake.dir\build.make
cnake.exe: ..\lib\SDL2.lib
cnake.exe: ..\lib\SDL2_image.lib
cnake.exe: ..\lib\SDL2_ttf.lib
cnake.exe: ..\lib\SDL2main.lib
cnake.exe: ..\lib\SDL2test.lib
cnake.exe: CMakeFiles\cnake.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\mitch\Documents\GitHub\cnake\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cnake.exe"
	C:\Users\mitch\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\212.5284.51\bin\cmake\win\bin\cmake.exe -E vs_link_exe --intdir=CMakeFiles\cnake.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\mt.exe --manifests -- C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\link.exe /nologo @CMakeFiles\cnake.dir\objects1.rsp @<<
 /out:cnake.exe /implib:cnake.lib /pdb:C:\Users\mitch\Documents\GitHub\cnake\cmake-build-debug\cnake.pdb /version:0.0 /machine:x64 /debug /INCREMENTAL /subsystem:console  ..\lib\SDL2.lib ..\lib\SDL2_image.lib ..\lib\SDL2_ttf.lib ..\lib\SDL2main.lib ..\lib\SDL2test.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\cnake.dir\build: cnake.exe
.PHONY : CMakeFiles\cnake.dir\build

CMakeFiles\cnake.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\cnake.dir\cmake_clean.cmake
.PHONY : CMakeFiles\cnake.dir\clean

CMakeFiles\cnake.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\mitch\Documents\GitHub\cnake C:\Users\mitch\Documents\GitHub\cnake C:\Users\mitch\Documents\GitHub\cnake\cmake-build-debug C:\Users\mitch\Documents\GitHub\cnake\cmake-build-debug C:\Users\mitch\Documents\GitHub\cnake\cmake-build-debug\CMakeFiles\cnake.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\cnake.dir\depend
