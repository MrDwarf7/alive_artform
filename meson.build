# If meson not building/pulling deps, try:
# meson setup build --wipe --clearcache \
#        --wrap-mode=forcefallback
#
## and then
#
# meson compile -C ./build/

project(
  'alive_artform',
  'cpp',
  version: '0.1.0',
  default_options: [
    'cpp_std=c++23',
    'warning_level=2',
    'force-fallback-for=sdl2,sdl2_ttf', ## We FORCE meson download of deps to pin versions
    'wrap_mode=forcefallback', ## Force meson to use fallback (downloaded) deps instead of system ones, if they exist. This is to ensure we get the pinned versions.
  ],
)

# ---------------------------------------------------------------------------
# Dependencies
# ---------------------------------------------------------------------------
sdl2_dep = dependency('sdl2', static: true)
sdl2_ttf_dep = dependency('sdl2_ttf', static: true)

# ---------------------------------------------------------------------------
# Embedded assets
##
# Converts each file under assets/ into a C header with a byte array.
# To add a new asset, just append to the list below.
# In code:  #include "arial_ttf.h"  →  arial_ttf[] and arial_ttf_len
# ---------------------------------------------------------------------------
embed_resource = find_program('scripts/embed_resource.py')

asset_files = {
  'arial.ttf': 'arial_ttf',
}

embedded_assets = []
foreach file, var_name : asset_files
  embedded_assets += custom_target(
    'embed_' + var_name,
    input: 'assets' / file,
    output: var_name + '.h',
    command: [embed_resource, '@INPUT@', '@OUTPUT@', var_name],
  )
endforeach

# ---------------------------------------------------------------------------
# Sources  (listed in src/meson.build)
# ---------------------------------------------------------------------------
subdir('src')

# ---------------------------------------------------------------------------
# Executable
# ---------------------------------------------------------------------------
executable(
  'alive_artform',
  sources,
  embedded_assets,
  dependencies: [sdl2_dep, sdl2_ttf_dep],
  # include_directories: ['src'],  ## Turn back on if we are 'okay' with src-relative includes (Rather be explicit here though, so is off/commented)
)
