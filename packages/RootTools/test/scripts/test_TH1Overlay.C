{
    // create some hists to play with
    rt::TH1Container h("$PAC/packages/root_tools/test/data/hsimple.root");
    h.Add(dynamic_cast<TH1*>(h["hpx"]->Clone("hpx2" )));
    h.Add(dynamic_cast<TH1*>(h["hpx"]->Clone("hpx3" )));
    h.Add(dynamic_cast<TH1*>(h["hpx"]->Clone("hpx4" )));
    h.Add(dynamic_cast<TH1*>(h["hpx"]->Clone("hpx5" )));
    h.Add(dynamic_cast<TH1*>(h["hpx"]->Clone("hpx6" )));
    h.Add(dynamic_cast<TH1*>(h["hpx"]->Clone("hpx7" )));
    h.Add(dynamic_cast<TH1*>(h["hpx"]->Clone("hpx8" )));
    h.Add(dynamic_cast<TH1*>(h["hpx"]->Clone("hpx9" )));
    h.Add(dynamic_cast<TH1*>(h["hpx"]->Clone("hpx10")));
    h["hpx2" ]->Scale(0.9);
    h["hpx3" ]->Scale(0.8);
    h["hpx4" ]->Scale(0.7);
    h["hpx5" ]->Scale(0.6);
    h["hpx6" ]->Scale(0.5);
    h["hpx7" ]->Scale(0.4);
    h["hpx8" ]->Scale(0.3);
    h["hpx9" ]->Scale(0.2);
    h["hpx10"]->Scale(0.1);
    h.List();

    // a plot with a lot of 
    c1 = new TCanvas("c1");
    rt::TH1Overlay p1;
    p1.Add(h["hpx"], "legend");
    p1.Add(h["hpx2" ], "legend2 ");
    p1.Add(h["hpx3" ], "legend3 ");
    p1.Add(h["hpx4" ], "legend4 ");
    p1.Add(h["hpx5" ], "legend5 ");
    p1.Add(h["hpx6" ], "legend6 ");
    p1.Add(h["hpx7" ], "legend7 ");
    p1.Add(h["hpx8" ], "legend8 ");
    p1.Add(h["hpx9" ], "legend9 ");
    p1.Add(h["hpx10"], "legend10");
    p1.List();
    p1.Draw();

    c2 = new TCanvas("c2");
    rt::TH1Overlay p2("p_{x} distribution; p_{x} [GeV/c]; events");
    p2.Add(h["hpx"], "legend", kBlack);
    p2.Add(h["hpx2"], "legend2", kBlue);
    p2.Add(h["hpx3"], "legend3");
    p2.Add(h["hpx4"], "legend4");
    p2.Draw();

    c3 = new TCanvas("c3");
    //rt::TH1Overlay p3(p2);
    rt::TH1Overlay p3 = p2;
    p3.Remove(h["hpx2"]);
    p3.Remove("hpx3");
    p3.SetLegendPlacement(rt::LegendPlacement::bottom_right);
    p3.SetStatBoxPlacement(rt::StatBoxPlacement::top_middle_right);
    p3.Draw();
}
