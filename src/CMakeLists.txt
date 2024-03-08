if (USE_GLOB)
    file(GLOB_RECURSE SOURCES *.h *.hpp *.cpp)
    add_library(${MODULE_NAME} STATIC ${SOURCES})
else ()
    set(HEADERS
        iterative/gauss-seidel.h
        )

    set(SOURCES
        )

    source_group("Header Files" FILES ${HEADERS})
    source_group("Source Files" FILES ${SOURCES})

    add_library(${PROJECT_NAME} INTERFACE ${HEADERS} ${SOURCES})
    #add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
endif ()

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)
