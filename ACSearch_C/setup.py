from distutils.core import setup, Extension
from distutils.command.build_ext import build_ext
from distutils.sysconfig import customize_compiler

class cpp_build_ext(build_ext):
    def build_extensions(self):
        customize_compiler(self.compiler)
        try:
            self.compiler.compiler_so.remove("-Wstrict-prototypes")
        except (AttributeError, ValueError):
            pass
        build_ext.build_extensions(self)

ext_module = Extension('ACSearch',
            sources = [
                'py_ACSearch.cpp',
                'ACSearch.cpp',
                'container.cpp'
            ],
            include_dirs=['./'],
            language='c++')

setup (name = 'ACSearch',
        version = '1.0',
        ext_modules = [ext_module],
        cmdclass={'build_ext': cpp_build_ext},
    )