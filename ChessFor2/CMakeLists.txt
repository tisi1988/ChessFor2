# check for requirements
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS})

# Gather source and header files
file(GLOB_RECURSE SOURCEFILES INC_ALL ${CMAKE_SOURCE_DIR}/ChessFor2/*.cpp)
file(GLOB_RECURSE HEADERS INC_ALL ${CMAKE_SOURCE_DIR}/ChessFor2/*.h)

set(TARGET_NAME "ChessFor2")

# add the library target
add_executable(${TARGET_NAME} ${SOURCEFILES} ${HEADERS})
target_link_libraries(${TARGET_NAME} SDL2 SDL2_image SDL2_ttf pthread)

include_directories("${CMAKE_BINARY_DIR}/include")

configure_file(config.h.in "${CMAKE_SOURCE_DIR}/ChessFor2/config.h")

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       "${CMAKE_SOURCE_DIR}/${TARGET_NAME}/1280px-Chess_Pieces_Sprite.png" "${CMAKE_BINARY_DIR}/${TARGET_NAME}/pieces.png")

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                  COMMAND ${CMAKE_COMMAND} -E copy
                      "${CMAKE_SOURCE_DIR}/${TARGET_NAME}/FreeSans.ttf" "${CMAKE_BINARY_DIR}/${TARGET_NAME}/FreeSans.ttf")
