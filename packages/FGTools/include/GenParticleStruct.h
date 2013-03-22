#ifndef GENPARTICLESTRUCT_H
#define GENPARTICLESTRUCT_H

struct GenParticleStruct {
    GenParticleStruct (int id, unsigned int idx, float pt, float eta, int did, unsigned int didx, float dpt, float deta);
    GenParticleStruct () : id_(0), idx_(999999), pt_(-1.), eta_(-999999.), did_(0), didx_(999999), dpt_(-1.), deta_(-999999.) {};
    int id_;
    unsigned int idx_;
    float pt_;
    float eta_;
    int did_;
    unsigned int didx_;
    float dpt_;
    float deta_;
    int rid_;
    unsigned int ridx_;    

    // sort by pt
    static bool SortByPt(const GenParticleStruct& lhs, const GenParticleStruct& rhs) {return rhs.pt_ > lhs.pt_;}
};

#endif
