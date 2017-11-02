# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := xsystem
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
	-Isamples \
	-I. \
	-I..

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
	-Isamples \
	-I. \
	-I..

OBJS := \
	$(obj).target/$(TARGET)/samples/xsystem/sample.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# Make sure our dependencies are built before any of us.
$(OBJS): | $(obj).target/engine/libvr_engine.a

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

LIBS := \
	-lkernel32.lib \
	-luser32.lib \
	-lcomdlg32.lib \
	-lgdi32.lib \
	-lshell32.lib \
	-lcomctl32.lib \
	-ladvapi32.lib \
	-lole32.lib \
	-lshlwapi.lib \
	-lrpcrt4.lib \
	-lopengl32.lib \
	-lglu32.lib \
	-lcef.dll.lib

$(builddir)/xsystem: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(builddir)/xsystem: LIBS := $(LIBS)
$(builddir)/xsystem: LD_INPUTS := $(OBJS) $(obj).target/engine/libvr_engine.a
$(builddir)/xsystem: TOOLSET := $(TOOLSET)
$(builddir)/xsystem: $(OBJS) $(obj).target/engine/libvr_engine.a FORCE_DO_CMD
	$(call do_cmd,link)

all_deps += $(builddir)/xsystem
# Add target alias
.PHONY: xsystem
xsystem: $(builddir)/xsystem

# Add executable to "all" target.
.PHONY: all
all: $(builddir)/xsystem

