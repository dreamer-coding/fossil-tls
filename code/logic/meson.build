dir = include_directories('.')
cc = meson.get_compiler('c')
python3 = import('python').find_installation('python3')

# Check if the host system is Windows
if host_machine.system() == 'windows'
    winsock_dep = cc.find_library('ws2_32', required: true)
else
    winsock_dep = []
endif

fossil_tsl_lib = library('fossil-tsl',
    files('opentls.c'),
    install: true,
    dependencies: [cc.find_library('m', required: false), dependency('openssl'), winsock_dep, python3.dependency()],
    include_directories: dir)

fossil_tsl_dep = declare_dependency(
    link_with: [fossil_tsl_lib],
    include_directories: dir)
