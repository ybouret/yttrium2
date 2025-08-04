include_directories(. .. ../core)

Y_CreateLibrary(y-jive
y/jive
y/jive/pattern
y/jive/pattern/basic
y/jive/pattern/joker
y/jive/pattern/logic
y/jive/regexp
)

add_subdirectory(tests)
Y_Regression(jive)
