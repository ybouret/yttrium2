#include "y/system/compiler.hpp"
#include "y/system/platform.hpp"
#include "y/core/variadic.hpp"
#include "y/core/setup.hpp"
#include "y/exception.hpp"
#include "y/utest/driver.hpp"
#include <cstring>
#include <iostream>

Y_UTEST_DECL(256)
{
    Y_UTEST(exception);

    Y_UTEST(singleton);
    Y_UTEST(static_init);
    Y_UTEST(functor);

    Y_UTEST(format_hexadecimal);
    Y_UTEST(format_decimal);
    Y_UTEST(format_human_readable);

    Y_UTEST(core_variadic);
    Y_UTEST(core_linked);

    Y_UTEST(type_ints);
    Y_UTEST(type_fourcc);

    Y_UTEST(static_moniker);
    Y_UTEST(static_solitary);
    Y_UTEST(static_multiple);
    Y_UTEST(static_replica);


    Y_UTEST(system_error);
    Y_UTEST(system_at_exit);
    Y_UTEST(system_rand);
    Y_UTEST(system_wall_time);

    Y_UTEST(calculus_integer_log2);
    Y_UTEST(calculus_alignment);
    Y_UTEST(calculus_base2);
    Y_UTEST(calculus_gcd);
    Y_UTEST(calculus_bits_for);
    Y_UTEST(calculus_bytes_for);
    Y_UTEST(calculus_isqrt);
    Y_UTEST(calculus_iabs);
    Y_UTEST(calculus_bits_in);





    Y_UTEST(concurrent_nucleus);
    Y_UTEST(concurrent_giant_lock);
    Y_UTEST(concurrent_life_time);
    Y_UTEST(concurrent_mutex);
    Y_UTEST(concurrent_condition);
    Y_UTEST(concurrent_thread);
    Y_UTEST(concurrent_inventory);
    Y_UTEST(concurrent_split1d);
    Y_UTEST(concurrent_split2d);


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
    Y_UTEST(hashing_digest);
    Y_UTEST(hashing_perfect);
    Y_UTEST(hashing_functions);
    Y_UTEST(hashing_hmac);

    Y_UTEST(xml_attribute);

    Y_UTEST(container_algo);
    Y_UTEST(container_iterator);
    Y_UTEST(container_cxx_array);
    Y_UTEST(container_cxx_series);
    Y_UTEST(container_matrix);
    Y_UTEST(container_suffix_tree);
    Y_UTEST(container_htable);
    Y_UTEST(container_suffix_set);
    Y_UTEST(container_suffix_map);
    Y_UTEST(container_hash_set);
    Y_UTEST(container_hash_map);
    Y_UTEST(container_associative);
    

    Y_UTEST(stream_io_char);
    Y_UTEST(stream_queue);
    Y_UTEST(stream_input_file);
    Y_UTEST(stream_output_file);
    Y_UTEST(stream_gets);
    Y_UTEST(stream_proc);
    Y_UTEST(stream_xmlog);
    Y_UTEST(stream_gzip_read);
    Y_UTEST(stream_gzip_write);
    Y_UTEST(stream_misc);


    Y_UTEST(sorting_heap);
    Y_UTEST(sorting_index);

    Y_UTEST(sequence_list);
    Y_UTEST(sequence_vector);

    Y_UTEST(ordered_pqueue);
    Y_UTEST(ordered_static_pqueue);
    Y_UTEST(ordered_data_book);

    Y_UTEST(ptr_auto);
    Y_UTEST(ptr_arc);
    Y_UTEST(ptr_keyed);

    Y_UTEST(info_bwt);
    Y_UTEST(info_stream);
    Y_UTEST(info_arc4);
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
    Y_UTEST(string_env);
    Y_UTEST(string_percent);
    
    Y_UTEST(apex_parcel);
    Y_UTEST(apex_parcels);
    Y_UTEST(apex_device);
    Y_UTEST(apex_perf);
    Y_UTEST(apex_n);
    Y_UTEST(apex_z);
    Y_UTEST(apex_q);
    Y_UTEST(apex_io);
    Y_UTEST(apex_rsa);
    Y_UTEST(apex_ortho_vector);
    Y_UTEST(apex_ortho_keep);
    Y_UTEST(apex_ortho_family);

    Y_UTEST(coven_indx);
    Y_UTEST(coven_tribes);
    Y_UTEST(coven_space);
    Y_UTEST(coven_max);


    Y_UTEST(random_bits);
    Y_UTEST(random_gaussian);
    Y_UTEST(random_in2d);
    Y_UTEST(random_in3d);
    Y_UTEST(random_fill);
    Y_UTEST(random_shuffle);
    
    Y_UTEST(mkl_numeric);
    Y_UTEST(mkl_api);
    Y_UTEST(mkl_adaptor);
    Y_UTEST(mkl_v2d);
    Y_UTEST(mkl_triplet);
    Y_UTEST(mkl_xreal);
    Y_UTEST(mkl_almost_equal);
    Y_UTEST(mkl_mod2);

    Y_UTEST(cameo_add);
    Y_UTEST(cameo_mul);

    Y_UTEST(dft_fmt);
    Y_UTEST(dft_core);
    Y_UTEST(dft_mul);

    Y_UTEST(ascii_convert);

    Y_UTEST(vfs_cwd);
    Y_UTEST(vfs_dname);
    Y_UTEST(vfs_entry);
    Y_UTEST(vfs_mkdir);
    Y_UTEST(vfs_names);
    Y_UTEST(vfs_rm);
    Y_UTEST(vfs_scan);
    Y_UTEST(vfs_subdirs);


    Y_UTEST(counting_comb);
    Y_UTEST(counting_combination);
    Y_UTEST(counting_nested);
    Y_UTEST(counting_part);
    Y_UTEST(counting_partition);
    Y_UTEST(counting_perm);
    Y_UTEST(counting_permutation);

    Y_UTEST(graphviz);

    Y_UTEST(field_layout);
}
Y_UTEST_EXEC()

