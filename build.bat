echo =======================build==========================

set workspace=%~dp0
set depot_tools_path=%workspace%\src\tools\depot_tools
set python_path=%depot_tools_path%\python276_bin

set PATH=%depot_tools_path%;%python_path%;%PATH%

ninja -C src\build/out/Debug all