


Y_CreateTest(test-core
system)

target_link_libraries(test-core y)

enable_testing()
Y_UTest(system:error 1 2)
