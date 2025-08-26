include_directories(. .. ../core ../jive ../lua++ ../y/lua/src)

Y_CreateLibrary(y-chemical
y/chemical
y/chemical/weasel
y/chemical/type
y/chemical/reactive
y/chemical/weasel/formula
y/chemical/weasel/equilibrium
)

add_subdirectory(tests)
Y_Regression(chemical)
