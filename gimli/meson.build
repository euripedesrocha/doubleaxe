gimli = include_directories('.')
gimli_src = files(['gimli.cpp'])
test_src = files(['test/test_gimli.cpp'])
t_gimli = executable('t_gimli',
    mtest, test_src, gimli_src,
    include_directories:[catch, gimli],
    install : false)

test('Inverse', t_gimli)
