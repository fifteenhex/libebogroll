project('libebogroll', 'c',
        license : 'GPLv2',
        default_options: ['c_std=c99'])

cc = meson.get_compiler('c')
cflags = cc.get_supported_arguments([
    '-Wall',
    '-Werror=incompatible-pointer-types',
    '-Werror=implicit-function-declaration',
    '-Werror=format-security'
])

inc = include_directories('include')

subdir('include')
subdir('src')

libebogroll_dep = declare_dependency(
    include_directories : inc,
    link_with : libebogroll)

pkg_mod = import('pkgconfig')
pkg_mod.generate(
    libraries : libebogroll,
    version : '0',
    name : 'libebogroll',
    filebase : 'libebogroll',
    description : 'Library for cheapy epaper displays')
