# ----------------------------------------------------------------------- #
# Makefile for ss2012 
# creates an shared lib and executables
# ----------------------------------------------------------------------- #

all:
	$(MAKE) -f build/ss2012_tools.mk
	$(MAKE) -f build/ss2012_analysis.mk
	$(MAKE) -f build/ss2012_create_fakerate.mk
	$(MAKE) -f build/ss2012_merge_babies.mk
	$(MAKE) -f build/ss2012_skim.mk
	$(MAKE) -f build/ss2012_plots.mk
	$(MAKE) -f build/ss2012_quick_check.mk
	$(MAKE) -f build/ss2012_outreach.mk
	$(MAKE) -f build/ss2012_outreach_closure.mk
	$(MAKE) -f build/ss2012_closure_test.mk

clean:
	$(MAKE) -f build/ss2012_tools.mk clean
	$(MAKE) -f build/ss2012_analysis.mk clean
	$(MAKE) -f build/ss2012_create_fakerate.mk clean
	$(MAKE) -f build/ss2012_skim.mk clean
	$(MAKE) -f build/ss2012_plots.mk clean
	$(MAKE) -f build/ss2012_merge_babies.mk clean
	$(MAKE) -f build/ss2012_quick_check.mk clean
	$(MAKE) -f build/ss2012_outreach.mk clean
	$(MAKE) -f build/ss2012_outreach_closure.mk clean
	$(MAKE) -f build/ss2012_closure_test.mk clean

.PHONY: all clean
