


Y_CreateTest(test-core
core
type
static
system
calculus
concurrent
memory
memory/small
memory/joint
hashing
xml
container
stream
stream/io
)


Y_LinkLibraries(test-core)

enable_testing()

Y_Message("Preparing ${Y_Test}")

Y_UTEST(exception)
Y_UTEST(hexadecimal)
Y_UTEST(decimal)
Y_UTEST(singleton)

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

#calculus
Y_UTEST(calculus:integer_log2)
Y_UTEST(calculus:alignment)
Y_UTEST(calculus:base2)
Y_UTEST(calculus:gcd)
Y_UTEST(calculus:bits_for)

#concurrent
Y_UTEST(concurrent:nucleus)
Y_UTEST(concurrent:giant_lock)
Y_UTEST(concurrent:life_time)
Y_UTEST(concurrent:mutex)
Y_UTEST(concurrent:condition)
Y_UTEST(concurrent:thread)
Y_UTEST(concurrent:dead_pool)
Y_UTEST(concurrent:inferno)

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


#hashing
Y_UTEST(hashing:mix64)
Y_UTEST(hashing:hash32)

#xml
Y_UTEST(xml:attribute)

#container
Y_UTEST(container:algo)
Y_UTEST(container:iterator)

#stream
Y_UTEST(stream:io:codec64)
Y_UTEST(stream:io:char)
Y_UTEST(stream:output:queue)

