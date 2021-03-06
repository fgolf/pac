#include "makeChain.h"

#include <stdio.h>
#include <string>

TChain *makeChain (const char *glob, const char *treename, TChain *chain_in, bool verbose)
{
    std::string cmd = "ls ";
    cmd += glob;
    FILE *f = popen(cmd.c_str(), "r");
    if (!f) {
        perror("Opening pipe");
        return 0;
    }
    TChain *c = chain_in == 0 ? new TChain(treename) : chain_in;
    int s;
    do {
        char fname[1024];
        s = fscanf(f, " %1024s\n", fname);
        if (s != 1) {
            if (s != EOF)
                perror("scanning file list");
        } else {
            if (verbose)
                printf("Adding %s\n", fname);
            c->Add(fname);
        }
    } while (s == 1);
    if (pclose(f) == -1) 
        perror("Closing pipe");
    return c;
}

TChain *makeChain_command (const char *cmd, const char *treename, bool verbose)
{
    FILE *f = popen(cmd, "r");
    if (!f) {
        perror("Opening pipe");
        return 0;
    }
    TChain *c = new TChain(treename);
    int s;
    do {
        char fname[1024];
        s = fscanf(f, " %1024s\n", fname);
        if (s != 1) {
            if (s != EOF)
                perror("scanning file list");
        } else {
            if (verbose)
                printf("Adding %s\n", fname);
            c->Add(fname);
        }
    } while (s == 1);
    if (pclose(f) == -1) 
        perror("Closing pipe");
    return c;
}

