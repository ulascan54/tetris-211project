cmake_minimum_required(VERSION 3.16)
project(cmake-tetris LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Globbing for header files
file(GLOB HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.h)

# Globbing for source files
file(GLOB SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(cmake-tetris ${SOURCE_FILES} ${HEADER_FILES})

# Link against all required SFML libraries
target_link_libraries(cmake-tetris PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

target_compile_features(cmake-tetris PRIVATE cxx_std_17)





configure_file(font/controls.otf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/font/controls.otf COPYONLY)
configure_file(font/PixelifySans-VariableFont_wght.ttf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/font/PixelifySans-VariableFont_wght.ttf COPYONLY)

file(GLOB MP3_FILES ${CMAKE_CURRENT_SOURCE_DIR}/sounds/*.mp3)
foreach(MP3_FILE ${MP3_FILES})
    get_filename_component(FILE_NAME ${MP3_FILE} NAME)
    configure_file(${MP3_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}//sounds/${FILE_NAME} COPYONLY)
endforeach()

file(GLOB PNG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/images/*.png)
foreach(PNG_FILE ${PNG_FILES})
    get_filename_component(FILE_NAME ${PNG_FILE} NAME)
    configure_file(${PNG_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/images/${FILE_NAME} COPYONLY)
endforeach()


configure_file(high_scores.txt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/high_scores.txt COPYONLY)


if(WIN32)
    add_custom_command(
        TARGET cmake-tetris
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:cmake-tetris>
        VERBATIM)
endif()

install(TARGETS cmake-tetris)
