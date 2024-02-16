if (USE_GLOB)
    file(GLOB_RECURSE SOURCES *.h *.hpp *.cpp)
    add_library(${MODULE_NAME} STATIC ${SOURCES})
else ()
    set(HEADERS
        tridiag/tridiagonal.h
        )

    set(SOURCES
        tridiag/tridiagonal.cpp
        )

    source_group("Header Files" FILES ${HEADERS})
    source_group("Source Files" FILES ${SOURCES})

    add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
