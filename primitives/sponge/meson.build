Sponge= include_directories('.')
TestSrc  = files('test/test_sponge.cpp')
t_sponge = executable('t_sponge',
    MainTest, TestSrc, GimliSrc,
    include_directories:[catch, Gimli],
    install : false)
