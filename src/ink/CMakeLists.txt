include_directories(. .. ../core ../jive)

Y_CreateLibrary(y-ink
y/ink
y/ink/image
)

add_subdirectory(tests)
Y_Regression(ink)
