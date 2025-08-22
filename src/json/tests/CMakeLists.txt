Y_CreateTest(test-json)
Y_LinkLibraries(test-json y-json y-jive)

enable_testing()

Y_Message("Preparing ${Y_Test}")
set(VAR "${CMAKE_CURRENT_SOURCE_DIR}/../../../var")

add_test(db test-json compiler  ${VAR}/db.js)
add_test(sample1 test-json compiler  ${VAR}/sample1.js)
