include_directories(. .. ../core)

Y_CreateLibrary(y-ink
y/ink
)

add_subdirectory(tests)
Y_Regression(ink)
