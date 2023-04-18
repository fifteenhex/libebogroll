libebogroll_sources = [
    'ebogroll.c',
    'gdew042c37.c'
]

libebogroll = shared_library('ebogroll',
                           libebogroll_sources,
                           include_directories: inc,
                           install : true,
                           dependencies : [ libusrio_dep, libdgpc_dep])
