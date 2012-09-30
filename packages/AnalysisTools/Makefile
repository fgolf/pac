# ----------------------------------------------------------------------- #
# Makefile for AnalysisTools
# creates an shared lib
# ----------------------------------------------------------------------- #

include ${PAC}/tools/Makefile.common

# specifiy the sources here
# ----------------------------------------------------------------------- #

# source files
libraries       := libAnalysisTools.so
package_dir_rel := packages/AnalysisTools
sources         := AnalysisBase.cc         \
				   AnalysisWithHist.cc     \
				   AnalysisWithTree.cc     \
				   Constants.cc            \
				   DorkyEventIdentifier.cc \
				   DileptonHypType.cc      \
				   DileptonChargeType.cc   \
				   VtxReweight.cc          \
				   GoodRun.cc              \
				   Sample.cc               \
				   LorentzVectorObject.cc  \
				   CMS2Wrapper.cc 		   \
				   ScanChain.cc 		   \
				   SkimChain.cc 		   \
				   EventInfoTree.cc        \
				   SingleLeptonTree.cc     \
				   PrintIdIsoInfo.cc       \
				   DileptonTree.cc	
include_dir     := include source 

# additional libraries
# ----------------------------------------------------------------------- #

# BOOST libraries
$(eval $(include_boost_libs))

# RootTools
$(eval $(include_root_tools))

# CMS2
$(eval $(include_cms2_header))
$(eval $(include_cms2_core))

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
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $(addprefix -D,$(defines)) -M $< | \
	$(SED) 's,\($(notdir $*)\.o\) *:,$(dir $@)\1 $@: ,' > $@.tmp 
	@$(MV) $@.tmp $@
