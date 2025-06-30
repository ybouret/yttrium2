#include "y/system/compiler.hpp"
#include "y/system/platform.hpp"
#include "y/core/variadic.hpp"
#include "y/core/setup.hpp"
#include "y/exception.hpp"
#include "y/utest/driver.hpp"
#include <cstring>
#include <iostream>

Y_UTEST_DECL(128)
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
    Y_UTEST(concurrent_inventory);


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
    Y_UTEST(memory_school_of);
    Y_UTEST(memory_static_buffer);
    Y_UTEST(memory_buffer_out_of);



    Y_UTEST(hashing_mix64);
    Y_UTEST(hashing_hash32);

    Y_UTEST(xml_attribute);

    Y_UTEST(container_algo);
    Y_UTEST(container_iterator);
    Y_UTEST(container_cxx_array);

    Y_UTEST(stream_io_char);
    Y_UTEST(stream_queue);
    Y_UTEST(stream_input_file);
    Y_UTEST(stream_output_file);
    Y_UTEST(stream_gets);


    Y_UTEST(sorting_heap);
    Y_UTEST(sorting_index);

    Y_UTEST(sequence_list);
    Y_UTEST(sequence_vector);

    Y_UTEST(ordered_pqueue);
    Y_UTEST(ordered_static_pqueue);

    Y_UTEST(ptr_auto);
    Y_UTEST(ptr_arc);

    Y_UTEST(info_bwt);
    Y_UTEST(info_stream);
    Y_UTEST(info_arc4);
    Y_UTEST(info_rle);
    Y_UTEST(info_bwt_rle);
    Y_UTEST(info_bwt_mtf);
    Y_UTEST(info_entropy);

    Y_UTEST(utf8_api);

    Y_UTEST(protean_direct_cache);
    Y_UTEST(protean_bare_light_list);
    Y_UTEST(protean_bare_heavy_list);
    Y_UTEST(protean_solo_light_list);
    Y_UTEST(protean_solo_heavy_list);
    Y_UTEST(protean_coop_light_list);
    Y_UTEST(protean_coop_heavy_list);

    Y_UTEST(string_stride);
    Y_UTEST(string);
    
    Y_UTEST(apex_blocks);
    Y_UTEST(apex_model);
    Y_UTEST(apex_n);

    Y_UTEST(random_bits);
    Y_UTEST(random_gaussian);
    
    Y_UTEST(mkl_numeric);
}
Y_UTEST_EXEC()

