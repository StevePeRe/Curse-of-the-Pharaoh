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

APP 		:= libimgui.a
CFLAGS  	:= -Wall -pedantic -std=c++11
#CCFLAGS 	:= $(CFLAGS) -std=c++11
CCFLAGS 	:= $(CFLAGS)
CC 			:= g++
C 			:= gcc
AR 			:= ar
ARFLAGS 	:= -crs
RANLIB 		:= ranlib
MKDIR		:= mkdir -p
LIBDIR		:= lib
SRC			:= src
OBJ			:= obj
#LIBDIR		:= lib

# los .a son estaticos
#LIBS		:= -lIrrlicht -lX11 -lXext -lfmod -lfmodstudio
#LIBS	:= $(LIBDIR)/tinyPTC/libimgui.a -lX11 -lXext
#INCDIRS := -I$(SRC) -I$(LIBDIR)
# ruta donde tiene que buscar los ficheros de include. que busque las del sistema, las de src y las de libs

ifdef DEBUG
# Debug
	CCFLAGS += -g
else
# Optimizaciones
	CCFLAGS += -O3
endif

# ifdef SANITIZE
# 	CCFLAGS += -fsanitize=address
# endif

# si se ha introducido make release, cambia el nombre del ejecutable y anade el path local
# ifeq ($(MAKECMDGOALS),release)
# 	APP=Prometheus_Ignis_Fur
# 	LIBS+=-Wl,-rpath=$(LIBDIR)
# endif

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
#.PHONY: info libs libs-clean libs-cleanall
.PHONY: info

$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(AR) $(ARFLAGS) $(APP) $(ALLOBJ)
	$(RANLIB) $(APP)
	$(shell mkdir $(LIBDIR))
	mv $(APP) $(LIBDIR)

# $(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CC),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CCFLAGS) $(INCDIRS))))
# #$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CC),,$(CCFLAGS) $(INCDIRS))))
# $(foreach F,$(ALLCS),$(eval $(call COMPILE,$(C),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS) $(INCDIRS))))

$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CC),$(call C2O,$(F)),$(F),,$(CCFLAGS))))
$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(C),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS))))

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
	$(RM) -r "./$(LIBDIR)"

# cleanall-release:
# 	$(RM) -r "./$(APP_SUBDIR)"

# lib rules
# libs:
# 	$(MAKE) -C $(LIBDIR)

# libs-clean:
# 	$(MAKE) -C $(LIBDIR) clean

# libs-cleanall:
# 	$(MAKE) -C $(LIBDIR) clean

# release rules
# release : cleanall-release $(APP_SUBDIR) $(APP)
	
# 	$(shell cp -r $(LIBDIR) $(APP_SUBDIR))
# 	$(shell cp -r $(MEDIADIR) $(APP_SUBDIR))
# 	$(shell mv $(APP) $(APP_SUBDIR))
# # 	$(shell zip -r $(APP).zip $(APP_SUBDIR))
# $(APP_SUBDIR) :
# 	$(MKDIR) $(APP_SUBDIR)
	