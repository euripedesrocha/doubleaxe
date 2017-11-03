project('doubleaxe', 'cpp',
    default_options : ['cpp_std=c++14'],
    version : '0.0.1',
    license : 'MIT')

add_global_arguments('-Werror',
    '-Wall',
    '-Wextra',
    language : 'cpp')

catch = include_directories(['tools'])
mtest = files('tools/test_main.cpp')

subdir('gimli')
