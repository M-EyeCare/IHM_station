# Root Cmake. Use to link the different libraries
#
# @version 1.0

# ########################################################################################################
# ##                                       GENERAL CONFIG                                               ##
# ########################################################################################################

message("%%% SYNTHESIS PROJECT : MEyeConsult")
message("\n%% GENERAL CONFIGURATION")

# GENERAL SETTINGS
project(MEyeConsult CXX)
cmake_minimum_required(VERSION 3.2)
set(VERSION 1.0.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

set(APP_NAME IHM_Station)

# OUTPUT DIR SETTINGS
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)

# COMPILER OPTIONS
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG " -g3 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE " -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") # Warning : option are important for some lib

# #######################################################################################################
# ##                                       LIBRARY CONFIG                                              ##
# #######################################################################################################
message("\n%% EXTERNALS libs configuration")

message("- Checking : pkg")
find_package(PkgConfig REQUIRED)

if(PkgConfig_FOUND)
    message("-> succes ")
else()
    message("Fail : You must hae PkgConfig installed")
endif()

message("- Checking : Thread")
find_package(Threads)

message("- Checking : Qt6")
# find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets )
find_package(Qt6 REQUIRED COMPONENTS Charts )

# qt_standard_project_setup()

# #####################################################################################################
# ##                                            LINKS                                                ##
# #####################################################################################################
link_libraries(
    ${CMAKE_THREAD_LIBS_INIT}
)

# target_link_libraries(config++)
add_subdirectory(lib)
include_directories(lib)
include_directories(src)

# #####################################################################################################
# ##                                         APPLICATION                                             ##
# #####################################################################################################
message("\n%% APPLICATION GENERATION")

file(GLOB_RECURSE IHM_Station_SRC
    "lib/*.h"
    "src/*.h"
    "src/*.cpp"
)

# Copy the config file to the bin folder to make it run
# file(COPY config/config.cfg DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# %% App files
add_executable(${APP_NAME} ${IHM_Station_SRC})

target_link_libraries(${APP_NAME} PUBLIC

    # Qt6::Core
    Qt6::Widgets
    Qt6::Charts
)