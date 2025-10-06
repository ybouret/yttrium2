Y_CreateTest(test-chemical)
Y_LinkLibraries(test-chemical y-chemical y-json y-jive y-mkl y-lua++ y-lua)

enable_testing()

Y_Message("Preparing ${Y_Test}")
set(VAR "${CMAKE_CURRENT_SOURCE_DIR}/../../../var")

Y_UTEST(weasel)
Y_UTEST(species)
Y_UTEST(library)
Y_UTEST(solve1d)
Y_UTEST(plexus)
