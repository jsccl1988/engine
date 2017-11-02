# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := vr_engine
DEFS_Debug := \
	'-DVE_WINDOWS' \
	'-DDEBUG'

# Flags passed to all source files.
CFLAGS_Debug :=

# Flags passed to only C files.
CFLAGS_C_Debug :=

# Flags passed to only C++ files.
CFLAGS_CC_Debug :=

INCS_Debug := \
	-Iengine \
	-I.

DEFS_Release := \
	'-DVE_WINDOWS' \
	'-DNDEBUG'

# Flags passed to all source files.
CFLAGS_Release :=

# Flags passed to only C files.
CFLAGS_C_Release :=

# Flags passed to only C++ files.
CFLAGS_CC_Release :=

INCS_Release := \
	-Iengine \
	-I.

OBJS := \
	$(obj).target/$(TARGET)/engine/buffers/fbo_ext.o \
	$(obj).target/$(TARGET)/engine/buffers/fbo_impl.o \
	$(obj).target/$(TARGET)/engine/buffers/frame_buffer.o \
	$(obj).target/$(TARGET)/engine/buffers/render_buffer.o \
	$(obj).target/$(TARGET)/engine/buffers/vbo_ext.o \
	$(obj).target/$(TARGET)/engine/buffers/vbo_impl.o \
	$(obj).target/$(TARGET)/engine/buffers/video_buffer.o \
	$(obj).target/$(TARGET)/engine/cameras/abstract_camera.o \
	$(obj).target/$(TARGET)/engine/cameras/camera.o \
	$(obj).target/$(TARGET)/engine/cameras/ortho_camera.o \
	$(obj).target/$(TARGET)/engine/engines/device_caps.o \
	$(obj).target/$(TARGET)/engine/engines/engine.o \
	$(obj).target/$(TARGET)/engine/engines/gl_device_caps.o \
	$(obj).target/$(TARGET)/engine/engines/gl_engine.o \
	$(obj).target/$(TARGET)/engine/events/action_event.o \
	$(obj).target/$(TARGET)/engine/events/action_event_source.o \
	$(obj).target/$(TARGET)/engine/events/action_listener.o \
	$(obj).target/$(TARGET)/engine/events/key_event.o \
	$(obj).target/$(TARGET)/engine/events/key_event_source.o \
	$(obj).target/$(TARGET)/engine/events/key_listener.o \
	$(obj).target/$(TARGET)/engine/events/mouse_event.o \
	$(obj).target/$(TARGET)/engine/events/mouse_event_source.o \
	$(obj).target/$(TARGET)/engine/events/mouse_listener.o \
	$(obj).target/$(TARGET)/engine/events/system_event.o \
	$(obj).target/$(TARGET)/engine/events/window_event.o \
	$(obj).target/$(TARGET)/engine/ext/multi_texture_ext.o \
	$(obj).target/$(TARGET)/engine/ext/multi_texture_impl.o \
	$(obj).target/$(TARGET)/engine/ext/vsync_ext.o \
	$(obj).target/$(TARGET)/engine/ext/vsync_impl.o \
	$(obj).target/$(TARGET)/engine/fonts/font.o \
	$(obj).target/$(TARGET)/engine/fonts/font_cache.o \
	$(obj).target/$(TARGET)/engine/fonts/font_descriptor.o \
	$(obj).target/$(TARGET)/engine/fonts/win_font.o \
	$(obj).target/$(TARGET)/engine/fonts/x_font.o \
	$(obj).target/$(TARGET)/engine/io/data_ouput_stream.o \
	$(obj).target/$(TARGET)/engine/io/file.o \
	$(obj).target/$(TARGET)/engine/io/file_input_stream.o \
	$(obj).target/$(TARGET)/engine/io/file_output_stream.o \
	$(obj).target/$(TARGET)/engine/io/input_stream.o \
	$(obj).target/$(TARGET)/engine/io/output_stream.o \
	$(obj).target/$(TARGET)/engine/io/text_writer.o \
	$(obj).target/$(TARGET)/engine/loaders/3ds_loader.o \
	$(obj).target/$(TARGET)/engine/loaders/bmp_loader.o \
	$(obj).target/$(TARGET)/engine/loaders/loader.o \
	$(obj).target/$(TARGET)/engine/loaders/png_loader.o \
	$(obj).target/$(TARGET)/engine/loaders/tga_loader.o \
	$(obj).target/$(TARGET)/engine/loaders/texture_loader.o \
	$(obj).target/$(TARGET)/engine/logs/log.o \
	$(obj).target/$(TARGET)/engine/math/bounding_box.o \
	$(obj).target/$(TARGET)/engine/math/frustum.o \
	$(obj).target/$(TARGET)/engine/math/maths.o \
	$(obj).target/$(TARGET)/engine/math/matrix3f.o \
	$(obj).target/$(TARGET)/engine/math/matrix4f.o \
	$(obj).target/$(TARGET)/engine/math/plane.o \
	$(obj).target/$(TARGET)/engine/math/vector2f.o \
	$(obj).target/$(TARGET)/engine/math/vector3f.o \
	$(obj).target/$(TARGET)/engine/math/vector4f.o \
	$(obj).target/$(TARGET)/engine/models/mesh.o \
	$(obj).target/$(TARGET)/engine/models/model.o \
	$(obj).target/$(TARGET)/engine/models/sphere.o \
	$(obj).target/$(TARGET)/engine/shaders/program.o \
	$(obj).target/$(TARGET)/engine/shaders/shaders.o \
	$(obj).target/$(TARGET)/engine/shaders/shaders_ext.o \
	$(obj).target/$(TARGET)/engine/shaders/shaders_impl.o \
	$(obj).target/$(TARGET)/engine/sprites/abstract_sprite.o \
	$(obj).target/$(TARGET)/engine/sprites/animated_sprite.o \
	$(obj).target/$(TARGET)/engine/sprites/movable_sprite.o \
	$(obj).target/$(TARGET)/engine/sprites/simple_sprite.o \
	$(obj).target/$(TARGET)/engine/sprites/sprite.o \
	$(obj).target/$(TARGET)/engine/states/blend_state.o \
	$(obj).target/$(TARGET)/engine/states/color_state.o \
	$(obj).target/$(TARGET)/engine/states/gl_gpu_state_manager.o \
	$(obj).target/$(TARGET)/engine/states/gpu_state.o \
	$(obj).target/$(TARGET)/engine/states/gpu_state_dumper.o \
	$(obj).target/$(TARGET)/engine/states/gpu_state_manager.o \
	$(obj).target/$(TARGET)/engine/states/viewport_state.o \
	$(obj).target/$(TARGET)/engine/textures/mips_ext.o \
	$(obj).target/$(TARGET)/engine/textures/mips_impl.o \
	$(obj).target/$(TARGET)/engine/textures/texture.o \
	$(obj).target/$(TARGET)/engine/tools/dynamic_huffman_tree.o \
	$(obj).target/$(TARGET)/engine/tools/keys_codec.o \
	$(obj).target/$(TARGET)/engine/tools/linux_timer.o \
	$(obj).target/$(TARGET)/engine/tools/memory_manager.o \
	$(obj).target/$(TARGET)/engine/tools/string_tool.o \
	$(obj).target/$(TARGET)/engine/tools/texture_tool.o \
	$(obj).target/$(TARGET)/engine/tools/timer_factory.o \
	$(obj).target/$(TARGET)/engine/tools/win_timer.o \
	$(obj).target/$(TARGET)/engine/ui/border.o \
	$(obj).target/$(TARGET)/engine/ui/button.o \
	$(obj).target/$(TARGET)/engine/ui/button_list.o \
	$(obj).target/$(TARGET)/engine/ui/checkbox.o \
	$(obj).target/$(TARGET)/engine/ui/desktop.o \
	$(obj).target/$(TARGET)/engine/ui/editbox.o \
	$(obj).target/$(TARGET)/engine/ui/editbox_filter.o \
	$(obj).target/$(TARGET)/engine/ui/editbox_numbers_filter.o \
	$(obj).target/$(TARGET)/engine/ui/form.o \
	$(obj).target/$(TARGET)/engine/ui/gauge.o \
	$(obj).target/$(TARGET)/engine/ui/gui_builder.o \
	$(obj).target/$(TARGET)/engine/ui/label.o \
	$(obj).target/$(TARGET)/engine/ui/panel.o \
	$(obj).target/$(TARGET)/engine/ui/slot.o \
	$(obj).target/$(TARGET)/engine/ui/slot_item.o \
	$(obj).target/$(TARGET)/engine/ui/ui.o \
	$(obj).target/$(TARGET)/engine/ui/ui_container.o \
	$(obj).target/$(TARGET)/engine/ui/ui_control.o \
	$(obj).target/$(TARGET)/engine/web/cef/cef_app_impl.o \
	$(obj).target/$(TARGET)/engine/web/cef/cef_handler_impl.o \
	$(obj).target/$(TARGET)/engine/web/web.o \
	$(obj).target/$(TARGET)/engine/windows/critical_section.o \
	$(obj).target/$(TARGET)/engine/windows/thread_factory.o \
	$(obj).target/$(TARGET)/engine/windows/win_message_pump.o \
	$(obj).target/$(TARGET)/engine/windows/win_message_queue.o \
	$(obj).target/$(TARGET)/engine/windows/win_message_router.o \
	$(obj).target/$(TARGET)/engine/windows/window.o \
	$(obj).target/$(TARGET)/engine/windows/window_system.o \
	$(obj).target/$(TARGET)/engine/windows/window_system_factory.o \
	$(obj).target/$(TARGET)/engine/windows/windows_system.o \
	$(obj).target/$(TARGET)/engine/windows/xwindow_system.o \
	$(obj).target/$(TARGET)/engine/zlib/zlib.o \
	$(obj).target/$(TARGET)/engine/object.o \
	$(obj).target/$(TARGET)/engine/visible_object.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Debug :=

LDFLAGS_Release :=

LIBS :=

$(obj).target/engine/libvr_engine.a: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/engine/libvr_engine.a: LIBS := $(LIBS)
$(obj).target/engine/libvr_engine.a: TOOLSET := $(TOOLSET)
$(obj).target/engine/libvr_engine.a: $(OBJS) FORCE_DO_CMD
	$(call do_cmd,alink_thin)

all_deps += $(obj).target/engine/libvr_engine.a
# Add target alias
.PHONY: vr_engine
vr_engine: $(obj).target/engine/libvr_engine.a

# Add target alias to "all" target.
.PHONY: all
all: vr_engine

