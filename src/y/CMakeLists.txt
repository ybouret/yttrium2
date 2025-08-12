
set(third_party_list "")

set(test_third_party OFF)

set( TestThirdPartyFlag "$ENV{TestThirdParty}" )
if( "1" STREQUAL "${TestThirdPartyFlag}" )
    set(test_third_party ON)
endif()

#cmake_print_variables(test_third_party)


# macro to add to list
macro(Y_ThirdParty theTarget)
    set(local_third_party ${third_party_list})
    list(APPEND local_third_party "${theTarget}")
    set(third_party_list ${local_third_party} PARENT_SCOPE)
endmacro()

add_subdirectory(zlib)
add_subdirectory(bzip2)
add_subdirectory(lua)
add_subdirectory(jbig)
add_subdirectory(jpeg)

#cmake_print_variables(third_party_list)

add_custom_target(third_party
DEPENDS ${third_party_list})
