file(GLOB_RECURSE SOURCES *.h *.hpp *.cpp)
add_library(${PROJECT_NAME} INTERFACE ${HEADERS} ${SOURCES})


target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)