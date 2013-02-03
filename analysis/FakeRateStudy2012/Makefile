# ----------------------------------------------------------------------- #
# Makefile for ss2012 
# creates an shared lib and executables
# ----------------------------------------------------------------------- #

all:
	$(MAKE) -f build/fr2012_plots.mk
	$(MAKE) -f build/fr2012_trig_study.mk

clean:
	$(MAKE) -f build/fr2012_plots.mk clean
	$(MAKE) -f build/fr2012_trig_study.mk clean

.PHONY: all clean
