DoubleAxe = include_directories('.')
TestSrc = files(['test/test_doubleaxe.cpp'])
t_doubleaxe = executable('t_doubleaxe',
    MainTest, TestSrc,
    include_directories:[catch, DoubleAxe, Gimli, Sponge],
    install : false)

test('DoubleAxe Stream Cypher', t_doubleaxe)
