# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zedlin/mywebserver02

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zedlin/mywebserver02/build

# Include any dependencies generated for this target.
include CMakeFiles/MyExecutable.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyExecutable.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyExecutable.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyExecutable.dir/flags.make

CMakeFiles/MyExecutable.dir/main.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/main.cpp.o: ../main.cpp
CMakeFiles/MyExecutable.dir/main.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zedlin/mywebserver02/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyExecutable.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/main.cpp.o -MF CMakeFiles/MyExecutable.dir/main.cpp.o.d -o CMakeFiles/MyExecutable.dir/main.cpp.o -c /home/zedlin/mywebserver02/main.cpp

CMakeFiles/MyExecutable.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zedlin/mywebserver02/main.cpp > CMakeFiles/MyExecutable.dir/main.cpp.i

CMakeFiles/MyExecutable.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zedlin/mywebserver02/main.cpp -o CMakeFiles/MyExecutable.dir/main.cpp.s

CMakeFiles/MyExecutable.dir/src/buffer/buffer.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/buffer/buffer.cpp.o: ../src/buffer/buffer.cpp
CMakeFiles/MyExecutable.dir/src/buffer/buffer.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zedlin/mywebserver02/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MyExecutable.dir/src/buffer/buffer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/buffer/buffer.cpp.o -MF CMakeFiles/MyExecutable.dir/src/buffer/buffer.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/buffer/buffer.cpp.o -c /home/zedlin/mywebserver02/src/buffer/buffer.cpp

CMakeFiles/MyExecutable.dir/src/buffer/buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/buffer/buffer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zedlin/mywebserver02/src/buffer/buffer.cpp > CMakeFiles/MyExecutable.dir/src/buffer/buffer.cpp.i

CMakeFiles/MyExecutable.dir/src/buffer/buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/buffer/buffer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zedlin/mywebserver02/src/buffer/buffer.cpp -o CMakeFiles/MyExecutable.dir/src/buffer/buffer.cpp.s

CMakeFiles/MyExecutable.dir/src/config/config.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/config/config.cpp.o: ../src/config/config.cpp
CMakeFiles/MyExecutable.dir/src/config/config.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zedlin/mywebserver02/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MyExecutable.dir/src/config/config.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/config/config.cpp.o -MF CMakeFiles/MyExecutable.dir/src/config/config.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/config/config.cpp.o -c /home/zedlin/mywebserver02/src/config/config.cpp

CMakeFiles/MyExecutable.dir/src/config/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/config/config.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zedlin/mywebserver02/src/config/config.cpp > CMakeFiles/MyExecutable.dir/src/config/config.cpp.i

CMakeFiles/MyExecutable.dir/src/config/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/config/config.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zedlin/mywebserver02/src/config/config.cpp -o CMakeFiles/MyExecutable.dir/src/config/config.cpp.s

CMakeFiles/MyExecutable.dir/src/http/httpconn.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/http/httpconn.cpp.o: ../src/http/httpconn.cpp
CMakeFiles/MyExecutable.dir/src/http/httpconn.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zedlin/mywebserver02/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MyExecutable.dir/src/http/httpconn.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/http/httpconn.cpp.o -MF CMakeFiles/MyExecutable.dir/src/http/httpconn.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/http/httpconn.cpp.o -c /home/zedlin/mywebserver02/src/http/httpconn.cpp

CMakeFiles/MyExecutable.dir/src/http/httpconn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/http/httpconn.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zedlin/mywebserver02/src/http/httpconn.cpp > CMakeFiles/MyExecutable.dir/src/http/httpconn.cpp.i

CMakeFiles/MyExecutable.dir/src/http/httpconn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/http/httpconn.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zedlin/mywebserver02/src/http/httpconn.cpp -o CMakeFiles/MyExecutable.dir/src/http/httpconn.cpp.s

CMakeFiles/MyExecutable.dir/src/http/httprequest.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/http/httprequest.cpp.o: ../src/http/httprequest.cpp
CMakeFiles/MyExecutable.dir/src/http/httprequest.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zedlin/mywebserver02/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MyExecutable.dir/src/http/httprequest.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/http/httprequest.cpp.o -MF CMakeFiles/MyExecutable.dir/src/http/httprequest.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/http/httprequest.cpp.o -c /home/zedlin/mywebserver02/src/http/httprequest.cpp

CMakeFiles/MyExecutable.dir/src/http/httprequest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/http/httprequest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zedlin/mywebserver02/src/http/httprequest.cpp > CMakeFiles/MyExecutable.dir/src/http/httprequest.cpp.i

CMakeFiles/MyExecutable.dir/src/http/httprequest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/http/httprequest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zedlin/mywebserver02/src/http/httprequest.cpp -o CMakeFiles/MyExecutable.dir/src/http/httprequest.cpp.s

CMakeFiles/MyExecutable.dir/src/http/httpresponse.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/http/httpresponse.cpp.o: ../src/http/httpresponse.cpp
CMakeFiles/MyExecutable.dir/src/http/httpresponse.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zedlin/mywebserver02/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/MyExecutable.dir/src/http/httpresponse.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/http/httpresponse.cpp.o -MF CMakeFiles/MyExecutable.dir/src/http/httpresponse.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/http/httpresponse.cpp.o -c /home/zedlin/mywebserver02/src/http/httpresponse.cpp

CMakeFiles/MyExecutable.dir/src/http/httpresponse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/http/httpresponse.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zedlin/mywebserver02/src/http/httpresponse.cpp > CMakeFiles/MyExecutable.dir/src/http/httpresponse.cpp.i

CMakeFiles/MyExecutable.dir/src/http/httpresponse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/http/httpresponse.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zedlin/mywebserver02/src/http/httpresponse.cpp -o CMakeFiles/MyExecutable.dir/src/http/httpresponse.cpp.s

CMakeFiles/MyExecutable.dir/src/log/log.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/log/log.cpp.o: ../src/log/log.cpp
CMakeFiles/MyExecutable.dir/src/log/log.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zedlin/mywebserver02/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/MyExecutable.dir/src/log/log.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/log/log.cpp.o -MF CMakeFiles/MyExecutable.dir/src/log/log.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/log/log.cpp.o -c /home/zedlin/mywebserver02/src/log/log.cpp

CMakeFiles/MyExecutable.dir/src/log/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/log/log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zedlin/mywebserver02/src/log/log.cpp > CMakeFiles/MyExecutable.dir/src/log/log.cpp.i

CMakeFiles/MyExecutable.dir/src/log/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/log/log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zedlin/mywebserver02/src/log/log.cpp -o CMakeFiles/MyExecutable.dir/src/log/log.cpp.s

CMakeFiles/MyExecutable.dir/src/pool/sqlconnpool.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/pool/sqlconnpool.cpp.o: ../src/pool/sqlconnpool.cpp
CMakeFiles/MyExecutable.dir/src/pool/sqlconnpool.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zedlin/mywebserver02/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/MyExecutable.dir/src/pool/sqlconnpool.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/pool/sqlconnpool.cpp.o -MF CMakeFiles/MyExecutable.dir/src/pool/sqlconnpool.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/pool/sqlconnpool.cpp.o -c /home/zedlin/mywebserver02/src/pool/sqlconnpool.cpp

CMakeFiles/MyExecutable.dir/src/pool/sqlconnpool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/pool/sqlconnpool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zedlin/mywebserver02/src/pool/sqlconnpool.cpp > CMakeFiles/MyExecutable.dir/src/pool/sqlconnpool.cpp.i

CMakeFiles/MyExecutable.dir/src/pool/sqlconnpool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/pool/sqlconnpool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zedlin/mywebserver02/src/pool/sqlconnpool.cpp -o CMakeFiles/MyExecutable.dir/src/pool/sqlconnpool.cpp.s

CMakeFiles/MyExecutable.dir/src/server/epoller.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/server/epoller.cpp.o: ../src/server/epoller.cpp
CMakeFiles/MyExecutable.dir/src/server/epoller.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zedlin/mywebserver02/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/MyExecutable.dir/src/server/epoller.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/server/epoller.cpp.o -MF CMakeFiles/MyExecutable.dir/src/server/epoller.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/server/epoller.cpp.o -c /home/zedlin/mywebserver02/src/server/epoller.cpp

CMakeFiles/MyExecutable.dir/src/server/epoller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/server/epoller.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zedlin/mywebserver02/src/server/epoller.cpp > CMakeFiles/MyExecutable.dir/src/server/epoller.cpp.i

CMakeFiles/MyExecutable.dir/src/server/epoller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/server/epoller.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zedlin/mywebserver02/src/server/epoller.cpp -o CMakeFiles/MyExecutable.dir/src/server/epoller.cpp.s

CMakeFiles/MyExecutable.dir/src/server/webserver.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/server/webserver.cpp.o: ../src/server/webserver.cpp
CMakeFiles/MyExecutable.dir/src/server/webserver.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zedlin/mywebserver02/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/MyExecutable.dir/src/server/webserver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/server/webserver.cpp.o -MF CMakeFiles/MyExecutable.dir/src/server/webserver.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/server/webserver.cpp.o -c /home/zedlin/mywebserver02/src/server/webserver.cpp

CMakeFiles/MyExecutable.dir/src/server/webserver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/server/webserver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zedlin/mywebserver02/src/server/webserver.cpp > CMakeFiles/MyExecutable.dir/src/server/webserver.cpp.i

CMakeFiles/MyExecutable.dir/src/server/webserver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/server/webserver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zedlin/mywebserver02/src/server/webserver.cpp -o CMakeFiles/MyExecutable.dir/src/server/webserver.cpp.s

CMakeFiles/MyExecutable.dir/src/timer/timer.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/timer/timer.cpp.o: ../src/timer/timer.cpp
CMakeFiles/MyExecutable.dir/src/timer/timer.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zedlin/mywebserver02/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/MyExecutable.dir/src/timer/timer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/timer/timer.cpp.o -MF CMakeFiles/MyExecutable.dir/src/timer/timer.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/timer/timer.cpp.o -c /home/zedlin/mywebserver02/src/timer/timer.cpp

CMakeFiles/MyExecutable.dir/src/timer/timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/timer/timer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zedlin/mywebserver02/src/timer/timer.cpp > CMakeFiles/MyExecutable.dir/src/timer/timer.cpp.i

CMakeFiles/MyExecutable.dir/src/timer/timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/timer/timer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zedlin/mywebserver02/src/timer/timer.cpp -o CMakeFiles/MyExecutable.dir/src/timer/timer.cpp.s

# Object files for target MyExecutable
MyExecutable_OBJECTS = \
"CMakeFiles/MyExecutable.dir/main.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/buffer/buffer.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/config/config.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/http/httpconn.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/http/httprequest.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/http/httpresponse.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/log/log.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/pool/sqlconnpool.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/server/epoller.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/server/webserver.cpp.o" \
"CMakeFiles/MyExecutable.dir/src/timer/timer.cpp.o"

# External object files for target MyExecutable
MyExecutable_EXTERNAL_OBJECTS =

../bin/MyExecutable: CMakeFiles/MyExecutable.dir/main.cpp.o
../bin/MyExecutable: CMakeFiles/MyExecutable.dir/src/buffer/buffer.cpp.o
../bin/MyExecutable: CMakeFiles/MyExecutable.dir/src/config/config.cpp.o
../bin/MyExecutable: CMakeFiles/MyExecutable.dir/src/http/httpconn.cpp.o
../bin/MyExecutable: CMakeFiles/MyExecutable.dir/src/http/httprequest.cpp.o
../bin/MyExecutable: CMakeFiles/MyExecutable.dir/src/http/httpresponse.cpp.o
../bin/MyExecutable: CMakeFiles/MyExecutable.dir/src/log/log.cpp.o
../bin/MyExecutable: CMakeFiles/MyExecutable.dir/src/pool/sqlconnpool.cpp.o
../bin/MyExecutable: CMakeFiles/MyExecutable.dir/src/server/epoller.cpp.o
../bin/MyExecutable: CMakeFiles/MyExecutable.dir/src/server/webserver.cpp.o
../bin/MyExecutable: CMakeFiles/MyExecutable.dir/src/timer/timer.cpp.o
../bin/MyExecutable: CMakeFiles/MyExecutable.dir/build.make
../bin/MyExecutable: CMakeFiles/MyExecutable.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zedlin/mywebserver02/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable ../bin/MyExecutable"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyExecutable.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyExecutable.dir/build: ../bin/MyExecutable
.PHONY : CMakeFiles/MyExecutable.dir/build

CMakeFiles/MyExecutable.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyExecutable.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyExecutable.dir/clean

CMakeFiles/MyExecutable.dir/depend:
	cd /home/zedlin/mywebserver02/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zedlin/mywebserver02 /home/zedlin/mywebserver02 /home/zedlin/mywebserver02/build /home/zedlin/mywebserver02/build /home/zedlin/mywebserver02/build/CMakeFiles/MyExecutable.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyExecutable.dir/depend
