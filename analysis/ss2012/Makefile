# ----------------------------------------------------------------------- #
# Makefile for ss2012 
# creates an shared lib and executables
# ----------------------------------------------------------------------- #

all:
	$(MAKE) -f build/ss2012_analysis.mk
	$(MAKE) -f build/ss2012_create_fakerate.mk
	$(MAKE) -f build/ss2012_plots.mk

clean:
	$(MAKE) -f build/ss2012_analysis.mk clean
	$(MAKE) -f build/ss2012_create_fakerate.mk clean
	$(MAKE) -f build/ss2012_plots.mk clean

.PHONY: all clean
