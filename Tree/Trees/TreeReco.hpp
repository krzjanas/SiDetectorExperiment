//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov 19 21:32:40 2015 by ROOT version 6.04/02
// from TTree Reco/Reco
// found on file: ResultsTrees.root
//////////////////////////////////////////////////////////

#ifndef TreeReco_h
#define TreeReco_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class TreeReco {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Bool_t          reco;
   Int_t           nPoints;
   Float_t         slope;
   Float_t         offset;
   Float_t         theta;
   Float_t         slopeErr;
   Float_t         offsetErr;
   Float_t         thetaErr;
   Float_t         chi;

   // List of branches
   TBranch        *b_reco;   //!
   TBranch        *b_nPoints;   //!
   TBranch        *b_slope;   //!
   TBranch        *b_offset;   //!
   TBranch        *b_theta;   //!
   TBranch        *b_slopeErr;   //!
   TBranch        *b_offsetErr;   //!
   TBranch        *b_thetaErr;   //!
   TBranch        *b_chi;   //!

   TreeReco(TTree *tree=0);
   virtual ~TreeReco();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

