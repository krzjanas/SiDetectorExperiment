//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov 19 21:32:57 2015 by ROOT version 6.04/02
// from TTree Sensor/Sensor
// found on file: ResultsTrees.root
//////////////////////////////////////////////////////////

#ifndef TreeSensor_h
#define TreeSensor_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class TreeSensor {
public :
   TChain          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         real;
   Float_t         blurry;
   Bool_t          observed;
   Float_t         measured;
   Bool_t          isReco;
   Float_t         recoVal;

   // List of branches
   TBranch        *b_real;   //!
   TBranch        *b_blurry;   //!
   TBranch        *b_observed;   //!
   TBranch        *b_measured;   //!
   TBranch        *b_isReco;   //!
   TBranch        *b_recoVal;   //!

   TreeSensor(TString const & fileName = "", TString const & treeName = "");
   virtual ~TreeSensor();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init();
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif
