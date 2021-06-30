cmake_minimum_required(VERSION 2.8.4)

# define arduino SDK path
message( "ARDUINO_SDK_PATH=$ENV{ARDUINO_SDK_PATH}")
set(ARDUINO_SDK_PATH $ENV{ARDUINO_SDK_PATH})

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME balanced_car)

set(${PROJECT_NAME}_BOARD nano)
set(ARDUINO_CPU atmega328)
project(${PROJECT_NAME})

# Define additional source and header files or default arduino sketch files
# set(${PROJECT_NAME}_SRCS)
# set(${PROJECT_NAME}_HDRS)

### Additional static libraries to include in the target.
# set(${PROJECT_NAME}_LIBS)

### Main sketch file
set(${PROJECT_NAME}_SKETCH balanced_car.ino)

### Add project directories into the build
# add_subdirectory()

### Additional settings to add non-standard or your own Arduino libraries.
# For this example (libs will contain additional arduino libraries)
# An Arduino library my_lib will contain files in libs/my_lib/: my_lib.h, my_lib.cpp + any other cpp files
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

# For nested library sources replace ${LIB_NAME} with library name for each library
# set(_RECURSE true)

#### Additional settings for programmer. From programmers.txt
# set(${PROJECT_NAME}_PROGRAMMER avrispmkii)
# set(${PROJECT_NAME}_PORT /dev/cu.usbserial-00000000)
set(nano.upload.speed 9600)

## Verbose build process
set(${PROJECT_NAME}_AFLAGS -v)

#set(INPUT_BOARD )

generate_arduino_firmware(${PROJECT_NAME})


print_board_list()
print_programmer_list()
