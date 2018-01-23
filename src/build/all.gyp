# Copyright (c) 2017 The Smart Authors.
# All rights reserved.

{
  'targets': [
    {
      'target_name': 'all',
      'type': 'none',
      'dependencies': [
        '../samples/samples.gyp:*',
        '../test/test.gyp:*',
      ],
    },
  ],
}
