
if(MSVC)
    add_compile_options(
        /std:c++17
        $<$<CONFIG:RELEASE>:/O2>
        $<$<CONFIG:DEBUG>:/Od>
        $<$<CONFIG:DEBUG>:/Zi>)
elseif(UNIX)
    addd_compile_options(
        -Wall -Wextra -pedantic -Werror
        $<$<CONFIG:RELEASE>:-Ofast>
        $<$<CONFIG:DEBUG>:-g3>
        $<$<CONFIG:DEBUG>:-O0>)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)


set(Sources 
            Game.cpp
            Player.cpp 
            Object.cpp
            main.cpp)
set (Headers
            Game.h
            Player.h
            Object.h)


add_executable(${PROJECT_NAME} ${Sources})
target_include_directories(${PROJECT_NAME} PRIVATE ${Headers})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()

install(TARGETS ${PROJECT_NAME})
# add_executable(app main.cpp Game.cpp Object.cpp Player.cpp)
# target_link_libraries(app PRIVATE sfml-graphics)

# if (WIN32 AND BUILD_SHARED_LIBS)
#     add_custom_command(TARGET app POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:app> $<TARGET_FILE_DIR:app> COMMAND_EXPAND_LISTS)
# endif()
