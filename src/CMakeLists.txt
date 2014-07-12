project("brainvolve")

add_subdirectory(neural)

file(GLOB SOURCE "./*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} neural)

