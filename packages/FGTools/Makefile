# ----------------------------------------------------------------------- #
# Makefile for RootTools library
# creates an interative shared lib to use with ROOT or stand alone c++ code
# ----------------------------------------------------------------------- #

include ../../tools/Makefile.common

# specifiy the sources here
# ----------------------------------------------------------------------- #

# source files
libraries       := libFGTools.so
package_dir_rel := packages/FGTools
sources         := BabyDorkIdentifier.cc \
					EfficiencyModelTools.cc \
					FakeRateType.cc \
					GenParticleStruct.cc \
					browseStacks.cc \
					eff.cc \
					eff2.cc \
					fliprate_egun.cc \
					getMyHistosNames.cc \
					goodrun.cc \
					histtools.cc \
					makeChain.cc \
					makeProjectionPlots.cc \
					printFRtable.cc \
					tdrStyle.cc \
					tools.cc \
					histio.cc \
					vtxreweight.cc
					#DileptonHypType.cc \
					#ScaleFactors.cc # temporarilty removed until i found the right place for this 
include_dir      := include


# additional libraries
# ----------------------------------------------------------------------- #

# CMS2
$(eval $(include_cms2_header))
$(eval $(include_cms2_core))

# Analysis Tools
$(eval $(include_analysis_tools))

# package setup
# ----------------------------------------------------------------------- #

package_dir := $(project_dir)/$(package_dir_rel)

sources     := $(call add-path,$(package_dir)/source,$(sources))
source_dir  := $(sort $(dir $(sources)))

include_dir := $(addprefix $(strip $(package_dir))/,$(include_dir))

object_dir  := $(call add-path,$(project_obj),$(package_dir_rel))
objects     := $(call source-to-object,$(sources),$(object_dir))  

dep_dir     := $(call add-path,$(project_obj),$(package_dir_rel))
deps        := $(call source-to-dep,$(sources),$(dep_dir))  

libraries   := $(call add-path,$(project_lib),$(libraries))

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
	@echo lib = $(call add-path,$(project_lib),%.so) 
	@echo objs = $(call add-path,$(object_dir),%.o) 

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

# link all the objects 
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
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -M $< | \
	$(SED) 's,\($(notdir $*)\.o\) *:,$(dir $@)\1 $@: ,' > $@.tmp 
	@$(MV) $@.tmp $@
