


Y_CreateTest(test-core
core
type
system
calculus)

target_link_libraries(test-core y)

enable_testing()

Y_UTEST(exception)

# core
Y_UTEST(core:variadic)

# system
Y_UTEST(system:error 1 2)
Y_UTEST(system:at_exit)

# type
Y_UTEST(type:ints)

#calculus
Y_UTEST(calculus_integer_log2)
Y_UTEST(calculus_alignment)


