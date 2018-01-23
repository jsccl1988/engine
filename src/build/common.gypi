# Copyright (c) 2017 The Smart Authors.
# All rights reserved.

{
  "conditions": [
    ["OS=='win'", {
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
        'msvs_disabled_warnings': [4577],
        'defines': [
          'VE_LINUX',
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
