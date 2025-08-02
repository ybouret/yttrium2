Y_CreateTest(test-jive)
Y_LinkLibraries(test-jive y-jive)

enable_testing()

Y_Message("Preparing ${Y_Test}")

Y_UTEST(source)
