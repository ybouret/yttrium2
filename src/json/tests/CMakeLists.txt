Y_CreateTest(test-json)
Y_LinkLibraries(test-json y-json y-jive)

enable_testing()

Y_Message("Preparing ${Y_Test}")
set(VAR "${CMAKE_CURRENT_SOURCE_DIR}/../../../var")

add_test(db      test-json compiler  ${VAR}/db.js)
add_test(sample1 test-json compiler  ${VAR}/sample1.js)
add_test(sample2 test-json compiler  ${VAR}/sample2.js)
add_test(sample3 test-json compiler  ${VAR}/sample3.js)
add_test(sample4 test-json compiler  ${VAR}/sample4.js)
