# Copyright (c) 2017 The Smart Authors.
# All rights reserved.

{
  "conditions": [
    ["OS=='win'", {
      "target_defaults": {
        "default_configuration": "Release_x64",
        "configurations": {
          "Debug_Win32": {
            "msvs_configuration_platform": "Win32",
          },
          "Debug_x64": {
            "msvs_configuration_platform": "x64",
          },
          "Release_Win32": {
            "msvs_configuration_platform": "Win32",
          },
          "Release_x64": {
            "msvs_configuration_platform": "x64",
          }
        },
        'msvs_configuration_attributes': {
          'CharacterSet': '2'
        },
        'msvs_disabled_warnings': [
            4201,  # nonstandard extension used : nameless struct/union.
            4577,  # 'noexcept' used with no exception handling mode specified
            4530,  # C++ exception handler used, but unwind semantics are not enabled. 
        ],        
        'defines': [
          'VE_WINDOWS',
        ],
      }
    }],
    ["OS=='linux'",{
      "target_defaults": {
        "default_configuration": "Debug",
        "configurations": {
          "Debug": {
            "defines": [
              "DEBUG"
            ],
          },
          "Release": {
            "defines": [
              "NDEBUG"
            ],
          }
        },
        'defines': [
          'VE_LINUX',
        ],
      }
    }],
    ["OS=='mac'",{
      "target_defaults": {
        "default_configuration": "Debug",
        "xcode_settings": {
        },
        "configurations": {
          "Debug": {
            "defines": [
              "DEBUG"
            ],
            "xcode_settings": {
              "GCC_OPTIMIZATION_LEVEL": "0",
              "GCC_GENERATE_DEBUGGING_SYMBOLS": "YES"
            }
          },
          "Release": {
            "defines": [
              "NDEBUG"
            ],
            "xcode_settings": {
              "GCC_OPTIMIZATION_LEVEL": "3",
              "GCC_GENERATE_DEBUGGING_SYMBOLS": "NO",
              "DEAD_CODE_STRIPPING": "YES",
              "GCC_INLINES_ARE_PRIVATE_EXTERN": "YES"
            }
          }
        },
      }
    }]    
  ]
}
