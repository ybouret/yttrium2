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
    Y_UTEST(static_init);

    Y_UTEST(core_variadic);
    Y_UTEST(core_linked);

    Y_UTEST(type_ints);

    Y_UTEST(static_moniker);
    Y_UTEST(static_solitary);
    Y_UTEST(static_multiple);

    Y_UTEST(system_error);
    Y_UTEST(system_at_exit);
    Y_UTEST(system_rand);
    Y_UTEST(system_wall_time);

    Y_UTEST(calculus_integer_log2);
    Y_UTEST(calculus_alignment);
    Y_UTEST(calculus_base2);
    Y_UTEST(calculus_gcd);
    Y_UTEST(calculus_bits_for);



    Y_UTEST(concurrent_nucleus);
    Y_UTEST(concurrent_giant_lock);
    Y_UTEST(concurrent_life_time);
    Y_UTEST(concurrent_mutex);
    Y_UTEST(concurrent_condition);
    Y_UTEST(concurrent_thread);
    Y_UTEST(concurrent_dead_pool);
    Y_UTEST(concurrent_inferno);


    Y_UTEST(memory_gc);
    Y_UTEST(memory_system);
    Y_UTEST(memory_dyadic);
    Y_UTEST(memory_pooled);
    Y_UTEST(memory_quanta);
    Y_UTEST(memory_small_chunk);
    Y_UTEST(memory_small_pages);
    Y_UTEST(memory_small_ledger);
    Y_UTEST(memory_small_arena);
    Y_UTEST(memory_small_blocks);
    Y_UTEST(memory_small_guild);
    Y_UTEST(memory_joint_segment);
    Y_UTEST(memory_joint_segments);
    Y_UTEST(memory_object_factory);
    Y_UTEST(memory_object);
    Y_UTEST(memory_operative);
    Y_UTEST(memory_io_zombies);


    Y_UTEST(hashing_mix64);
    Y_UTEST(hashing_hash32);

    Y_UTEST(xml_attribute);

    Y_UTEST(container_algo);
    Y_UTEST(container_iterator);

    Y_UTEST(stream_io_codec64);
    Y_UTEST(stream_io_char);
    Y_UTEST(stream_queue);
}
Y_UTEST_EXEC()

