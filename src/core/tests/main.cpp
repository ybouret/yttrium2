#include "y/system/compiler.hpp"
#include "y/system/platform.hpp"
#include "y/core/variadic.hpp"
#include "y/core/setup.hpp"
#include "y/exception.hpp"
#include "y/utest/driver.hpp"
#include <cstring>
#include <iostream>

Y_UTEST_DECL(64)
{
    Y_UTEST(exception);
    Y_UTEST(hexadecimal);
    Y_UTEST(decimal);
    Y_UTEST(singleton);

    Y_UTEST(core_variadic);
    Y_UTEST(core_linked);

    Y_UTEST(type_ints);

    Y_UTEST(system_error);
    Y_UTEST(system_at_exit);
    Y_UTEST(system_rand);

    Y_UTEST(calculus_integer_log2);
    Y_UTEST(calculus_alignment);
    Y_UTEST(calculus_base2);
    Y_UTEST(calculus_gcd);


    Y_UTEST(concurrent_nucleus);
    Y_UTEST(concurrent_giant_lock);
    Y_UTEST(concurrent_life_time);

    Y_UTEST(memory_system);
    Y_UTEST(memory_dyadic);
    Y_UTEST(memory_pooled);
    Y_UTEST(memory_workspace);
    Y_UTEST(memory_object_chunk);
    Y_UTEST(memory_object_pages);
    Y_UTEST(memory_object_book);
    Y_UTEST(memory_object_arena);
    Y_UTEST(memory_object_blocks);
    Y_UTEST(memory_object_factory);
    Y_UTEST(memory_object_guild);
    Y_UTEST(memory_dyads);
    Y_UTEST(memory_joint_segment);
    Y_UTEST(memory_joint_segments);

    Y_UTEST(hashing_mix64);
    Y_UTEST(hashing_hash32);
    
    Y_UTEST(xml_attribute);

}
Y_UTEST_EXEC()

