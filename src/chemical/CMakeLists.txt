include_directories(. .. ../core ../jive ../lua++ ../y/lua/src ../mkl ../json)

Y_CreateLibrary(y-chemical
y/chemical
y/chemical/db
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
set(TARGET ${HERE}/y/chemical/db/iffusion-coefficients.hxx)
set(SOURCE ${HERE}/ionocell/diffusion-coefficients.js)
cmake_print_variables(SOURCE)
cmake_print_variables(TARGET)

add_custom_command(OUTPUT ${TARGET}
    COMMAND y_embed ${SOURCE} ${TARGET}
    COMMENT "Embedding Diffusion Coefficients"
    VERBATIM
)

add_subdirectory(tests)
Y_Regression(chemical)

add_subdirectory(ionocell)

