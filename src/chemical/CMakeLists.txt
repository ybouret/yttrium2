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

set(HERE ${CMAKE_CURRENT_SOURCE_DIR})
set(TARGET ${HERE}/y/chemical/difftab.inc)
set(SOURCE ${HERE}/y/ionocell/diffusion-coefficient-table.js)

add_custom_command(OUTPUT ${TARGET}
    COMMAND y_embed ARGS ${SOURCE} ${TARGET}
    COMMENT "Embedding Diffusion Coefficients"
    VERBATIM
)

add_subdirectory(tests)
Y_Regression(chemical)

add_subdirectory(ionocell)

