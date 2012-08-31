# ----------------------------------------------------------------------- #
# Makefile for RootTools library
# creates an interative shared lib to use with ROOT or stand alone c++ code
# ----------------------------------------------------------------------- #

include ${PAC}/tools/Makefile.common

# specifiy the sources here
# ----------------------------------------------------------------------- #

# source files
libraries       := libRootTools.so
package_dir_rel := packages/RootTools
sources         := MiscTools.cc              	\
				   CompareContentsOfTTrees.cc 	\
				   DrawAllBranches.cc         	\
				   Keyboard.cc					\
				   MergeTChain.cc               \
				   MiscTools.cc				    \
				   PrintFakeRateTable.cc        \
				   TDRStyle.cc					\
				   TH1Container.cc				\
				   TH1Overlay.cc				\
				   is_equal.cc					\
				   is_zero.cc					
include_dir     := include source 
defines         := __RTINT__

# for ROOT interactive use (rootcint)
headers         := rt/MiscTools.h               \
              	   rt/TH1Container.h            \
              	   rt/TH1Overlay.h			    \
              	   rt/PrintFakeRateTable.h      \
              	   rt/DrawAllBranches.h         \
              	   rt/MergeTChain.h             \
              	   rt/CompareContentsOfTTrees.h \
              	   rt/is_equal.h                \
              	   rt/TDRStyle.h			    \
              	   rt/is_zero.h				    
link_def	    := LinkDef.h

# additional libraries
# ----------------------------------------------------------------------- #

# BOOST libraries
$(eval $(include_boost_libs))

# package setup
# ----------------------------------------------------------------------- #

package_dir := $(project_dir)/$(package_dir_rel)

include_dir := $(addprefix $(strip $(package_dir))/,$(include_dir))

sources     := $(call add-path,$(package_dir)/source,$(sources))
source_dir  := $(sort $(dir $(sources)))

object_dir  := $(call add-path,$(project_obj),$(package_dir_rel))
objects     := $(call source-to-object,$(sources),$(object_dir))  

dep_dir     := $(call add-path,$(project_obj),$(package_dir_rel))
deps        := $(call source-to-dep,$(sources),$(dep_dir))  

libraries   := $(call add-path,$(project_lib),$(libraries))
rootdict    := $(call lib-to-rootdict,$(libraries),$(object_dir)) 
sources     += $(rootdict)

vpath %.h $(include_dir)
vpath %.cc $(source_dir)
vpath %.o   $(object_dir)
vpath %.d   $(dep_dir)

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
	@echo add-path test = $(call add-path,$(object_dir),%.o)
	@echo lib-to-rootdict = $(rootdict)
	@echo dict path = $(call add-path,$(dir $(rootdict)),%.cc) 
	@echo lib = $(call add-path,$(project_lib),%.so) 
	@echo objs = $(call add-path,$(object_dir),%.o) 
	@echo dict = $(subst .cc,.o,$(rootdict))

.PHONY: deps 
deps: $(dep)

.PHONY: libraries
libraries: $(libraries)

.PHONY: all
all: $(deps) $(rootdict) $(libraries)

.PHONY: clean
clean:
	$(RM) $(objects) $(libraries) $(deps) $(extra_clean) 
	$(RMDIR) $(dep_dir) $(object_dir)

# system rules
# ----------------------------------------------------------------------- #

# keep object files
.PRECIOUS: $(call add-path,$(object_dir),%.o)

# create the dict.cc
$(rootdict): $(headers)
	$(call root-cint,$(rootdict),$(headers),$(include_dir),$(link_def),$(defines))

# create dict.o
$(subst .cc,.o,$(rootdict)): $(rootdict)
	$(COMPILE.cc) $(addprefix -D,$(defines)) $(OUTPUT_OPTION) $<

# compile all the objects
$(call add-path,$(object_dir),%.o): $(call add-path,$(source_dir),%.cc)
	@mkdir -p $(object_dir)
	$(COMPILE.cc) $(addprefix -D,$(defines)) $(OUTPUT_OPTION) $<

# link all the objects 
$(call add-path,$(project_lib),%.so): $(objects) $(subst .cc,.o,$(rootdict))
	@mkdir -p $(project_lib)
	$(SHAREDLIB.cc) $@ $^

# autmatically resolve dependencies
# ----------------------------------------------------------------------- #

ifneq "$(MAKECMDGOALS)" "clean"
  -include $(deps)
endif

$(call add-path,$(dep_dir),%.d): $(call add-path,$(source_dir),%.cc)
	@mkdir -p $(dep_dir)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -M $< | \
	$(SED) 's,\($(notdir $*)\.o\) *:,$(dir $@)\1 $@: ,' > $@.tmp 
	@$(MV) $@.tmp $@
