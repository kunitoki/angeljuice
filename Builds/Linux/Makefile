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

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../Modules/thirdparty -I ../../Modules/juce/modules -I ../../Modules/thirdparty/lua/sdk/src/ -I ../../Modules/thirdparty/luabind/sdk/
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../Modules/thirdparty -I ../../Modules/juce/modules -I ../../Modules/thirdparty/lua/sdk/src/ -I ../../Modules/thirdparty/luabind/sdk/
  TARGET := angeljuice
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

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../Modules/thirdparty -I ../../Modules/juce/modules -I ../../Modules/thirdparty/lua/sdk/src/ -I ../../Modules/thirdparty/luabind/sdk/
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -O3
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../Modules/thirdparty -I ../../Modules/juce/modules -I ../../Modules/thirdparty/lua/sdk/src/ -I ../../Modules/thirdparty/luabind/sdk/
  TARGET := angeljuice
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/AngelScriptCrypt_60b56bff.o \
  $(OBJDIR)/AngelScriptFile_aad9cbd5.o \
  $(OBJDIR)/AngelScriptCore_bad8bc78.o \
  $(OBJDIR)/AngelScriptString_d2720aea.o \
  $(OBJDIR)/ScriptablePlugin_9cffda66.o \
  $(OBJDIR)/ScriptablePreprocessor_53d0e802.o \
  $(OBJDIR)/ScriptableEngine_9e645f5.o \
  $(OBJDIR)/MainWindow_863ef6c8.o \
  $(OBJDIR)/MainComponent_8d17822f.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/angelscript_5c8981d6.o \
  $(OBJDIR)/juce_audio_basics_f90d4cc4.o \
  $(OBJDIR)/juce_audio_devices_70988082.o \
  $(OBJDIR)/juce_audio_formats_9f19ca22.o \
  $(OBJDIR)/juce_audio_processors_7a5b227c.o \
  $(OBJDIR)/juce_core_42fdda6.o \
  $(OBJDIR)/juce_cryptography_fa925000.o \
  $(OBJDIR)/juce_data_structures_10670e2.o \
  $(OBJDIR)/juce_events_a5af071a.o \
  $(OBJDIR)/juce_graphics_69e6c97e.o \
  $(OBJDIR)/juce_gui_basics_1bcd41fa.o \
  $(OBJDIR)/juce_gui_extra_aeabaa02.o \
  $(OBJDIR)/juce_opengl_65f72f46.o \
  $(OBJDIR)/juce_video_4394ef22.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking angeljuice
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning angeljuice
	@$(CLEANCMD)

strip:
	@echo Stripping angeljuice
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/AngelScriptCrypt_60b56bff.o: ../../Source/Engine/Bindings/AngelScriptCrypt.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AngelScriptCrypt.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AngelScriptFile_aad9cbd5.o: ../../Source/Engine/Bindings/AngelScriptFile.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AngelScriptFile.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AngelScriptCore_bad8bc78.o: ../../Source/Engine/Bindings/AngelScriptCore.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AngelScriptCore.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AngelScriptString_d2720aea.o: ../../Source/Engine/Bindings/AngelScriptString.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AngelScriptString.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ScriptablePlugin_9cffda66.o: ../../Source/Engine/ScriptablePlugin.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ScriptablePlugin.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ScriptablePreprocessor_53d0e802.o: ../../Source/Engine/ScriptablePreprocessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ScriptablePreprocessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ScriptableEngine_9e645f5.o: ../../Source/Engine/ScriptableEngine.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ScriptableEngine.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainWindow_863ef6c8.o: ../../Source/Interface/MainWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainComponent_8d17822f.o: ../../Source/Interface/MainComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/angelscript_5c8981d6.o: ../../Modules/thirdparty/angelscript/angelscript.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling angelscript.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_f90d4cc4.o: ../../Modules/juce/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_70988082.o: ../../Modules/juce/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_9f19ca22.o: ../../Modules/juce/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_7a5b227c.o: ../../Modules/juce/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_42fdda6.o: ../../Modules/juce/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_cryptography_fa925000.o: ../../Modules/juce/modules/juce_cryptography/juce_cryptography.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_cryptography.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_10670e2.o: ../../Modules/juce/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_a5af071a.o: ../../Modules/juce/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_69e6c97e.o: ../../Modules/juce/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_1bcd41fa.o: ../../Modules/juce/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_aeabaa02.o: ../../Modules/juce/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_opengl_65f72f46.o: ../../Modules/juce/modules/juce_opengl/juce_opengl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_opengl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_video_4394ef22.o: ../../Modules/juce/modules/juce_video/juce_video.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_video.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
