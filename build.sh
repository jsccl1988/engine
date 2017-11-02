echo =======================build==========================

workspace=$pwd
depot_tools_path=${workspace}/src/tools/depot_tools
python_path=${depot_tools_path}/python276_bin

export PATH=${depot_tools_path}:${python_path}:${PATH}

ninja -C out/Debug all