include_directories(../core)

add_library(module MODULE module.c)
add_library(cxxmod MODULE cxxmod.cpp)
add_executable(loader loader.cpp)
Y_LinkLibraries(loader)

add_custom_command( TARGET loader POST_BUILD
    COMMAND $<TARGET_FILE:loader> $<TARGET_FILE:module>
    COMMAND $<TARGET_FILE:loader> $<TARGET_FILE:cxxmod>
    COMMENT "Testing DLL Loader"
)
