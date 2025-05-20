


Y_CreateTest(test-core
core
system)

target_link_libraries(test-core y)

enable_testing()

# core
Y_UTest(core:variadic)

# system
Y_UTest(system:error 1 2)
