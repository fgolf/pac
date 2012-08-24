#ifndef HISTIO_H
#define HISTIO_H

void saveHist(const char* filename, const char* pat="*");
void loadHist(const char* filename, const char* pfx=0, const char* pat="*", Bool_t doAdd=kFALSE);

#endif
