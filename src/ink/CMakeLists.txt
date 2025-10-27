include_directories(. .. ../core)

Y_CreateLibrary(y-ink
y/ink
y/ink/pixel
)

add_subdirectory(tests)
Y_Regression(ink)
