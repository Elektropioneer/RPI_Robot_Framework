#
# This file is part of the RPI Robot Framework distribution (https://github.com/Elektropioneer/RPI_Robot_Framework).
# Copyright (c) 2020 Miloš Zivlak (milos.zivlak@sensa-group.net).
# 
# This program is free software: you can redistribute it and/or modify  
# it under the terms of the GNU General Public License as published by  
# the Free Software Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
# General Public License for more details.
#
#* You should have received a copy of the GNU General Public License 
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 2.8.11)
project(rrf)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Lua51 REQUIRED)

find_package(Threads REQUIRED)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(include/)
include_directories(${CMAKE_BINARY_DIR})
include_directories(lib/spdlog/include)
include_directories(${LUA_INCLUDE_DIR})
include_directories(lib/WiringPi)

# JSON Library
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(lib/json)

set(project_SRC
    src/core/Settings.cpp
    src/core/Log.cpp
    src/core/SerialMessage.cpp
    src/core/Serial.cpp
    src/core/RobotFramework.cpp

    src/main.cpp
)

set(project_INCLUDE
)

set(project_LIB
    nlohmann_json::nlohmann_json
    ${LUA_LIBRARIES}
)

set(project_LIB_SRC
    lib/WiringPi/wiringSerial.c
)

# Tell CMake to create the rrf executable
add_executable(rrf ${project_SRC} ${project_LIB_SRC})

# Tell CMake to link the rrf executable
target_link_libraries(rrf ${project_LIB} Threads::Threads)

# Install the executable
install(TARGETS rrf DESTINATION bin)
