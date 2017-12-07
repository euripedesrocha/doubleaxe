Gimli = include_directories('.')
TestSrc = files(['test/test_gimli.cpp'])
t_gimli = executable('t_gimli',
    MainTest, TestSrc, ReferenceSrc,
    include_directories:[catch, Gimli, ReferenceInc],
    install : false)

test('Gimli Permutation', t_gimli)
