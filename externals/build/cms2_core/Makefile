# ----------------------------------------------------------------------- #
# Makefile for CORE
# creates an shared lib
# ----------------------------------------------------------------------- #

include ${PAC}/tools/Makefile.common

# specifiy the sources here
# ----------------------------------------------------------------------- #

# source files
tag             := HEAD
libraries       := libCMS2CORE.so
package_dir_rel := externals/source/cms2_core/$(tag)/CORE
sources         := MITConversionUtilities.cc \
					electronSelections.cc \
					electronSelectionsParameters.cc \
					eventSelections.cc \
					jetSelections.cc \
					mcSelections.cc \
					mcbtagSFuncert.cc \
					metSelections.cc \
					muonSelections.cc \
					ssSelections.cc \
					susySelections.cc \
					trackSelections.cc \
					triggerUtils.cc \
					utilities.cc
#sources         = $(wildcard $(package_dir)/*.cc) $(wildcard $(package_dir)/jetsmear/*.cc) $(wildcard $(package_dir)/MT2/*.cc) 
include_dir     := .

# additional libraries
# ----------------------------------------------------------------------- #

# CMS2 header 
$(eval $(include_cms2_header))

# package setup
# ----------------------------------------------------------------------- #

package_dir := $(project_dir)/$(package_dir_rel)

include_dir := $(addprefix $(strip $(package_dir))/,$(include_dir))

#sources     := $(call add-path,$(package_dir),$(sources))
#source_dir  := $(sort $(dir $(sources)))
source_dir  := $(package_dir)
sources     := $(call add-path,$(source_dir),$(sources))


object_dir  := $(call add-path,$(project_obj),$(package_dir_rel))
objects     := $(call source-to-object,$(sources),$(object_dir)) 

dep_dir     := $(call add-path,$(project_obj),$(package_dir_rel))
deps        := $(call source-to-dep,$(sources),$(dep_dir)) 

libraries   := $(call add-path,$(project_lib),$(libraries))

vpath %.h  $(include_dir)
vpath %.cc $(source_dir)
vpath %.o  $(object_dir)
vpath %.d  $(dep_dir)

CPPFLAGS    += $(addprefix -I,$(sort $(include_dir)))

# rules
# ----------------------------------------------------------------------- #

all:

# for troubleshooting
.PHONY: test
test:
	@echo package_dir = $(package_dir)
	@echo package_dir_rel = $(package_dir_rel)
	@echo sources = $(sources)
	@echo source_dir = $(source_dir)
	@echo includes = $(includes)
	@echo include_dir = $(include_dir)
	@echo objects = $(objects)
	@echo object_dir = $(object_dir)
	@echo deps = $(deps)
	@echo dep_dir = $(dep_dir)
	@echo libraries = $(libraries)
	@echo dep rule dependencies = $(call add-path,$(source_dir),%.cc)

.PHONY: deps
deps: $(dep)

.PHONY: libraries
libraries: $(libraries)

.PHONY: all
all: $(deps) $(libraries)

.PHONY: clean
clean:
	$(RM) $(objects) $(libraries) $(deps) $(extra_clean) 
	$(RMDIR) $(dep_dir) $(object_dir)

# system rules
# ----------------------------------------------------------------------- #

# keep object files
.PRECIOUS: $(call add-path,$(object_dir),%.o)

# compile all the objects
$(call add-path,$(object_dir),%.o): $(call add-path,$(source_dir),%.cc)
	@mkdir -p $(object_dir)
	$(COMPILE.cc) $(addprefix -D,$(defines)) $(OUTPUT_OPTION) $<

# link all the library
$(call add-path,$(project_lib),%.so): $(objects)
	@mkdir -p $(project_lib)
	$(SHAREDLIB.cc) $@ $^

# autmatically resolve dependencies
# ----------------------------------------------------------------------- #

ifneq "$(MAKECMDGOALS)" "clean"
  -include $(deps)
endif

$(call add-path,$(dep_dir),%.d): $(call add-path,$(source_dir),%.cc)
	@mkdir -p $(dep_dir)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $(addprefix -D,$(defines)) -M $< | \
	$(SED) 's,\($(notdir $*)\.o\) *:,$(dir $@)\1 $@: ,' > $@.tmp
	@$(MV) $@.tmp $@

