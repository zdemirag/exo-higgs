//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Thu Sep 25 12:07:45 2014 by ROOT version 5.32/00)
//      from the StreamerInfo in file total_nuTuple.root
//////////////////////////////////////////////////////////


#ifndef TCGenParticle_h
#define TCGenParticle_h
class TCGenParticle;

#include "TCPhysObject.h"
#include "TCGenParticle.h"

class TCGenParticle : public TCPhysObject {

public:
// Nested classes declaration.

public:
// Data Members.
   TCGenParticle* _mother;     //
   int            _PDGID;      //
   unsigned int   _status;     //
   bool           _isParton;    //

   TCGenParticle();
   TCGenParticle(const TCGenParticle & );
   virtual ~TCGenParticle();

   ClassDef(TCGenParticle,2); // Generated by MakeProject.
};
#endif