# ----------------------------------------------------------------------- #
# Makefile for RootTools library
# creates an interative shared lib to use with ROOT or stand alone c++ code
# ----------------------------------------------------------------------- #

include ${PAC}/tools/Makefile.common

# specifiy the sources here
# ----------------------------------------------------------------------- #

# source files
libraries       := libss2012_tools.so
package_dir_rel := analysis/ss2012
sources         := SSB2012.cc      		 \
				   SSB2012Wrapper.cc	 \
				   ScaleFactors.cc 		 \
				   SameSignTree.cc 		 \
				   PredSummary.cc   	 \
				   FakeRatePrediction.cc \
				   FlipRatePrediction.cc \
				   SignalRegion.cc 
include_dir     := include source 
defines         := 

# for ROOT interactive use (rootcint)
headers         := SignalRegion.h 
link_def	    := LinkDef.h

# additional libraries
# ----------------------------------------------------------------------- #

# BOOST libraries
$(eval $(include_boost_libs))

# BOOST c++ libraries 
$(eval $(include_boost_libs))

# RootTools 
$(eval $(include_root_tools))

# AnalysisTools
$(eval $(include_analysis_tools))

# MiniFWLite 
$(eval $(include_mini_fwlite))

# SimpleTable 
#$(eval $(include_simple_table))

# Frank's tools
#$(eval $(include_fg_tools))

# CMS2 
$(eval $(include_cms2_header))
$(eval $(include_cms2_core))
# package setup
# ----------------------------------------------------------------------- #

package_dir := $(project_dir)/$(package_dir_rel)

include_dir := $(addprefix $(strip $(package_dir))/,$(include_dir))

source_dir  := $(package_dir)/source
sources     := $(call add-path,$(source_dir),$(sources))

object_dir  := $(call add-path,$(project_obj),$(package_dir_rel))
objects     := $(call source-to-object,$(sources),$(object_dir))  

dep_dir     := $(call add-path,$(project_obj),$(package_dir_rel))
deps        := $(call source-to-dep,$(sources),$(dep_dir))  

libraries   := $(call add-path,$(project_lib),$(libraries))
rootdict    := $(call lib-to-rootdict,$(libraries),$(object_dir)) 
sources     += $(rootdict)

vpath %.h $(include_dir)
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
	@echo dep dep = $(call add-path,$(source_dir),%.cc)
	@echo dep targ = $(call add-path,$(dep_dir),%.d)

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
