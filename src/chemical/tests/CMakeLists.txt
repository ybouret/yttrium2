Y_CreateTest(test-chemical)
Y_LinkLibraries(test-chemical y-chemical y-jive)

enable_testing()

Y_Message("Preparing ${Y_Test}")
set(VAR "${CMAKE_CURRENT_SOURCE_DIR}/../../../var")

Y_UTEST(weasel)
