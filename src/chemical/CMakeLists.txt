include_directories(. .. ../core ../jive ../lua++ ../y/lua/src ../mkl)

Y_CreateLibrary(y-chemical
y/chemical
y/chemical/weasel
y/chemical/type
y/chemical/reactive
y/chemical/weasel/formula
y/chemical/weasel/equilibrium
y/chemical/plexus
y/chemical/plexus/cluster
y/chemical/plexus/conservation
y/chemical/plexus/solver
)

add_subdirectory(tests)
Y_Regression(chemical)

add_subdirectory(ionocell)

