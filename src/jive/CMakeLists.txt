include_directories(. .. ../core)

Y_CreateLibrary(y-jive
y/jive
y/jive/pattern
y/jive/pattern/basic
)

add_subdirectory(tests)
Y_Regression(jive)
