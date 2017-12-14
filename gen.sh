echo =======================gen==========================

export GYP_DEFINES=component=shared_library
export GYP_GENERATORS=ninja
export GYP_GENERATOR_FLAGS="output_dir=../out"

workspace=$(pwd)
depot_tools_path=${workspace}/src/tools/depot_tools
python_path=${depot_tools_path}/python276_bin

export PATH=${PATH}:${depot_tools_path}:${python_path}

source=src
source_depth=src/build
target_gyp=src/build/all.gyp
python src/tools/gyp/gyp_main.py --depth=${source_depth} --toplevel-dir=${source} --no-duplicate-basename-check ${target_gyp} -I src/build/common.gypi
