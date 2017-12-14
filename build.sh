echo =======================build==========================

workspace=$(pwd)
depot_tools_path=${workspace}/src/tools/depot_tools
python_path=${depot_tools_path}/python276_bin

export PATH=${PATH}:${depot_tools_path}:${python_path}
${depot_tools_path}/ninja -C out/Debug all
