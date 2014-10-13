#include "testProjectHeaders.h"

#include "testLinkDef.h"

#include "testProjectDict.cxx"

struct DeleteObjectFunctor {
   template <typename T>
   void operator()(const T *ptr) const {
      delete ptr;
   }
   template <typename T, typename Q>
   void operator()(const std::pair<T,Q> &) const {
      // Do nothing
   }
   template <typename T, typename Q>
   void operator()(const std::pair<T,Q*> &ptr) const {
      delete ptr.second;
   }
   template <typename T, typename Q>
   void operator()(const std::pair<T*,Q> &ptr) const {
      delete ptr.first;
   }
   template <typename T, typename Q>
   void operator()(const std::pair<T*,Q*> &ptr) const {
      delete ptr.first;
      delete ptr.second;
   }
};

#ifndef TCMET_cxx
#define TCMET_cxx
TCMET::TCMET() {
}
TCMET::TCMET(const TCMET & rhs)
   : TVector2(const_cast<TCMET &>( rhs ))
   , _genMET(const_cast<TCMET &>( rhs )._genMET)
   , _sumEt(const_cast<TCMET &>( rhs )._sumEt)
   , _muonFraction(const_cast<TCMET &>( rhs )._muonFraction)
   , _neutralHadronFraction(const_cast<TCMET &>( rhs )._neutralHadronFraction)
   , _neutralEMFraction(const_cast<TCMET &>( rhs )._neutralEMFraction)
   , _chargedHadronFraction(const_cast<TCMET &>( rhs )._chargedHadronFraction)
   , _chargedEMFraction(const_cast<TCMET &>( rhs )._chargedEMFraction)
   , _unCorPhi(const_cast<TCMET &>( rhs )._unCorPhi)
   , _Significance(const_cast<TCMET &>( rhs )._Significance)
   , _SigmaX2(const_cast<TCMET &>( rhs )._SigmaX2)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
TCMET::~TCMET() {
}
#endif // TCMET_cxx

#ifndef TCJet_cxx
#define TCJet_cxx
TCJet::TCJet() {
}
TCJet::TCJet(const TCJet & rhs)
   : TCPhysObject(const_cast<TCJet &>( rhs ))
   , _id_cut_loose(const_cast<TCJet &>( rhs )._id_cut_loose)
   , _id_cut_medium(const_cast<TCJet &>( rhs )._id_cut_medium)
   , _id_cut_tight(const_cast<TCJet &>( rhs )._id_cut_tight)
   , _id_mva_loose(const_cast<TCJet &>( rhs )._id_mva_loose)
   , _id_mva_medium(const_cast<TCJet &>( rhs )._id_mva_medium)
   , _id_mva_tight(const_cast<TCJet &>( rhs )._id_mva_tight)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
TCJet::~TCJet() {
}
#endif // TCJet_cxx

#ifndef TCPhysObject_cxx
#define TCPhysObject_cxx
TCPhysObject::TCPhysObject() {
}
TCPhysObject::TCPhysObject(const TCPhysObject & rhs)
   : TLorentzVector(const_cast<TCPhysObject &>( rhs ))
   , _vtx(const_cast<TCPhysObject &>( rhs )._vtx)
   , _IdMap(const_cast<TCPhysObject &>( rhs )._IdMap)
   , _IsoMap(const_cast<TCPhysObject &>( rhs )._IsoMap)
   , _charge(const_cast<TCPhysObject &>( rhs )._charge)
   , _type(const_cast<TCPhysObject &>( rhs )._type)
   , _isPF(const_cast<TCPhysObject &>( rhs )._isPF)
   , _isReco(const_cast<TCPhysObject &>( rhs )._isReco)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TCPhysObject &modrhs = const_cast<TCPhysObject &>( rhs );
   modrhs._IdMap.clear();
   modrhs._IsoMap.clear();
   modrhs._type.clear();
}
TCPhysObject::~TCPhysObject() {
}
#endif // TCPhysObject_cxx

#ifndef TCElectron__HitInfo_cxx
#define TCElectron__HitInfo_cxx
TCElectron::HitInfo::HitInfo() {
}
TCElectron::HitInfo::HitInfo(const HitInfo & rhs)
   : Layer(const_cast<HitInfo &>( rhs ).Layer)
   , ValidFilter(const_cast<HitInfo &>( rhs ).ValidFilter)
   , PixelFilter(const_cast<HitInfo &>( rhs ).PixelFilter)
   , BarrelPixelFilter(const_cast<HitInfo &>( rhs ).BarrelPixelFilter)
   , MuonFilter(const_cast<HitInfo &>( rhs ).MuonFilter)
   , StripFilter(const_cast<HitInfo &>( rhs ).StripFilter)
   , TrackerFilter(const_cast<HitInfo &>( rhs ).TrackerFilter)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
TCElectron::HitInfo::~HitInfo() {
}
#endif // TCElectron__HitInfo_cxx

#ifndef TCElectron_cxx
#define TCElectron_cxx
TCElectron::TCElectron() {
}
TCElectron::TCElectron(const TCElectron & rhs)
   : TCEGamma(const_cast<TCElectron &>( rhs ))
   , _pos(const_cast<TCElectron &>( rhs )._pos)
   , _normChi2gsf(const_cast<TCElectron &>( rhs )._normChi2gsf)
   , _normChi2kf(const_cast<TCElectron &>( rhs )._normChi2kf)
   , _ptError(const_cast<TCElectron &>( rhs )._ptError)
   , _fBrem(const_cast<TCElectron &>( rhs )._fBrem)
   , _inverseEnergyMomentumDiff(const_cast<TCElectron &>( rhs )._inverseEnergyMomentumDiff)
   , _EoP(const_cast<TCElectron &>( rhs )._EoP)
   , _EoPout(const_cast<TCElectron &>( rhs )._EoPout)
   , _ip3d(const_cast<TCElectron &>( rhs )._ip3d)
   , _ip3dSig(const_cast<TCElectron &>( rhs )._ip3dSig)
   , _deltaEtaSeedCluster(const_cast<TCElectron &>( rhs )._deltaEtaSeedCluster)
   , _deltaPhiSeedCluster(const_cast<TCElectron &>( rhs )._deltaPhiSeedCluster)
   , _passConvVeto(const_cast<TCElectron &>( rhs )._passConvVeto)
   , _convMissHits(const_cast<TCElectron &>( rhs )._convMissHits)
   , _trackerLayersWithMeasurement(const_cast<TCElectron &>( rhs )._trackerLayersWithMeasurement)
   , _numberOfValidHits(const_cast<TCElectron &>( rhs )._numberOfValidHits)
   , _numberOfValidPixelHits(const_cast<TCElectron &>( rhs )._numberOfValidPixelHits)
   , _numberOfValidTrackerHits(const_cast<TCElectron &>( rhs )._numberOfValidTrackerHits)
   , _numberOfLostPixelHits(const_cast<TCElectron &>( rhs )._numberOfLostPixelHits)
   , _numberOfLostTrackerHits(const_cast<TCElectron &>( rhs )._numberOfLostTrackerHits)
   , _effArea(const_cast<TCElectron &>( rhs )._effArea)
   , _HitMap(const_cast<TCElectron &>( rhs )._HitMap)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TCElectron &modrhs = const_cast<TCElectron &>( rhs );
   modrhs._HitMap.clear();
}
TCElectron::~TCElectron() {
}
#endif // TCElectron_cxx

#ifndef TCEGamma__CrystalInfo_cxx
#define TCEGamma__CrystalInfo_cxx
TCEGamma::CrystalInfo::CrystalInfo() {
}
TCEGamma::CrystalInfo::CrystalInfo(const CrystalInfo & rhs)
   : rawId(const_cast<CrystalInfo &>( rhs ).rawId)
   , ieta(const_cast<CrystalInfo &>( rhs ).ieta)
   , iphi(const_cast<CrystalInfo &>( rhs ).iphi)
   , energy(const_cast<CrystalInfo &>( rhs ).energy)
   , time(const_cast<CrystalInfo &>( rhs ).time)
   , timeErr(const_cast<CrystalInfo &>( rhs ).timeErr)
   , recoFlag(const_cast<CrystalInfo &>( rhs ).recoFlag)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
TCEGamma::CrystalInfo::~CrystalInfo() {
}
#endif // TCEGamma__CrystalInfo_cxx

#ifndef TCEGamma_cxx
#define TCEGamma_cxx
TCEGamma::TCEGamma() {
}
TCEGamma::TCEGamma(const TCEGamma & rhs)
   : TCPhysObject(const_cast<TCEGamma &>( rhs ))
   , _isEB(const_cast<TCEGamma &>( rhs )._isEB)
   , _isEE(const_cast<TCEGamma &>( rhs )._isEE)
   , _isInGap(const_cast<TCEGamma &>( rhs )._isInGap)
   , _hadOverEm(const_cast<TCEGamma &>( rhs )._hadOverEm)
   , _r9(const_cast<TCEGamma &>( rhs )._r9)
   , _scEta(const_cast<TCEGamma &>( rhs )._scEta)
   , _scPhi(const_cast<TCEGamma &>( rhs )._scPhi)
   , _scDeltaPhi(const_cast<TCEGamma &>( rhs )._scDeltaPhi)
   , _scDeltaEta(const_cast<TCEGamma &>( rhs )._scDeltaEta)
   , _scSigmaIetaIeta(const_cast<TCEGamma &>( rhs )._scSigmaIetaIeta)
   , _scSigmaIetaIphi(const_cast<TCEGamma &>( rhs )._scSigmaIetaIphi)
   , _scSigmaIphiIphi(const_cast<TCEGamma &>( rhs )._scSigmaIphiIphi)
   , _scEtaWidth(const_cast<TCEGamma &>( rhs )._scEtaWidth)
   , _scPhiWidth(const_cast<TCEGamma &>( rhs )._scPhiWidth)
   , _scRawEnergy(const_cast<TCEGamma &>( rhs )._scRawEnergy)
   , _scEnergy(const_cast<TCEGamma &>( rhs )._scEnergy)
   , _scPSEnergy(const_cast<TCEGamma &>( rhs )._scPSEnergy)
   , _preShowerOverRaw(const_cast<TCEGamma &>( rhs )._preShowerOverRaw)
   , _e1x3(const_cast<TCEGamma &>( rhs )._e1x3)
   , _e1x5(const_cast<TCEGamma &>( rhs )._e1x5)
   , _e2x2(const_cast<TCEGamma &>( rhs )._e2x2)
   , _e2x5(const_cast<TCEGamma &>( rhs )._e2x5)
   , _e2x5Max(const_cast<TCEGamma &>( rhs )._e2x5Max)
   , _e5x5(const_cast<TCEGamma &>( rhs )._e5x5)
   , _esEffSigmaRR(const_cast<TCEGamma &>( rhs )._esEffSigmaRR)
   , _pfIsoCharged(const_cast<TCEGamma &>( rhs )._pfIsoCharged)
   , _pfIsoNeutral(const_cast<TCEGamma &>( rhs )._pfIsoNeutral)
   , _pfIsoPhoton(const_cast<TCEGamma &>( rhs )._pfIsoPhoton)
   , _crysVect(const_cast<TCEGamma &>( rhs )._crysVect)
   , _nCrystals(const_cast<TCEGamma &>( rhs )._nCrystals)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TCEGamma &modrhs = const_cast<TCEGamma &>( rhs );
   modrhs._esEffSigmaRR.clear();
   modrhs._crysVect.clear();
}
TCEGamma::~TCEGamma() {
}
#endif // TCEGamma_cxx

#ifndef TCMuon_cxx
#define TCMuon_cxx
TCMuon::TCMuon() {
}
TCMuon::TCMuon(const TCMuon & rhs)
   : TCPhysObject(const_cast<TCMuon &>( rhs ))
   , _ptError(const_cast<TCMuon &>( rhs )._ptError)
   , _isPF(const_cast<TCMuon &>( rhs )._isPF)
   , _isTRK(const_cast<TCMuon &>( rhs )._isTRK)
   , _isGLB(const_cast<TCMuon &>( rhs )._isGLB)
   , _isSoft(const_cast<TCMuon &>( rhs )._isSoft)
   , _isTight(const_cast<TCMuon &>( rhs )._isTight)
   , _isGood(const_cast<TCMuon &>( rhs )._isGood)
   , _isGoodLoose(const_cast<TCMuon &>( rhs )._isGoodLoose)
   , _caloComp(const_cast<TCMuon &>( rhs )._caloComp)
   , _segComp(const_cast<TCMuon &>( rhs )._segComp)
   , _numberOfMatches(const_cast<TCMuon &>( rhs )._numberOfMatches)
   , _numberOfMatchedStations(const_cast<TCMuon &>( rhs )._numberOfMatchedStations)
   , _numberOfValidPixelHits(const_cast<TCMuon &>( rhs )._numberOfValidPixelHits)
   , _numberOfValidTrackerHits(const_cast<TCMuon &>( rhs )._numberOfValidTrackerHits)
   , _numberOfLostPixelHits(const_cast<TCMuon &>( rhs )._numberOfLostPixelHits)
   , _numberOfLostTrackerHits(const_cast<TCMuon &>( rhs )._numberOfLostTrackerHits)
   , _numberOfValidMuonHits(const_cast<TCMuon &>( rhs )._numberOfValidMuonHits)
   , _trackLayersWithMeasurement(const_cast<TCMuon &>( rhs )._trackLayersWithMeasurement)
   , _pixelLayersWithMeasurement(const_cast<TCMuon &>( rhs )._pixelLayersWithMeasurement)
   , _normalizedChi2(const_cast<TCMuon &>( rhs )._normalizedChi2)
   , _normalizedChi2_tracker(const_cast<TCMuon &>( rhs )._normalizedChi2_tracker)
   , _pfIsoCharged(const_cast<TCMuon &>( rhs )._pfIsoCharged)
   , _pfIsoNeutral(const_cast<TCMuon &>( rhs )._pfIsoNeutral)
   , _pfIsoPhoton(const_cast<TCMuon &>( rhs )._pfIsoPhoton)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
TCMuon::~TCMuon() {
}
#endif // TCMuon_cxx

#ifndef TCPhoton_cxx
#define TCPhoton_cxx
TCPhoton::TCPhoton() {
}
TCPhoton::TCPhoton(const TCPhoton & rhs)
   : TCEGamma(const_cast<TCPhoton &>( rhs ))
   , _trackVeto(const_cast<TCPhoton &>( rhs )._trackVeto)
   , _convVeto(const_cast<TCPhoton &>( rhs )._convVeto)
   , _mipchi2(const_cast<TCPhoton &>( rhs )._mipchi2)
   , _miptoten(const_cast<TCPhoton &>( rhs )._miptoten)
   , _mipslope(const_cast<TCPhoton &>( rhs )._mipslope)
   , _mipintercept(const_cast<TCPhoton &>( rhs )._mipintercept)
   , _mipnhitcone(const_cast<TCPhoton &>( rhs )._mipnhitcone)
   , _mipishalo(const_cast<TCPhoton &>( rhs )._mipishalo)
   , _roundness(const_cast<TCPhoton &>( rhs )._roundness)
   , _angle(const_cast<TCPhoton &>( rhs )._angle)
   , _smin(const_cast<TCPhoton &>( rhs )._smin)
   , _smaj(const_cast<TCPhoton &>( rhs )._smaj)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
TCPhoton::~TCPhoton() {
}
#endif // TCPhoton_cxx

#ifndef TCGenJet_cxx
#define TCGenJet_cxx
TCGenJet::TCGenJet() {
}
TCGenJet::TCGenJet(const TCGenJet & rhs)
   : TCPhysObject(const_cast<TCGenJet &>( rhs ))
   , _progenitorP4(const_cast<TCGenJet &>( rhs )._progenitorP4)
   , _hadEnergy(const_cast<TCGenJet &>( rhs )._hadEnergy)
   , _emEnergy(const_cast<TCGenJet &>( rhs )._emEnergy)
   , _invEnergy(const_cast<TCGenJet &>( rhs )._invEnergy)
   , _auxEnergy(const_cast<TCGenJet &>( rhs )._auxEnergy)
   , _numConstit(const_cast<TCGenJet &>( rhs )._numConstit)
   , _numChPart(const_cast<TCGenJet &>( rhs )._numChPart)
   , _jetFlavor(const_cast<TCGenJet &>( rhs )._jetFlavor)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
TCGenJet::~TCGenJet() {
}
#endif // TCGenJet_cxx

#ifndef TCGenParticle_cxx
#define TCGenParticle_cxx
TCGenParticle::TCGenParticle() {
   _mother = 0;
}
TCGenParticle::TCGenParticle(const TCGenParticle & rhs)
   : TCPhysObject(const_cast<TCGenParticle &>( rhs ))
   , _mother(const_cast<TCGenParticle &>( rhs )._mother)
   , _PDGID(const_cast<TCGenParticle &>( rhs )._PDGID)
   , _status(const_cast<TCGenParticle &>( rhs )._status)
   , _isParton(const_cast<TCGenParticle &>( rhs )._isParton)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TCGenParticle &modrhs = const_cast<TCGenParticle &>( rhs );
   modrhs._mother = 0;
}
TCGenParticle::~TCGenParticle() {
   delete _mother;   _mother = 0;
}
#endif // TCGenParticle_cxx

#ifndef TCTriggerObject_cxx
#define TCTriggerObject_cxx
TCTriggerObject::TCTriggerObject() {
}
TCTriggerObject::TCTriggerObject(const TCTriggerObject & rhs)
   : TLorentzVector(const_cast<TCTriggerObject &>( rhs ))
   , _id(const_cast<TCTriggerObject &>( rhs )._id)
   , _HLTName(const_cast<TCTriggerObject &>( rhs )._HLTName)
   , _moduleName(const_cast<TCTriggerObject &>( rhs )._moduleName)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TCTriggerObject &modrhs = const_cast<TCTriggerObject &>( rhs );
   modrhs._HLTName.clear();
   modrhs._moduleName.clear();
}
TCTriggerObject::~TCTriggerObject() {
}
#endif // TCTriggerObject_cxx

#ifndef TCPrimaryVtx_cxx
#define TCPrimaryVtx_cxx
TCPrimaryVtx::TCPrimaryVtx() {
}
TCPrimaryVtx::TCPrimaryVtx(const TCPrimaryVtx & rhs)
   : TVector3(const_cast<TCPrimaryVtx &>( rhs ))
   , _nDof(const_cast<TCPrimaryVtx &>( rhs )._nDof)
   , _chi2(const_cast<TCPrimaryVtx &>( rhs )._chi2)
   , _isFake(const_cast<TCPrimaryVtx &>( rhs )._isFake)
   , _nTracks(const_cast<TCPrimaryVtx &>( rhs )._nTracks)
   , _sumPt2Trks(const_cast<TCPrimaryVtx &>( rhs )._sumPt2Trks)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
TCPrimaryVtx::~TCPrimaryVtx() {
}
#endif // TCPrimaryVtx_cxx

