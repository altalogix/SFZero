# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../../../SDKs/vstsdk2.4 -I ../../JuceLibraryCode -I ../../../modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -fPIC -O0
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -Wl,--no-undefined -shared -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 

  TARGET := SFZero.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../../../SDKs/vstsdk2.4 -I ../../JuceLibraryCode -I ../../../modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -fPIC -Os
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -Wl,--no-undefined -shared -fvisibility=hidden -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 

  TARGET := SFZero.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/ClickableLabel_50df57bb.o \
  $(OBJDIR)/SFZeroAudioProcessor_31b1f2c0.o \
  $(OBJDIR)/SFZeroEditor_db20151.o \
  $(OBJDIR)/juce_audio_basics_27abef.o \
  $(OBJDIR)/juce_audio_devices_1a97c0ed.o \
  $(OBJDIR)/juce_audio_formats_49190a8d.o \
  $(OBJDIR)/juce_audio_processors_142526a7.o \
  $(OBJDIR)/juce_audio_utils_403fd72d.o \
  $(OBJDIR)/juce_core_c78bf2d1.o \
  $(OBJDIR)/juce_data_structures_1f4983cd.o \
  $(OBJDIR)/juce_events_85568ec5.o \
  $(OBJDIR)/juce_graphics_95dc83a9.o \
  $(OBJDIR)/juce_gui_basics_84b3eea5.o \
  $(OBJDIR)/juce_gui_extra_b41b856d.o \
  $(OBJDIR)/juce_PluginUtilities_841689f9.o \
  $(OBJDIR)/juce_VST_Wrapper_b9b26e02.o \
  $(OBJDIR)/juce_VST3_Wrapper_20692ec0.o \
  $(OBJDIR)/SFZero_8086cd4d.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(RESOURCES)
	@echo Linking SFZero
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning SFZero
	@$(CLEANCMD)

strip:
	@echo Stripping SFZero
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/ClickableLabel_50df57bb.o: ../../Source/ClickableLabel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ClickableLabel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SFZeroAudioProcessor_31b1f2c0.o: ../../Source/SFZeroAudioProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SFZeroAudioProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SFZeroEditor_db20151.o: ../../Source/SFZeroEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SFZeroEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_27abef.o: ../../../modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_1a97c0ed.o: ../../../modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_49190a8d.o: ../../../modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_142526a7.o: ../../../modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_utils_403fd72d.o: ../../../modules/juce_audio_utils/juce_audio_utils.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_utils.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_c78bf2d1.o: ../../../modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_1f4983cd.o: ../../../modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_85568ec5.o: ../../../modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_95dc83a9.o: ../../../modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_84b3eea5.o: ../../../modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_b41b856d.o: ../../../modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_PluginUtilities_841689f9.o: ../../../modules/juce_audio_plugin_client/utility/juce_PluginUtilities.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_PluginUtilities.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST_Wrapper_b9b26e02.o: ../../../modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST3_Wrapper_20692ec0.o: ../../../modules/juce_audio_plugin_client/VST3/juce_VST3_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST3_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SFZero_8086cd4d.o: ../../../modules/SFZero/SFZero.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SFZero.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
