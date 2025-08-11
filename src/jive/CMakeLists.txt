include_directories(. .. ../core)

Y_CreateLibrary(y-jive
y/jive
y/jive/pattern
y/jive/pattern/basic
y/jive/pattern/joker
y/jive/pattern/logic
y/jive/regexp
y/jive/lexical
y/jive/lexical/comment
y/jive/lexical/plugin
y/jive/syntax
y/jive/babel
)

add_subdirectory(tests)
Y_Regression(jive)
