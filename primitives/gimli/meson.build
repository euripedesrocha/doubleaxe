Gimli = include_directories('.')
GimliSrc = files(['gimli.cpp'])
TestSrc = files(['test/test_gimli.cpp'])
t_gimli = executable('t_gimli',
    MainTest, TestSrc, GimliSrc, ReferenceSrc,
    include_directories:[catch, Gimli, ReferenceInc],
    install : false)

test('Gimli Permutation', t_gimli)
