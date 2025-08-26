include_directories(. .. ../core ../jive)

Y_CreateLibrary(y-chemical
y/chemical
y/chemical/weasel
y/chemical/type
y/chemical/reactive
y/chemical/weasel/formula
)

add_subdirectory(tests)
Y_Regression(chemical)
