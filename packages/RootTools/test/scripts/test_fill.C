{
    new TCanvas("c1", "c1");
    TH1* h1 = new TH1D("h1", "h1", 100, 0, 100);
    for (size_t i = 0; i < 100; i++) 
    { 
        rt::Fill(h1, i); 
        rt::Fill(h1, -5); 
        rt::Fill(h1, 1000); 
    }
    h1->Draw();

    new TCanvas("c2", "c2");
    TH1* h2 = new TH1D("h2", "h2", 100, 0, 100);
    for (size_t i = 0; i < 100; i++) 
    { 
        h2->Fill(i); 
        h2->Fill(-5); 
        h2->Fill(1000); 
    }
    h2->Draw();
}

