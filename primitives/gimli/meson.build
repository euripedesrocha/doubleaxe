Gimli = include_directories('.')
GimliSrc = files(['gimli.cpp'])
TestSrc = files(['test/test_gimli.cpp'])
t_gimli = executable('t_gimli',
    MainTest, TestSrc, GimliSrc,
    include_directories:[catch, Gimli],
    install : false)

test('Gimli Permutation', t_gimli)
