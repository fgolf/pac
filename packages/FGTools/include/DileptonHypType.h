// -*- C++ -*-
#ifndef DILEPTONHYPTYPE_H
#define DILEPTONHYPTYPE_H

enum HypType {
    DILEPTON_SS,
    DILEPTON_OS,
    DILEPTON_ANY
};

enum DileptonHypType {
     DILEPTON_ALL,
     DILEPTON_MUMU,
     DILEPTON_EMU,
     DILEPTON_EE
};

static const char dilepton_hypo_names[][128] = { "all", "mm", "em", "ee" };

enum DileptonHypType hyp_typeToHypType (int hyp_type);

#endif
