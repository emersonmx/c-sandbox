import os

BUILD_ROOT = 'build'
DEFAULT_CFLAGS = [
    '-std=c11',
]
DEFAULT_CXXFLAGS = [
    '-std=c++17',
]
DEBUG_CFLAGS = [
    '-g', '-Wall', '-Wextra', '-Wpedantic',
    '-Wformat=2', '-Wno-unused-parameter', '-Wshadow',
    '-Wwrite-strings', '-Wstrict-prototypes', '-Wold-style-definition',
    '-Wredundant-decls', '-Wnested-externs', '-Wmissing-include-dirs',
    '-DDEBUG',
]
DEBUG_CXXFLAGS = [
    '-g', '-Wall', '-Wextra', '-Wpedantic',
    '-Wformat=2', '-Wno-unused-parameter', '-Wshadow',
    '-Wwrite-strings', '-Wredundant-decls', '-Wmissing-include-dirs',
    '-DDEBUG',
]
RELEASE_CFLAGS = [
    '-O3', '-DNDEBUG',
]

env = Environment(
    CFLAGS=DEFAULT_CFLAGS,
    CXXFLAGS=DEFAULT_CXXFLAGS,
    CPPPATH=['#']
)

build_type = ARGUMENTS.get('build', 'debug')
if build_type == 'debug':
    env.Append(
        CFLAGS=DEBUG_CFLAGS,
        CXXFLAGS=DEBUG_CXXFLAGS,
    )
elif build_type == 'release':
    env.Append(CFLAGS=RELEASE_CFLAGS)

dirs = [
    'default', 'sdl2', 'pong'
]

for subdir in dirs:
    variant_path = os.path.join(BUILD_ROOT, subdir)
    SConscript(
        dirs=subdir,
        exports=['env', 'variant_path'],
        variant_dir=variant_path,
        duplicate=0
    )
