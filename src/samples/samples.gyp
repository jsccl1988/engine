# Copyright (c) 2017 The Smart Authors.
# All rights reserved.

{
  'targets': [
    {
      'target_name': 'device_caps',
      'type': 'executable',
      'dependencies': [
        '../engine/engine.gyp:vr_engine',
      ],
      'include_dirs': [
        './',
        '../',
        '../../',
      ],
      'sources': [
        'device_caps/sample.cpp',
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': '1',  # /SUBSYSTEM:CONSOLE
        },
      },
    }, 
    {
      'target_name': 'fonts',
      'type': 'executable',
      'dependencies': [
        '../engine/engine.gyp:*',
      ],
      'include_dirs': [
        './',
        '../',
        '../../',
      ],
      'sources': [
        'fonts/sample.cpp',
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': '1',  # /SUBSYSTEM:CONSOLE
        },
      },
    }, 
    {
      'target_name': 'inventory',
      'type': 'executable',
      'dependencies': [
        '../engine/engine.gyp:*',
      ],
      'include_dirs': [
        './',
        '../',
        '../../',
      ],
      'sources': [
        'inventory/sample.cpp',
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': '1',  # /SUBSYSTEM:CONSOLE
        },
      },
    }, 
    {
      'target_name': 'models',
      'type': 'executable',
      'dependencies': [
        '../engine/engine.gyp:*',
      ],
      'include_dirs': [
        './',
        '../',
        '../../',
      ],
      'sources': [
        'models/sample.cpp',
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': '1',  # /SUBSYSTEM:CONSOLE
        },
      },
    }, 
    {
      'target_name': 'movable_sprite',
      'type': 'executable',
      'dependencies': [
        '../engine/engine.gyp:*',
      ],
      'include_dirs': [
        './',
        '../',
        '../../',
      ],
      'sources': [
        'movable_sprite/sample.cpp',
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': '1',  # /SUBSYSTEM:CONSOLE
        },
      },
    }, 
    {
      'target_name': 'screen_modes',
      'type': 'executable',
      'dependencies': [
        '../engine/engine.gyp:*',
      ],
      'include_dirs': [
        './',
        '../',
        '../../',
      ],
      'sources': [
        'screen_modes/sample.cpp',
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': '1',  # /SUBSYSTEM:CONSOLE
        },
      },
    }, 
    {
      'target_name': 'shaders',
      'type': 'executable',
      'dependencies': [
        '../engine/engine.gyp:*',
      ],
      'include_dirs': [
        './',
        '../',
        '../../',
      ],
      'sources': [
        'shaders/sample.cpp',
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': '1',  # /SUBSYSTEM:CONSOLE
        },
      },
    }, 
    {
      'target_name': 'sobel',
      'type': 'executable',
      'dependencies': [
        '../engine/engine.gyp:*',
      ],
      'include_dirs': [
        './',
        '../',
        '../../',
      ],
      'sources': [
        'sobel/sample.cpp',
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': '1',  # /SUBSYSTEM:CONSOLE
        },
      },
    }, 
    {
      'target_name': 'splatting',
      'type': 'executable',
      'dependencies': [
        '../engine/engine.gyp:*',
      ],
      'include_dirs': [
        './',
        '../',
        '../../',
      ],
      'sources': [
        'splatting/sample.cpp',
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': '1',  # /SUBSYSTEM:CONSOLE
        },
      },
    }, 
    {
      'target_name': 'sprite_animation',
      'type': 'executable',
      'dependencies': [
        '../engine/engine.gyp:*',
      ],
      'include_dirs': [
        './',
        '../',
        '../../',
      ],
      'sources': [
        'sprite_animation/sample.cpp',
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': '1',  # /SUBSYSTEM:CONSOLE
        },
      },
    }, 
    {
      'target_name': 'sprite_interface',
      'type': 'executable',
      'dependencies': [
        '../engine/engine.gyp:*',
      ],
      'include_dirs': [
        './',
        '../',
        '../../',
      ],
      'sources': [
        'sprite_interface/sample.cpp',
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': '1',  # /SUBSYSTEM:CONSOLE
        },
      },
    }, 
    {
      'target_name': 'sprites',
      'type': 'executable',
      'dependencies': [
        '../engine/engine.gyp:*',
      ],
      'include_dirs': [
        './',
        '../',
        '../../',
      ],
      'sources': [
        'sprites/sample.cpp',
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': '1',  # /SUBSYSTEM:CONSOLE
        },
      },
    },
    {
      'target_name': 'tiling',
      'type': 'executable',
      'dependencies': [
        '../engine/engine.gyp:*',
      ],
      'include_dirs': [
        './',
        '../',
        '../../',
      ],
      'sources': [
        'tiling/sample.cpp',
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': '1',  # /SUBSYSTEM:CONSOLE
        },
      },
    },  
    {
      'target_name': 'ui',
      'type': 'executable',
      'dependencies': [
        '../engine/engine.gyp:*',
      ],
      'include_dirs': [
        './',
        '../',
        '../../',
      ],
      'sources': [
        'ui/sample.cpp',
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': '1',  # /SUBSYSTEM:CONSOLE
        },
      },
    },  
    {
      'target_name': 'xsystem',
      'type': 'executable',
      'dependencies': [
        '../engine/engine.gyp:*',
      ],
      'include_dirs': [
        './',
        '../',
        '../../',
      ],
      'sources': [
        'xsystem/sample.cpp',
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': '1',  # /SUBSYSTEM:CONSOLE
        },
      },
    },                                                              
  ],
}
