//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov 19 21:31:37 2015 by ROOT version 6.04/02
// from TTree Tracks/Tracks
// found on file: ResultsTrees.root
//////////////////////////////////////////////////////////

#ifndef TreeTracks_h
#define TreeTracks_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class TreeTracks {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         x0;
   Float_t         y0;
   Float_t         t0;
   Float_t         tan;
   Float_t         off;

   // List of branches
   TBranch        *b_x0;   //!
   TBranch        *b_y0;   //!
   TBranch        *b_t0;   //!
   TBranch        *b_tan;   //!
   TBranch        *b_off;   //!

   TreeTracks(TTree *tree=0);
   virtual ~TreeTracks();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif


