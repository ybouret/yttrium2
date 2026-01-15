Y_CreateTest(test-ink)
Y_LinkLibraries(test-ink y-ink)

enable_testing()

Y_Message("Preparing ${Y_Test}")
set(VAR "${CMAKE_CURRENT_SOURCE_DIR}/../../../var")

Y_UTEST(zflux)
Y_UTEST(bitmap)
Y_UTEST(pixmap)
Y_UTEST(broker)
