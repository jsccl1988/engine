# Copyright (c) 2015 The Baidu Authors.
# All rights reserved.


{
  'targets': [
    {
      'target_name': 'test',
      'type': 'executable',
      'dependencies': [
      ],
      'sources': [
        'list.cpp',
        'list.h',
        'main.cpp',
        'sort.cpp',
        'sort.h',              
        'tree.cpp',
        'tree.h',        
        'utils.cpp',
        'utils.h',
      ],
      'include_dirs': [
      ],
      'conditions': [
        ['OS=="win"',{
          'cflags':[],
          'ldflags':[]
        },{
          'cflags':[
            '--std=c++11',
          ],
          'ldflags':[]
        }]
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': '1',
        },
      },
      'defines': [
        'STRICT',
        '_CRT_NON_CONFORMING_SWPRINTFS',
      ],
      'libraries': [
      ],
    },
  ],
}
