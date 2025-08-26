
Y_CreateTest(test-lua++)

Y_LinkLibraries(test-lua++ y-lua++ y-lua)

Y_Message("Preparing ${Y_Test}")

set( HERE ${CMAKE_CURRENT_SOURCE_DIR} )

enable_testing()

Y_UTEST(state  ${HERE}/sample.lua)
Y_UTEST(function)

#add_test(state    test-lua++ state ${HERE}/sample.lua)
#add_test(function test-lua++ function)
