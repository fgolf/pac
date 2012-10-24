# ----------------------------------------------------------------------- #
# Makefile for ss2012 
# creates an shared lib and executables
# ----------------------------------------------------------------------- #

all:
	$(MAKE) -f build/ttv2012_tools.mk
	$(MAKE) -f build/trilepz2012_analysis.mk

clean:
	$(MAKE) -f build/ttv2012_tools.mk clean
	$(MAKE) -f build/trilepz2012_analysis.mk clean

.PHONY: all clean
