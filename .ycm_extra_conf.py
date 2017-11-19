# Partially stolen from https://bitbucket.org/mblum/libgp/src/2537ea7329ef/.ycm_extra_conf.py
import os
import ycm_core

def DirectoryOfThisScript():
    return os.path.dirname(os.path.abspath(__file__))

compilation_database_folder = DirectoryOfThisScript() + '/build'
database = ycm_core.CompilationDatabase(compilation_database_folder)
def MakeRelativePathsInFlagsAbsolute( flags, working_directory ):
    if not working_directory:
        return list(flags)
    new_flags = []
    make_next_absolute = False
    path_flags = ['-isystem', '-I', '-iquote', '--sysroot=']
    for flag in flags:
        new_flag = flag

        if make_next_absolute:
            make_next_absolute = False
            if not flag.startswith('/'):
                new_flag = os.path.join(working_directory, flag)

        for path_flag in path_flags:
            if flag == path_flag:
                make_next_absolute = True
                break

            if flag.startswith(path_flag):
                path = flag[len(path_flag):]
                new_flag = path_flag + os.path.join(working_directory, path)
                break

        if new_flag:
            new_flags.append(new_flag)
    return new_flags

def FlagsForFile(filename):
    # Bear in mind that compilation_info.compiler_flags_ does NOT return a
    # python list, but a "list-like" StringVec object
    compilation_info = database.GetCompilationInfoForFile(filename)
    final_flags = MakeRelativePathsInFlagsAbsolute(
        compilation_info.compiler_flags_,
        compilation_info.compiler_working_dir_)

    return {
        'flags': final_flags,
        'do_cache': True
    }
