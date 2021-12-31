# check for requirements
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Gather source and header files
file(GLOB_RECURSE SOURCEFILES INC_ALL ${CMAKE_SOURCE_DIR}/ChessFor2/*.cpp)
file(GLOB_RECURSE HEADERS INC_ALL ${CMAKE_SOURCE_DIR}/ChessFor2/*.h)

# add the library target
add_executable(ChessFor2 ${SOURCEFILES} ${HEADERS})
target_link_libraries(ChessFor2 SDL2 pthread)

include_directories("${CMAKE_BINARY_DIR}/include")

configure_file(config.h.in "${CMAKE_SOURCE_DIR}/ChessFor2/config.h")

