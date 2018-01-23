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
        'main.cpp',
      ],
      'include_dirs': [
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
