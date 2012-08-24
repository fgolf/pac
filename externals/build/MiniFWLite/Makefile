include ../../../tools/Makefile.common

target        := $(call add-path,$(project_lib),libMiniFWLite.so)
external_path := $(call add-path,$(project_dir),externals/source/MiniFWLite)
lib           := $(call add-path,$(external_path),$(notdir $(target)))

all: $(target)

$(target): $(lib)
	$(MKDIR) $(dir $(target))
	$(CP) $(call add-path,$(external_path),$(notdir $(target))) $(target)

$(lib):
	$(MAKE) -C $(external_path)

clean: 
	$(MAKE) -C $(external_path) clean

.PHONY: all clean
