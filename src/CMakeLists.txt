file(GLOB SRC_FILES *.cpp)

add_executable(app ${SRC_FILES})

target_link_libraries(app PUBLIC matplot)
