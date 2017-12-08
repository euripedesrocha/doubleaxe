project('doubleaxe', 'cpp', 'c',
    default_options : ['cpp_std=c++1z', 'c_std=c11'],
    version : '0.0.1',
    license : 'MIT')

add_global_arguments('-Werror',
    '-Wall',
    '-Wextra',
    language : 'cpp')

catch = include_directories(['tools/Catch'])
MainTest = files('tools/Catch/test_main.cpp')
ReferenceInc = include_directories('tools/Reference')
ReferenceSrc = files('tools/Reference/gimli.c')


subdir('primitives/gimli')
subdir('primitives/sponge')
subdir('doubleaxe')
