//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Thu Sep 25 12:07:45 2014 by ROOT version 5.32/00)
//      from the StreamerInfo in file total_nuTuple.root
//////////////////////////////////////////////////////////


#ifndef TCJet_h
#define TCJet_h
class TCJet;

#include "TCPhysObject.h"

class TCJet : public TCPhysObject {

public:
// Nested classes declaration.

public:
// Data Members.
   int         _id_cut_loose;    //
   int         _id_cut_medium;    //
   int         _id_cut_tight;     //
   int         _id_mva_loose;     //
   int         _id_mva_medium;    //
   int         _id_mva_tight;     //

   TCJet();
   TCJet(const TCJet & );
   virtual ~TCJet();

   ClassDef(TCJet,2); // Generated by MakeProject.
};
#endif
