import os

VARIANT_BASE_DIR = 'build'

env = Environment(
    CFLAGS='-std=c11'
)

dirs = [
    'default', 'sdl2'
]

for subdir in dirs:
    variant_path = os.path.join(VARIANT_BASE_DIR, subdir)
    SConscript(
        dirs=subdir,
        exports=['env'],
        variant_dir=variant_path,
        duplicate=0
    )
