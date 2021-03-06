# Copyright (c) 2017 The Smart Authors.
# All rights reserved.

{
  'targets': [
    {
      'target_name': 'vr_engine',
      'type': 'static_library',
      'include_dirs': [
        './',
        '../',
      ],
      "conditions": [
        ["OS=='win'", {
          'link_settings': {
            'libraries': [
              '-lkernel32.lib',
              '-luser32.lib',
              '-lcomdlg32.lib',
              '-lgdi32.lib',
              '-lshell32.lib',
              '-lcomctl32.lib',
              '-ladvapi32.lib',
              '-lole32.lib',
              '-lshlwapi.lib',
              '-lrpcrt4.lib',
              '-lopengl32.lib',
              '-lglu32.lib',
            ],
           },
        }],
        ["OS=='linux'", {
          'link_settings': {
            'libraries': [
              '-lX11',
              '-lGL',
              '-lGLU',
            ],
           },
        }],        
      ],
      'sources': [
        'buffers/fbo_ext.cpp',
        'buffers/fbo_ext.h',
        'buffers/fbo_impl.cpp',
        'buffers/fbo_impl.h',
        'buffers/frame_buffer.cpp',
        'buffers/frame_buffer.h',
        'buffers/render_buffer.cpp',
        'buffers/render_buffer.h',
        'buffers/vbo_ext.cpp',
        'buffers/vbo_ext.h',
        'buffers/vbo_impl.cpp',
        'buffers/vbo_impl.h',
        'buffers/video_buffer.cpp',
        'buffers/video_buffer.h',
        'cameras/abstract_camera.cpp',
        'cameras/abstract_camera.h',
        'cameras/camera.cpp',
        'cameras/camera.h',
        'cameras/ortho_camera.cpp',
        'cameras/ortho_camera.h',
        'engines/device_caps.cpp',
        'engines/device_caps.h',
        'engines/engine.cpp',
        'engines/engine.h',
        'engines/gl_device_caps.cpp',
        'engines/gl_device_caps.h',
        'engines/gl_engine.cpp',
        'engines/gl_engine.h', 
        'events/action_event.cpp',
        'events/action_event.h',
        'events/action_event_source.cpp',
        'events/action_event_source.h',
        'events/action_listener.cpp',
        'events/action_listener.h',
        'events/key_event.cpp',
        'events/key_event.h',
        'events/key_event_source.cpp',
        'events/key_event_source.h',
        'events/key_listener.cpp',
        'events/key_listener.h',
        'events/mouse_event.cpp',
        'events/mouse_event.h',
        'events/mouse_event_source.cpp',
        'events/mouse_event_source.h',
        'events/mouse_listener.cpp',
        'events/mouse_listener.h',
        'events/system_event.cpp',
        'events/system_event.h',
        'events/window_event.cpp',
        'events/window_event.h',
        'ext/multi_texture_ext.cpp',
        'ext/multi_texture_ext.h',
        'ext/multi_texture_impl.cpp',
        'ext/multi_texture_impl.h',
        'ext/vsync_ext.cpp',
        'ext/vsync_ext.h', 
        'ext/vsync_impl.cpp',
        'ext/vsync_impl.h',
        'fonts/font.cpp',
        'fonts/font.h',
        'fonts/font_cache.cpp',
        'fonts/font_cache.h',
        'fonts/font_descriptor.cpp',
        'fonts/font_descriptor.h',
        'fonts/win_font.cpp',
        'fonts/win_font.h',
        'fonts/x_font.cpp',
        'fonts/x_font.h',
        'io/data_ouput_stream.cpp',
        'io/data_ouput_stream.h', 
        'io/file.cpp',
        'io/file.h', 
        'io/file_input_stream.cpp',
        'io/file_input_stream.h', 
        'io/file_output_stream.cpp',
        'io/file_output_stream.h', 
        'io/input_stream.cpp',
        'io/input_stream.h', 
        'io/output_stream.cpp',
        'io/output_stream.h', 
        'io/text_writer.cpp',
        'io/text_writer.h',
        'loaders/3ds_loader.cpp',
        'loaders/3ds_loader.h',
        'loaders/bmp_loader.cpp',
        'loaders/bmp_loader.h',
        'loaders/loader.cpp',
        'loaders/loader.h',
        'loaders/png_loader.cpp',
        'loaders/png_loader.h',
        'loaders/tga_loader.cpp',
        'loaders/tga_loader.h', 
        'loaders/texture_loader.cpp',
        'loaders/texture_loader.h',
        'logs/log.cpp',
        'logs/log.h',
        'math/bounding_box.cpp',
        'math/bounding_box.h', 
        'math/frustum.cpp',
        'math/frustum.h', 
        'math/maths.cpp',
        'math/maths.h', 
        'math/matrix3f.cpp',
        'math/matrix3f.h', 
        'math/matrix4f.cpp',
        'math/matrix4f.h', 
        'math/plane.cpp',
        'math/plane.h', 
        'math/vector2f.cpp',
        'math/vector2f.h',
        'math/vector3f.cpp',
        'math/vector3f.h',  
        'math/vector4f.cpp',
        'math/vector4f.h',
        'models/mesh.cpp',
        'models/mesh.h', 
        'models/model.cpp',
        'models/model.h',
        'models/model_interface.h',
        'models/sphere.cpp',
        'models/sphere.h',
        'shaders/program.cpp',
        'shaders/program.h', 
        'shaders/shaders.cpp',
        'shaders/shaders.h', 
        'shaders/shaders_ext.cpp',
        'shaders/shaders_ext.h', 
        'shaders/shaders_impl.cpp',
        'shaders/shaders_impl.h',
        'sprites/abstract_sprite.cpp',
        'sprites/abstract_sprite.h', 
        'sprites/animated_sprite.cpp',
        'sprites/animated_sprite.h',
        'sprites/movable_sprite.cpp',
        'sprites/movable_sprite.h',
        'sprites/simple_sprite.cpp',
        'sprites/simple_sprite.h',
        'sprites/sprite.cpp',
        'sprites/sprite.h',
        'states/alpha_test_state.h',
        'states/blend_state.cpp',
        'states/blend_state.h',
        'states/buffer_state.h',
        'states/color_state.cpp',
        'states/color_state.h',
        'states/depth_test_state.h',
        'states/gl_gpu_state_manager.cpp',
        'states/gl_gpu_state_manager.h',
        'states/gpu_state.cpp',
        'states/gpu_state.h',   
        'states/gpu_state_dumper.cpp',
        'states/gpu_state_dumper.h',
        'states/gpu_state_manager.cpp',
        'states/gpu_state_manager.h',
        'states/matrix_state.h',
        'states/shaders_state.h',
        'states/textures_state.h',
        'states/viewport_state.cpp',
        'states/viewport_state.h',
        'textures/mips_ext.cpp',
        'textures/mips_ext.h', 
        'textures/mips_impl.cpp',
        'textures/mips_impl.h',
        'textures/texture.cpp',
        'textures/texture.h',
        'tools/dynamic_huffman_tree.cpp',
        'tools/dynamic_huffman_tree.h',
        'tools/keys_codec.cpp',
        'tools/keys_codec.h',
        'tools/linux_timer.cpp',
        'tools/linux_timer.h',
        'tools/memory_manager.cpp',
        'tools/memory_manager.h',
        'tools/string_tool.cpp',
        'tools/string_tool.h', 
        'tools/texture_tool.cpp',
        'tools/texture_tool.h',
        'tools/timer.h',
        'tools/timer_factory.cpp',
        'tools/timer_factory.h',
        'tools/win_timer.cpp',
        'tools/win_timer.h',
        'ui/border.cpp',
        'ui/border.h',
        'ui/button.cpp',
        'ui/button.h', 
        'ui/button_list.cpp',
        'ui/button_list.h',
        'ui/checkbox.cpp',
        'ui/checkbox.h', 
        'ui/desktop.cpp',
        'ui/desktop.h',
        'ui/editbox.cpp',
        'ui/editbox.h', 
        'ui/editbox_filter.cpp',
        'ui/editbox_filter.h',
        'ui/editbox_numbers_filter.cpp',
        'ui/editbox_numbers_filter.h',
        'ui/form.cpp',
        'ui/form.h',
        'ui/gauge.cpp',
        'ui/gauge.h', 
        'ui/gui_builder.cpp',
        'ui/gui_builder.h',
        'ui/label.cpp',
        'ui/label.h',
        'ui/panel.cpp',
        'ui/panel.h', 
        'ui/slot.cpp',
        'ui/slot.h',
        'ui/slot_item.cpp',
        'ui/slot_item.h', 
        'ui/ui.cpp',
        'ui/ui.h',
        'ui/ui_container.cpp',
        'ui/ui_container.h',
        'ui/ui_control.cpp',
        'ui/ui_control.h', 
        'windows/critical_section.cpp',
        'windows/critical_section.h',
        'windows/thread_factory.cpp',
        'windows/thread_factory.h',
        'windows/win_message_pump.cpp',
        'windows/win_message_pump.h',
        'windows/win_message_queue.cpp',
        'windows/win_message_queue.h',
        'windows/win_message_router.cpp',
        'windows/win_message_router.h',
        'windows/window.cpp',
        'windows/window.h',
        'windows/window_system.cpp',
        'windows/window_system.h',
        'windows/window_system_factory.cpp',
        'windows/window_system_factory.h',
        'windows/windows_system.cpp',
        'windows/windows_system.h',
        'windows/xwindow_system.cpp',
        'windows/xwindow_system.h',
        'zlib/zlib.cpp',
        'zlib/zlib.h', 
        'common.h',
        'consts.h',
        'debug.h',
        'keys.h',
        'object.cpp',
        'object.h',
        'types.h',
        'visible_object.cpp',
        'visible_object.h',
      ],
    },
  ],
}
