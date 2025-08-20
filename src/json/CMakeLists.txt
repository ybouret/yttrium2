include_directories(. .. ../core)

Y_CreateLibrary(y-json
y/json
)

add_subdirectory(tests)
Y_Regression(json)
