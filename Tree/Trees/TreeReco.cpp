#include "TreeReco.hpp"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

TreeReco::TreeReco(TString const & fileName, TString const & treeName) : fChain(0) 
{
   if( fileName == "" ) return;

   fChain = new TChain(treeName);
   fChain->Add(fileName);

   Init();
}

TreeReco::~TreeReco()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TreeReco::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TreeReco::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TreeReco::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers

   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("reco", &reco, &b_reco);
   fChain->SetBranchAddress("nPoints", &nPoints, &b_nPoints);
   fChain->SetBranchAddress("slope", &slope, &b_slope);
   fChain->SetBranchAddress("offset", &offset, &b_offset);
   fChain->SetBranchAddress("theta", &theta, &b_theta);
   fChain->SetBranchAddress("slopeErr", &slopeErr, &b_slopeErr);
   fChain->SetBranchAddress("offsetErr", &offsetErr, &b_offsetErr);
   fChain->SetBranchAddress("thetaErr", &thetaErr, &b_thetaErr);
   fChain->SetBranchAddress("chi", &chi, &b_chi);
   Notify();
}

Bool_t TreeReco::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TreeReco::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TreeReco::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

void TreeReco::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Reco.C
//      root> Reco t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}
