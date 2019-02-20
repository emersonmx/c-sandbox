import os

BUILD_ROOT = 'build'
DEFAULT_CFLAGS = [
    '-std=c11',
]
DEBUG_CFLAGS = [
    '-g', '-Wall', '-Wextra', '-Wpedantic',
    '-Wformat=2', '-Wno-unused-parameter', '-Wshadow',
    '-Wwrite-strings', '-Wstrict-prototypes', '-Wold-style-definition',
    '-Wredundant-decls', '-Wnested-externs', '-Wmissing-include-dirs',
]

env = Environment(
    CFLAGS=DEFAULT_CFLAGS
)

env.Append(
    CFLAGS=DEBUG_CFLAGS,
)

dirs = [
    'default', 'sdl2', 'games'
]

for subdir in dirs:
    variant_path = os.path.join(BUILD_ROOT, subdir)
    SConscript(
        dirs=subdir,
        exports=['env', 'variant_path'],
        variant_dir=variant_path,
        duplicate=0
    )
