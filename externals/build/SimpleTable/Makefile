include ${PAC}/tools/Makefile.common

target        := $(call add-path,$(project_lib),libSimpleTable.so)
external_path := $(call add-path,$(project_dir),externals/source/SimpleTable)
lib           := $(call add-path,$(external_path),$(notdir $(target)))

all: $(target)

$(target): $(lib)
	$(CP) $(call add-path,$(external_path),$(notdir $(target))) $(target)

$(lib):
	$(MAKE) -C $(external_path)

clean: 
	$(MAKE) -C $(external_path) clean

.PHONY: all clean
