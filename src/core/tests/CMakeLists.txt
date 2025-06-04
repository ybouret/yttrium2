


Y_CreateTest(test-core
core
type
system
calculus
concurrent
memory
memory/object
memory/joint
hashing
xml
container
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

# type
Y_UTEST(type:ints)
Y_UTEST(type:moniker)

#calculus
Y_UTEST(calculus:integer_log2)
Y_UTEST(calculus:alignment)
Y_UTEST(calculus:base2)
Y_UTEST(calculus:gcd)

#concurrent
Y_UTEST(concurrent:nucleus)
Y_UTEST(concurrent:giant_lock)
Y_UTEST(concurrent:life_time)
Y_UTEST(concurrent:mutex)

#memory
Y_UTEST(memory:gc)
Y_UTEST(memory:system)
Y_UTEST(memory:dyadic)
Y_UTEST(memory:pooled)
Y_UTEST(memory:quanta)
Y_UTEST(memory:workspace)
Y_UTEST(memory:object:chunk)
Y_UTEST(memory:object:pages)
Y_UTEST(memory:object:book)
Y_UTEST(memory:object:arena)
Y_UTEST(memory:object:blocks)
Y_UTEST(memory:object:factory)
Y_UTEST(memory:object:guild)
Y_UTEST(memory:joint:segment)
Y_UTEST(memory:joint:segments)


#hashing
Y_UTEST(hashing:mix64)
Y_UTEST(hashing:hash32)

#xml
Y_UTEST(xml:attribute)

#container
Y_UTEST(container:algo)

