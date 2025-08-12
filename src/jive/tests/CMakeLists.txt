Y_CreateTest(test-jive)
Y_LinkLibraries(test-jive y-jive)

enable_testing()

Y_Message("Preparing ${Y_Test}")

Y_UTEST(tag)
Y_UTEST(source)
Y_UTEST(fc)
Y_UTEST(pattern)
Y_UTEST(posix)
Y_UTEST(rx)
Y_UTEST(scanner)
Y_UTEST(lexer)
Y_UTEST(xnode)
Y_UTEST(grammar)
