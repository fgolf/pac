#ifndef AT_TRACKISOTOOLS_H
#define AT_TRACKISOTOOLS_H

namespace at
{
    struct myTrackIso {

        //defaultValue 
        float iso_dr03_dz005_pt00;

        // iso sum options
        float isoDir_dr03_dz005_pt00;

        // r04 cone option
        float iso_dr04_dz005_pt00;

        // veto cone
        float iso_dr01503_dz005_pt00;
        float iso_dr0503_dz005_pt00;

        // dz variation
        float iso_dr03_dz000_pt00;
        float iso_dr03_dz010_pt00;
        float iso_dr03_dz020_pt00;

        //pt Variation
        float iso_dr03_dz005_pt01;
        float iso_dr03_dz005_pt02;
        float iso_dr03_dz005_pt03;
        float iso_dr03_dz005_pt04;
        float iso_dr03_dz005_pt05;
        float iso_dr03_dz005_pt06;
        float iso_dr03_dz005_pt07;
        float iso_dr03_dz005_pt08;
        float iso_dr03_dz005_pt09;
        float iso_dr03_dz005_pt10;
    };

    struct myTrackIso trackIso( int thisPf , float coneR , float dz_thresh , bool dovtxcut , float pt_thresh );
    struct myTrackIso trackIso( int thisPf , float coneR = 0.3 , float dz_thresh = 0.05 , bool dovtxcut = false, float pt_thresh = 0.0); 
} // namespace at

#endif // AT_TRACKISOTOOLS_H
