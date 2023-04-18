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

# Find dgpc. This should never be an installed library
libdgpc_proj = subproject('libdgpc')
libdgpc_dep = libdgpc_proj.get_variable('libdgpc_dep')
log_macros_tmpl = libdgpc_proj.get_variable('log_macros_tmpl')

# Find libusrio
libusrio_dep = dependency('libusrio', required : false)
if not libusrio_dep.found()
    libusrio_proj = subproject('libusrio')
    libusrio_dep = libusrio_proj.get_variable('libusrio_dep')
endif

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
