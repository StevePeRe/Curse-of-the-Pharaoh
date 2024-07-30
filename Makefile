##################################################################
### MACROS
##################################################################

# $(1) : Compiler
# $(2) : Object file to generate
# $(3) : Source file
# $(4) : Additional dependencies
# $(5) : Compiler flags
define COMPILE
$(2) : $(3) $(4)
	$(1) -c -o $(2) $(3) $(5)
endef

# $(1) : Source file
define C2O
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

# $(1) : Source file
define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef
##################################################################
## CONFIG
##################################################################

APP 		:= Curse_of_the_Pharaoh
CFLAGS  	:= -Wall -Wpedantic -Wconversion -Wextra
CCFLAGS 	:= $(CFLAGS) -std=c++20
CC 			:= g++
C 			:= gcc
MKDIR		:= mkdir -p
SRC			:= src
OBJ			:= obj
LIBDIR		:= thirdparty
MEDIADIR	:= media
FMOD_LIST	:= bancos_fmod
BUILD_DIR 	:= build

MINGW_DIR := /mingw64/bin

LIB_PATH := $(BUILD_DIR)/$(LIBDIR)


# DIRS
# los includes estan mal de Freetype y por tanto hay que incluir este directorio para que funcione correctamente segun la web oficial
FREETYPE2_DIR := /usr/include/freetype2
FMOD_LIB_DIR := $(LIBDIR)/FMOD/lib

FMOD_INSTR_LIB := cp $(FMOD_LIB_DIR)/*.so.* $(BUILD_DIR)/$(LIBDIR)
DLL_INSTR := 


AUDIO_LIBS := -L$(FMOD_LIB_DIR) -lfmod -lfmodstudio
OPEN_GL_LIBS := -lGL -L$(LIBDIR)/GLAD/lib -lglad
UI_LIB := -L$(LIBDIR)/imgui/lib -limgui
READ_IMAGE_LIB := -L$(LIBDIR)/stb/lib -lstb

# SYSTEM LIBS
READ_3D_LIB := -lassimp
READ_FONT_LIB := -lfreetype
GLFW_LIB := -lglfw

LIB_NAMES_LDD := -e 'libassimp' -e 'libfreetype' -e 'glfw' -e 'libssl' -e 'libcrypto' -e 'fmod' -e 'fmodstudio' -e 'libstdc++'

SAN_LIBS := -lasan -lubsan

# Windows DLL
FMOD_DLLs :=  $(LIBDIR)/FMOD/lib/fmod.dll $(LIBDIR)/FMOD/lib/fmodL.dll $(LIBDIR)/FMOD/lib/fmodstudio.dll $(LIBDIR)/FMOD/lib/fmodstudioL.dll
ALL_DLLs := $(FMOD_DLLs) $(MINGW_DIR)/glfw3.dll $(MINGW_DIR)/libassimp-5.dll $(MINGW_DIR)/libfreetype-6.dll

ALL_STATIC_LIBS := $(LIBDIR)/GLAD/lib/libglad.a $(LIBDIR)/stb/lib/libstb.a $(LIBDIR)/ImGui/lib/libimgui.a

# Rutas personalizadas
LOCAL_PATH := -Wl,-rpath=$(LIBDIR):$(FMOD_LIB_DIR)

# los .a son estaticos
LIBS := $(OPEN_GL_LIBS) $(GLFW_LIB) $(UI_LIB) $(AUDIO_LIBS) $(READ_IMAGE_LIB) $(READ_3D_LIB) $(READ_FONT_LIB)
INCDIRS := -I$(SRC) -I$(LIBDIR) -I$(FREETYPE2_DIR)
# ruta donde tiene que buscar los ficheros de include. que busque las del sistema, las de src y las de libs


ifdef DEBUG
# Debug
	CCFLAGS += -g
else
# Optimizaciones
	CCFLAGS += -O3
endif

ifdef SANITIZE
	CCFLAGS += -fsanitize=address -g
	LIBS	:= $(SAN_LIBS) $(OPEN_GL_LIBS) $(GLFW_LIB) $(UI_LIB) $(AUDIO_LIBS) $(READ_IMAGE_LIB) $(READ_3D_LIB) $(READ_FONT_LIB)
else
	CCFLAGS += -DNDEBUG
endif

ifeq ($(OS),Windows_NT)
	INCDIRS = -I$(SRC) -I$(LIBDIR) -I/mingw64/include/freetype2
	LIBS = $(ALL_DLLs) $(ALL_STATIC_LIBS) -static -mwindows
	LIB_PATH = $(BUILD_DIR)
	FMOD_INSTR_LIB = cp $(FMOD_DLLs) $(LIB_PATH)
	DLL_INSTR = cp $(MINGW_DIR)/zlib1.dll $(MINGW_DIR)/libwinpthread-1.dll $(MINGW_DIR)/libstdc++-6.dll $(MINGW_DIR)/libpng16-16.dll $(MINGW_DIR)/libpcre2-8-0.dll $(MINGW_DIR)/libminizip-1.dll $(MINGW_DIR)/libintl-8.dll $(MINGW_DIR)/libiconv-2.dll $(MINGW_DIR)/libharfbuzz-0.dll $(MINGW_DIR)/libbrotlicommon.dll $(MINGW_DIR)/libbrotlidec.dll $(MINGW_DIR)/libgcc_s_seh-1.dll $(MINGW_DIR)/libbz2-1.dll $(MINGW_DIR)/libglib-2.0-0.dll $(MINGW_DIR)/libgraphite2.dll $(BUILD_DIR)
endif

# Para ver ficheros -> find
# Ver ficheros. iname para no tener cuenta de mayus
ALLCPPS	:= $(shell find src/ -type f -iname *.cpp)
# ALLCPPSOBJ	:= $(patsubst %.cpp,%.o,$(ALLCPPS))
ALLCS	:= $(shell find src/ -type f -iname *.c)
# cambiar .c por .o. con un patron
# ALLCSOBJ:= $(patsubst %.c,%.o,$(ALLCS))
ALLOBJ	:= $(foreach F,$(ALLCPPS) $(ALLCS),$(call C2O,$(F)))

# Para ver lista de directorios de una carpeta: find src/ -type d
SUBDIRS 	:= $(shell find src/ -type d)
# Todo lo que haya en src y lo que sea, lo cambio por obj y lo que sea
OBJSUBDIRS 	:= $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

# Para decirle que no espere nada de salida.
# Si no lo ponemos, siempre se lanzaria
.PHONY: info libs libs-clean libs-cleanall

all: $(APP)
	$(MKDIR) $(BUILD_DIR)/$(LIBDIR)
	$(eval SYS_LIB_DIRS := $(shell ldd $(APP) | grep -oP '(?<=\s=>\s).*(?=\s)' | grep $(LIB_NAMES_LDD)))
	cp $(SYS_LIB_DIRS) $(LIB_PATH)
	$(FMOD_INSTR_LIB)
	$(DLL_INSTR)
	cp -r $(MEDIADIR) $(FMOD_LIST)  $(BUILD_DIR)
	mv $(APP) $(BUILD_DIR)

debug: cleanall
	$(MAKE) -j8 DEBUG=1

sanitize: cleanall
	$(MAKE) -j8 SANITIZE=1

release: libs all

$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(CC) -o $(APP) $(ALLOBJ) $(LIBS) $(LOCAL_PATH)

$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CC),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CCFLAGS) $(INCDIRS))))
$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(C),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS) $(INCDIRS))))
			
info:
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLCSOBJ))

# Se creara si alguien lo necesita, para que dispare

# Varios objetivos, si falta uno, lo sabra. Los crea todos
$(OBJSUBDIRS) :
	$(MKDIR) $(OBJSUBDIRS)

## clean rules
clean:
	$(RM) -r "./$(OBJ)"

cleanall: clean
	clear
	$(RM) "./$(APP)"
	$(RM) -r "./$(BUILD_DIR)"

# lib rules
libs:
	$(MAKE) -C $(LIBDIR)

libs-clean:
	$(MAKE) -C $(LIBDIR) clean

libs-cleanall:
	$(MAKE) -C $(LIBDIR) cleanall

	