Y_CreateTest(test-json)
Y_LinkLibraries(test-json y-json y-jive)

enable_testing()

Y_Message("Preparing ${Y_Test}")

Y_UTEST(compiler)
