


Y_CreateTest(test-core
core
format
ascii
type
static
system
calculus
concurrent
memory
memory/small
memory/joint
memory/io
hashing
xml
container
stream
stream/io
sorting
ptr
information
utf8
protean
string
apex apex/ortho
random
mkl
cameo
dft
vfs
counting
)


Y_LinkLibraries(test-core)

enable_testing()

Y_Message("Preparing ${Y_Test}")

Y_UTEST(exception)

Y_UTEST(singleton)
Y_UTEST(static_init)
Y_UTEST(functor)

#format
Y_UTEST(format:hexadecimal)
Y_UTEST(format:decimal)
Y_UTEST(format:human_readable)

# core
Y_UTEST(core:variadic)
Y_UTEST(core:linked)

# system
Y_UTEST(system:error 1 2)
Y_UTEST(system:at_exit)
Y_UTEST(system:rand)
Y_UTEST(system:wall_time)

# type
Y_UTEST(type:ints)

# static
Y_UTEST(static:moniker)
Y_UTEST(static:solitary)
Y_UTEST(static:multiple)
Y_UTEST(static:replica)

#calculus
Y_UTEST(calculus:integer_log2)
Y_UTEST(calculus:alignment)
Y_UTEST(calculus:base2)
Y_UTEST(calculus:gcd)
Y_UTEST(calculus:bits_for)
Y_UTEST(calculus:isqrt)
Y_UTEST(calculus:iabs)

#concurrent
Y_UTEST(concurrent:nucleus)
Y_UTEST(concurrent:giant_lock)
Y_UTEST(concurrent:life_time)
Y_UTEST(concurrent:mutex)
Y_UTEST(concurrent:condition)
Y_UTEST(concurrent:thread)
Y_UTEST(concurrent:inventory)

#memory
Y_UTEST(memory:gc)
Y_UTEST(memory:system)
Y_UTEST(memory:dyadic)
Y_UTEST(memory:pooled)
Y_UTEST(memory:quanta)
Y_UTEST(memory:small:chunk)
Y_UTEST(memory:small:pages)
Y_UTEST(memory:small:ledger)
Y_UTEST(memory:small:arena)
Y_UTEST(memory:small:blocks)
Y_UTEST(memory:small:guild)
Y_UTEST(memory:joint:segment)
Y_UTEST(memory:joint:segments)
Y_UTEST(memory:object:factory)
Y_UTEST(memory:object)
Y_UTEST(memory:operative)
Y_UTEST(memory:io:zombies)
Y_UTEST(memory:school_of)
Y_UTEST(memory:static_buffer)
Y_UTEST(memory:buffer_out_of)



#hashing
Y_UTEST(hashing:mix64)
Y_UTEST(hashing:hash32)
Y_UTEST(hashing:digest)
Y_UTEST(hashing:perfect)

#xml
Y_UTEST(xml:attribute)

#container
Y_UTEST(container:algo)
Y_UTEST(container:iterator)
Y_UTEST(container:cxx:array)
Y_UTEST(container:matrix)
Y_UTEST(container:suffix:tree)
Y_UTEST(container:htable)
Y_UTEST(container:suffix:set)
Y_UTEST(container:suffix:map)

#stream
Y_UTEST(stream:io:char)
Y_UTEST(stream:queue)
Y_UTEST(stream:input:file)
Y_UTEST(stream:output:file)
Y_UTEST(stream:gets)
Y_UTEST(stream:proc)
Y_UTEST(stream:gzip:read)

#sort
Y_UTEST(sorting:heap)
Y_UTEST(sorting:index)

#sequence
Y_UTEST(sequence:list)
Y_UTEST(sequence:vector)

#ordered
Y_UTEST(ordered:pqueue)
Y_UTEST(ordered:static_pqueue)

#ptr
Y_UTEST(ptr:auto)
Y_UTEST(ptr:arc)

#information
Y_UTEST(info:bwt)
Y_UTEST(info:stream)
Y_UTEST(info:arc4)
Y_UTEST(info:bwt_mtf)
Y_UTEST(info:entropy)

#utf8
Y_UTEST(utf8:api)

#protean
Y_UTEST(protean:direct_cache)
Y_UTEST(protean:bare:light:list)
Y_UTEST(protean:bare:heavy:list)
Y_UTEST(protean:solo:light:list)
Y_UTEST(protean:solo:heavy:list)
Y_UTEST(protean:coop:light:list)
Y_UTEST(protean:coop:heavy:list)


#string
Y_UTEST(string:stride)
Y_UTEST(string)
Y_UTEST(string:env)

#apex
Y_UTEST(apex:parcel)
Y_UTEST(apex:parcels)
Y_UTEST(apex:device)
Y_UTEST(apex:n)
Y_UTEST(apex:z)
Y_UTEST(apex:q)
Y_UTEST(apex:io)
Y_UTEST(apex:rsa)
Y_UTEST(apex:ortho:vector)
Y_UTEST(apex:ortho:keep)
Y_UTEST(apex:ortho:family)

#random
Y_UTEST(random:bits)
Y_UTEST(random:gaussian)
Y_UTEST(random:in2d)
Y_UTEST(random:in3d)
Y_UTEST(random:fill)
Y_UTEST(random:shuffle)

#mkl
Y_UTEST(mkl:numeric)
Y_UTEST(mkl:api)
Y_UTEST(mkl:adaptor)
Y_UTEST(mkl:triplet)
Y_UTEST(mkl:v2d)
Y_UTEST(mkl:almost_equal)
Y_UTEST(mkl:xreal)
Y_UTEST(mkl:mod2)

#cameo
Y_UTEST(cameo:add)
Y_UTEST(cameo:mul)

#dft
Y_UTEST(dft:core)
Y_UTEST(dft:fmt)

#ascii
Y_UTEST(ascii_convert)

#vfs
Y_UTEST(vfs:cwd)
Y_UTEST(vfs:dname)
Y_UTEST(vfs:entry)
Y_UTEST(vfs:mkdir)
Y_UTEST(vfs:names)
Y_UTEST(vfs:rm)
Y_UTEST(vfs:scan)
Y_UTEST(vfs:subdirs)

#counting
Y_UTEST(counting:comb)
Y_UTEST(counting:combination)
Y_UTEST(counting:nested)
Y_UTEST(counting:part)
Y_UTEST(counting:partition)
Y_UTEST(counting:perm)
Y_UTEST(counting:permutation)

#graphviz
Y_UTEST(graphviz)

