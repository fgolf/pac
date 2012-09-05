# ----------------------------------------------------------------------- #
# Makefile for ss2012 
# creates an shared lib and executables
# ----------------------------------------------------------------------- #

all:
	$(MAKE) -f build/ss2012_tools.mk
	$(MAKE) -f build/ss2012_analysis.mk
	$(MAKE) -f build/ss2012_create_fakerate.mk
	$(MAKE) -f build/ss2012_merge_babies.mk
	$(MAKE) -f build/ss2012_plots.mk
	$(MAKE) -f build/ss2012_quick_check.mk
#	$(MAKE) -f build/ss2012_bkgd_pred.mk

clean:
	$(MAKE) -f build/ss2012_tools.mk clean
	$(MAKE) -f build/ss2012_analysis.mk clean
	$(MAKE) -f build/ss2012_create_fakerate.mk clean
	$(MAKE) -f build/ss2012_plots.mk clean
	$(MAKE) -f build/ss2012_merge_babies.mk clean
	$(MAKE) -f build/ss2012_quick_check.mk clean
#	$(MAKE) -f build/ss2012_bkgd_pred.mk clean

.PHONY: all clean
