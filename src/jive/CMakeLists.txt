include_directories(. .. ../core)

Y_CreateLibrary(y-jive
y/jive
)

add_subdirectory(tests)
Y_Regression(jive)
