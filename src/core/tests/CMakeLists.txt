


Y_CreateTest(test-core
core
system)

target_link_libraries(test-core y)

enable_testing()

Y_UTEST(exception)

# core
Y_UTEST(core:variadic)

# system
Y_UTEST(system:error 1 2)
