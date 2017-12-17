echo =======================gen==========================

set GYP_DEFINES=component=shared_library
set /p GYP_MSVS_VERSION=<config.ini
set GYP_GENERATORS=msvs-ninja,ninja
set GYP_GENERATOR_FLAGS="output_dir=../out"

set workspace=%~dp0
set depot_tools_path=%workspace%src\tools\depot_tools
set python_path=%depot_tools_path%\python276_bin

set PATH=%depot_tools_path%;%python_path%;%PATH%

set source=src
set source_depth=src/build
set target_gyp=src/build/all.gyp
python src\tools\gyp\gyp_main.py --depth=%source_depth% --toplevel-dir=%source% --no-duplicate-basename-check %target_gyp% -I src\build\common.gypi
