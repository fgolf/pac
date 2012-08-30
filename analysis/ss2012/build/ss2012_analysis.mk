# ----------------------------------------------------------------------- #
# Makefile for RootTools library
# creates an interative shared lib to use with ROOT or stand alone c++ code
# ----------------------------------------------------------------------- #

include ${PAC}/tools/Makefile.common

# specifiy the sources here
# ----------------------------------------------------------------------- #

# source files
programs        := ss2012_analysis.exe
program_dir_rel := analysis/ss2012
sources         := ss2012_analysis.cc \
    			    AnalysisLooper.cc \
    			    SameSignTree.cc \
    			    ScaleFactors.cc 
include_dir     := include
defines         := __NON_ROOT_BUILD__

# additional libraries
# ----------------------------------------------------------------------- #

# BOOST c++ libraries 
$(eval $(include_boost_libs))

# RootTools 
$(eval $(include_root_tools))

# AnalysisTools
$(eval $(include_analysis_tools))

# MiniFWLite 
$(eval $(include_mini_fwlite))

# SimpleTable 
$(eval $(include_simple_table))

# Frank's tools
$(eval $(include_fg_tools))

# CMS2 
$(eval $(include_cms2_header))
$(eval $(include_cms2_core))

# program setup
# ----------------------------------------------------------------------- #

program_dir := $(project_dir)/$(program_dir_rel)

include_dir := $(addprefix $(strip $(program_dir))/,$(include_dir))

source_dir  := $(program_dir)/source
sources     := $(call add-path,$(source_dir),$(sources))

object_dir  := $(call add-path,$(project_obj),$(program_dir_rel))
objects     := $(call source-to-object,$(sources),$(object_dir))  

dep_dir     := $(call add-path,$(project_obj),$(program_dir_rel))
deps        := $(call source-to-dep,$(sources),$(dep_dir))  

programs    := $(call add-path,$(project_bin),$(programs))
sources     += $(rootdict)

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
	@echo program_dir = $(program_dir)
	@echo program_dir_rel = $(program_dir_rel)
	@echo sources = $(sources)
	@echo source_dir = $(source_dir)
	@echo include_dir = $(include_dir)
	@echo objects = $(objects)
	@echo object_dir = $(object_dir)
	@echo deps = $(deps)
	@echo dep_dir = $(dep_dir)
	@echo programs = $(programs)
	@echo add-path test = $(call add-path,$(object_dir),%.o)
	@echo dict path = $(call add-path,$(dir $(rootdict)),%.cc) 
	@echo bin = $(call add-path,$(project_bin),%.so) 
	@echo objs = $(call add-path,$(object_dir),%.o) 
	@echo src = $(call add-path,$(source_dir),%.cc)
	@echo dep = $(call add-path,$(dep_dir),%.d)

.PHONY: deps 
deps: $(deps)

.PHONY: programs
programs: $(programs)

.PHONY: all
all: $(deps) $(programs)

# specific rule
$(programs) : $(objects)
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: clean
clean:
	$(RM) $(objects) $(programs) $(deps) $(extra_clean) 
	$(RMDIR) $(dep_dir) $(object_dir)

# system rules
# ----------------------------------------------------------------------- #

# keep object files
.PRECIOUS: $(call add-path,$(object_dir),%.o)

# compile all the objects
$(call add-path,$(object_dir),%.o): $(call add-path,$(source_dir),%.cc)
	@mkdir -p $(object_dir)
	$(COMPILE.cc) $(addprefix -D,$(defines)) $(OUTPUT_OPTION) $<

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
