#include "TLorentzVector.h"
#include "TMath.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TString.h"

#include "../include/addProbToTree.hpp"
#include "../../../interface/TVar.hh"
#include "../../../interface/Mela.h"


///////////////////////////////
// Add Probabilities to Tree //
///////////////////////////////

using namespace std;

//=================================================================================================
addProbToTree::addProbToTree(TTree *tree, TString channel, int limitStat, TString outputFileName)
{
	_outputFileName = outputFileName;
	_limitStat = limitStat;
	_max = 300000;
	_includePathIsSet = false;
	
	sigTree = tree;

	if ( channel == "4e" )
		_channel = 1;
	else if ( channel == "4mu" )
		_channel = 2;
	else if ( channel == "2e2mu" )
		_channel = 3;
	
	// Connect channel for MELA and flavor type from Trees
	if ( _channel == 1 )
		_flavorType = 0;
	else if ( _channel == 2 )
		_flavorType = 1;
	else if ( _channel == 3 )
		_flavorType = 3;

	sigTree->SetBranchAddress("Z2Mass", &m2);
	sigTree->SetBranchAddress("Z1Mass", &m1);
	sigTree->SetBranchAddress("ZZMass", &mzz);
	sigTree->SetBranchAddress("costhetastar",  &hs);
	sigTree->SetBranchAddress("helcosthetaZ1", &h1);
	sigTree->SetBranchAddress("helcosthetaZ2", &h2);
	sigTree->SetBranchAddress("helphi", &phi);
	sigTree->SetBranchAddress("phistarZ1", &phi1);
	
//	sigTree->SetBranchAddress("l1m_pT",  &l1m_pT);
//	sigTree->SetBranchAddress("l1p_pT",  &l1p_pT);
//	sigTree->SetBranchAddress("l2m_pT",  &l2m_pT);
//	sigTree->SetBranchAddress("l2p_pT",  &l2p_pT);
//	sigTree->SetBranchAddress("l1m_eta", &l1m_eta);
//	sigTree->SetBranchAddress("l1p_eta", &l1p_eta);
//	sigTree->SetBranchAddress("l2m_eta", &l2m_eta);
//	sigTree->SetBranchAddress("l2p_eta", &l2p_eta);
//	sigTree->SetBranchAddress("flavortype", &flavorType);
	
	newFile = new TFile(_outputFileName, "RECREATE");
	newTree = sigTree->CloneTree(0);
	
	/////////////////////////////
	// Production dependent gg //
	/////////////////////////////
	
	newTree->Branch("p0plus_VA",   &p0plus_VA,   "p0plus_VA/F");  // Higgs, vector algebra, JHUgen
	newTree->Branch("p0plus_ANA",  &p0plus_ANA,  "p0plus_ANA/F"); // Higgs, vector algebra, Analytical
	
	newTree->Branch("p2mplus_VA",  &p2mplus_VA,  "p2mplus_VA/F");  // 2m+, vector algebra, JHUgen
	newTree->Branch("p2mplus_ANA", &p2mplus_ANA, "p2mplus_ANA/F"); // 2m+, vector algebra, Analytical
	
	newTree->Branch("p2hplus_VA",  &p2hplus_VA,  "p2hplus_VA/F");  // 2h+, vector algebra, JHUgen
	newTree->Branch("p2hplus_ANA", &p2hplus_ANA, "p2hplus_ANA/F"); // 2h+, vector algebra, Analytical
	
	newTree->Branch("p2bplus_VA",  &p2bplus_VA,  "p2bplus_VA/F");  // 2b+, vector algebra, JHUgen
	newTree->Branch("p2bplus_ANA", &p2bplus_ANA, "p2bplus_ANA/F"); // 2b+, vector algebra, Analytical
	
	newTree->Branch("p2hminus_VA",  &p2hminus_VA,  "p2hminus_VA/F");  // 2h-, vector algebra, JHUgen
	newTree->Branch("p2hminus_ANA", &p2hminus_ANA, "p2hminus_ANA/F"); // 2h-, vector algebra, Analytical
	
	newTree->Branch("p2h2plus_VA",  &p2h2plus_VA,  "p2h2plus_VA/F");   // 2h2+, vector algebra, JHUgen
	newTree->Branch("p2h2plus_ANA", &p2h2plus_ANA, "p2h2plus_ANA/F" ); // 2h2+, vector algebra, Analytical
	
	newTree->Branch("p2h3plus_VA",  &p2h3plus_VA,  "p2h3plus_VA/F");   // 2h3+, vector algebra, JHUgen
	newTree->Branch("p2h3plus_ANA", &p2h3plus_ANA, "p2h3plus_ANA/F" ); // 2h3+, vector algebra, Analytical
	
	newTree->Branch("p2h6plus_VA",  &p2h6plus_VA,  "p2h6plus_VA/F");   // 2h6+, vector algebra, JHUgen
	newTree->Branch("p2h6plus_ANA", &p2h6plus_ANA, "p2h6plus_ANA/F" ); // 2h6+, vector algebra, Analytical
	
	newTree->Branch("p2h7plus_VA",  &p2h7plus_VA,  "p2h7plus_VA/F");   // 2h7+, vector algebra, JHUgen
	newTree->Branch("p2h7plus_ANA", &p2h7plus_ANA, "p2h7plus_ANA/F" ); // 2h7+, vector algebra, Analytical
	
	newTree->Branch("p2h9minus_VA",  &p2h9minus_VA,  "p2h9minus_VA/F");   // 2h9-, vector algebra, JHUgen
	newTree->Branch("p2h9minus_ANA", &p2h9minus_ANA, "p2h9minus_ANA/F" ); // 2h9-, vector algebra, Analytical
	
	newTree->Branch("p2h10minus_VA",  &p2h10minus_VA,  "p2h10minus_VA/F");   // 2h10-, vector algebra, JHUgen
	newTree->Branch("p2h10minus_ANA", &p2h10minus_ANA, "p2h10minus_ANA/F" ); // 2h10-, vector algebra, Analytical
	
	
	////////////////////////////////
	// Production dependent qqb //
	////////////////////////////////
	
	newTree->Branch("p2mplus_qqb_VA",  &p2mplus_qqb_VA,  "p2mplus_qqb_VA/F");  // 2m+, vector algebra, JHUgen
	newTree->Branch("p2mplus_qqb_ANA", &p2mplus_qqb_ANA, "p2mplus_qqb_ANA/F"); // 2m+, vector algebra, Analytical
	
	newTree->Branch("p2hplus_qqb_VA",  &p2hplus_qqb_VA,  "p2hplus_qqb_VA/F");  // 2h+, vector algebra, JHUgen
	newTree->Branch("p2hplus_qqb_ANA", &p2hplus_qqb_ANA, "p2hplus_qqb_ANA/F"); // 2h+, vector algebra, Analytical
	
	newTree->Branch("p2bplus_qqb_VA",  &p2bplus_qqb_VA,  "p2bplus_qqb_VA/F");  // 2b+, vector algebra, JHUgen
	newTree->Branch("p2bplus_qqb_ANA", &p2bplus_qqb_ANA, "p2bplus_qqb_ANA/F"); // 2b+, vector algebra, Analytical
	
	newTree->Branch("p2hminus_qqb_VA",  &p2hminus_qqb_VA,  "p2hminus_qqb_VA/F");  // 2h-, vector algebra, JHUgen
	newTree->Branch("p2hminus_qqb_ANA", &p2hminus_qqb_ANA, "p2hminus_qqb_ANA/F"); // 2h-, vector algebra, Analytical
	
	newTree->Branch("p2h2plus_qqb_VA",  &p2h2plus_qqb_VA,  "p2h2plus_qqb_VA/F");   // 2h2+, vector algebra, JHUgen
	newTree->Branch("p2h2plus_qqb_ANA", &p2h2plus_qqb_ANA, "p2h2plus_qqb_ANA/F" ); // 2h2+, vector algebra, Analytical
	
	newTree->Branch("p2h3plus_qqb_VA",  &p2h3plus_qqb_VA,  "p2h3plus_qqb_VA/F");   // 2h3+, vector algebra, JHUgen
	newTree->Branch("p2h3plus_qqb_ANA", &p2h3plus_qqb_ANA, "p2h3plus_qqb_ANA/F" ); // 2h3+, vector algebra, Analytical
	
	newTree->Branch("p2h6plus_qqb_VA",  &p2h6plus_qqb_VA,  "p2h6plus_qqb_VA/F");   // 2h6+, vector algebra, JHUgen
	newTree->Branch("p2h6plus_qqb_ANA", &p2h6plus_qqb_ANA, "p2h6plus_qqb_ANA/F" ); // 2h6+, vector algebra, Analytical
	
	newTree->Branch("p2h7plus_qqb_VA",  &p2h7plus_qqb_VA,  "p2h7plus_qqb_VA/F");   // 2h7+, vector algebra, JHUgen
	newTree->Branch("p2h7plus_qqb_ANA", &p2h7plus_qqb_ANA, "p2h7plus_qqb_ANA/F" ); // 2h7+, vector algebra, Analytical
	
	newTree->Branch("p2h9minus_qqb_VA",  &p2h9minus_qqb_VA,  "p2h9minus_qqb_VA/F");   // 2h9-, vector algebra, JHUgen
	newTree->Branch("p2h9minus_qqb_ANA", &p2h9minus_qqb_ANA, "p2h9minus_qqb_ANA/F" ); // 2h9-, vector algebra, Analytical
	
	newTree->Branch("p2h10minus_qqb_VA",  &p2h10minus_qqb_VA,  "p2h10minus_qqb_VA/F");   // 2h10-, vector algebra, JHUgen
	newTree->Branch("p2h10minus_qqb_ANA", &p2h10minus_qqb_ANA, "p2h10minus_qqb_ANA/F" ); // 2h10-, vector algebra, Analytical
	
	
	
	////////////////////////////
	// Production independent //
	////////////////////////////
	
	newTree->Branch("p2mplusPid_VA",  &p2mplusPid_VA,  "p2mplusPid_VA/F");  // 2m+, vector algebra, JHUgen
	newTree->Branch("p2mplusPid_ANA", &p2mplusPid_ANA, "p2mplusPid_ANA/F"); // 2m+, vector algebra, Analytical
	
	newTree->Branch("p2hplusPid_VA",  &p2hplusPid_VA,  "p2hplusPid_VA/F");  // 2h+, vector algebra, JHUgen
	newTree->Branch("p2hplusPid_ANA", &p2hplusPid_ANA, "p2hplusPid_ANA/F"); // 2h+, vector algebra, Analytical
	
	newTree->Branch("p2bplusPid_VA",  &p2bplusPid_VA,  "p2bplusPid_VA/F");  // 2b+, vector algebra, JHUgen
	newTree->Branch("p2bplusPid_ANA", &p2bplusPid_ANA, "p2bplusPid_ANA/F"); // 2b+, vector algebra, Analytical
	
	newTree->Branch("p2hminusPid_VA",  &p2hminusPid_VA,  "p2hminusPid_VA/F");  // 2h-, vector algebra, JHUgen
	newTree->Branch("p2hminusPid_ANA", &p2hminusPid_ANA, "p2hminusPid_ANA/F"); // 2h-, vector algebra, Analytical
	
	newTree->Branch("p2h2plusPid_VA",  &p2h2plusPid_VA,  "p2h2plusPid_VA/F");   // 2h2+, vector algebra, JHUgen
	newTree->Branch("p2h2plusPid_ANA", &p2h2plusPid_ANA, "p2h2plusPid_ANA/F" ); // 2h2+, vector algebra, Analytical
	
	newTree->Branch("p2h3plusPid_VA",  &p2h3plusPid_VA,  "p2h3plusPid_VA/F");   // 2h3+, vector algebra, JHUgen
	newTree->Branch("p2h3plusPid_ANA", &p2h3plusPid_ANA, "p2h3plusPid_ANA/F" ); // 2h3+, vector algebra, Analytical
	
	newTree->Branch("p2h6plusPid_VA",  &p2h6plusPid_VA,  "p2h6plusPid_VA/F");   // 2h6+, vector algebra, JHUgen
	newTree->Branch("p2h6plusPid_ANA", &p2h6plusPid_ANA, "p2h6plusPid_ANA/F" ); // 2h6+, vector algebra, Analytical
	
	newTree->Branch("p2h7plusPid_VA",  &p2h7plusPid_VA,  "p2h7plusPid_VA/F");   // 2h7+, vector algebra, JHUgen
	newTree->Branch("p2h7plusPid_ANA", &p2h7plusPid_ANA, "p2h7plusPid_ANA/F" ); // 2h7+, vector algebra, Analytical
	
	newTree->Branch("p2h9minusPid_VA",  &p2h9minusPid_VA,  "p2h9minusPid_VA/F");   // 2h9-, vector algebra, JHUgen
	newTree->Branch("p2h9minusPid_ANA", &p2h9minusPid_ANA, "p2h9minusPid_ANA/F" ); // 2h9-, vector algebra, Analytical
	
	newTree->Branch("p2h10minusPid_VA",  &p2h10minusPid_VA,  "p2h10minusPid_VA/F");   // 2h10-, vector algebra, JHUgen
	newTree->Branch("p2h10minusPid_ANA", &p2h10minusPid_ANA, "p2h10minusPid_ANA/F" ); // 2h10-, vector algebra, Analytical

}
//=================================================================================================



//=============================
addProbToTree::~addProbToTree()
{}
//=============================



//========================================
void addProbToTree::Loop()
{
	Mela myMELA(8, 125.6);

//	RooMsgService::instance().getStream(1).removeTopic(NumIntegration);
	
	
	for ( int iEvt = 0; iEvt < (_limitStat == 1 ? _max : sigTree->GetEntries() ); iEvt++ )
	{
		if ( iEvt >= sigTree->GetEntries() )
			break;
		
		if ( iEvt % 1000 == 1 ) cout << "[INFO] \n # of event: " << iEvt << endl;
    
		sigTree->GetEntry(iEvt);
		
//		cout << _flavorType << endl << flavorType << endl;
		
		
		
		
//		// Has to be changed manually
//		if ( _flavorType != flavorType ) continue;
//
//		bool elePtCut = l1m_pT > 7 && l1p_pT > 7 && l2m_pT > 7 && l2p_pT > 7;
//		bool muonPtCut = l1m_pT > 5 && l1p_pT > 5 && l2m_pT > 5 && l2p_pT > 5;
//		bool eleMuonPtCut = l1m_pT > 7 && l1p_pT > 7 && l2m_pT > 5 && l2p_pT > 5;
//		
//		bool eleEtaCut = abs(l1m_eta) < 2.5 && abs(l1p_eta) < 2.5 && abs(l2m_eta) < 2.5 && abs(l2p_eta) < 2.5;
//		bool muonEtaCut = abs(l1m_eta) < 2.4 && abs(l1p_eta) < 2.4 && abs(l2m_eta) < 2.4 && abs(l2p_eta) < 2.4;
//		bool eleMuonEtaCut = abs(l1m_eta) < 2.5 && abs(l1m_eta) < 2.5 && abs(l2m_eta) < 2.4 && abs(l2p_eta) < 2.4;
//		
//		bool passMz2 = m2 > 12 && m2 < 120;
//		bool passMz1 = m1 > 40 && m1 < 120;
//		bool passMzz = mzz > 100.;
//		
//		bool passing4e = elePtCut && eleEtaCut && passMz1 && passMz2 && passMzz;
//		bool passing4mu = muonPtCut && muonEtaCut && passMz1 && passMz2 && passMzz;
//		bool passing2e2mu = eleMuonPtCut && eleMuonEtaCut && passMz1 && passMz2 && passMzz;
//
////		cout << "[INFO]: Passing or not: " << passing2e2mu << " " << mzz << endl;
//		
//		// Cuts
//		if ( _flavorType == 3 )
//		{
//			if ( !passing4mu ) continue;
//		}
//		else if ( _flavorType == 0 )
//		{
//			if ( !passing4e ) continue;
//		}
//		else if ( _flavorType == 1 )
//			if ( !passing4mu ) continue;
		
		
		
		
	
/////////////////////////////
// Analytical calculations //
/////////////////////////////

// Production dependent gg
		// 0+
		myMELA.setProcess(TVar::HSMHiggs, TVar::ANALYTICAL, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs,h1,h2,phi,phi1,_channel, p0plus_ANA);
		
		// 2m+
		myMELA.setProcess(TVar::H2_g1g5, TVar::ANALYTICAL, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2mplus_ANA);
		
		// 2h+
		myMELA.setProcess(TVar::H2_g4, TVar::ANALYTICAL, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2hplus_ANA);
		
		// 2b+
		myMELA.setProcess(TVar::H2_g5, TVar::ANALYTICAL, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2bplus_ANA);
		
		// 2h-
		myMELA.setProcess(TVar::H2_g8, TVar::ANALYTICAL, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2hminus_ANA);
	
		// 2h2+
		myMELA.setProcess(TVar::H2_g2, TVar::ANALYTICAL, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h2plus_ANA);
		
		// 2h3+
		myMELA.setProcess(TVar::H2_g3, TVar::ANALYTICAL, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h3plus_ANA);
		
		// 2h6+
		myMELA.setProcess(TVar::H2_g6, TVar::ANALYTICAL, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h6plus_ANA);
		
		// 2h7+
		myMELA.setProcess(TVar::H2_g7, TVar::ANALYTICAL, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h7plus_ANA);
		
		// 2h9-
		myMELA.setProcess(TVar::H2_g9, TVar::ANALYTICAL, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h9minus_ANA);
		
		// 2h10-
		myMELA.setProcess(TVar::H2_g10, TVar::ANALYTICAL, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h10minus_ANA);
		
		
// Production dependent qqb
		// 2m+
		myMELA.setProcess(TVar::H2_g1g5, TVar::ANALYTICAL, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2mplus_qqb_ANA);
		
		// 2h+
		myMELA.setProcess(TVar::H2_g4, TVar::ANALYTICAL, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2hplus_qqb_ANA);
		
		// 2b+
		myMELA.setProcess(TVar::H2_g5, TVar::ANALYTICAL, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2bplus_qqb_ANA);
		
		// 2h-
		myMELA.setProcess(TVar::H2_g8, TVar::ANALYTICAL, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2hminus_qqb_ANA);
		
		// 2h2+
		myMELA.setProcess(TVar::H2_g2, TVar::ANALYTICAL, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h2plus_qqb_ANA);
		
		// 2h3+
		myMELA.setProcess(TVar::H2_g3, TVar::ANALYTICAL, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h3plus_qqb_ANA);
		
		// 2h6+
		myMELA.setProcess(TVar::H2_g6, TVar::ANALYTICAL, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h6plus_qqb_ANA);
		
		// 2h7+
		myMELA.setProcess(TVar::H2_g7, TVar::ANALYTICAL, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h7plus_qqb_ANA);
		
		// 2h9-
		myMELA.setProcess(TVar::H2_g9, TVar::ANALYTICAL, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h9minus_qqb_ANA);
		
		// 2h10-
		myMELA.setProcess(TVar::H2_g10, TVar::ANALYTICAL, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h10minus_qqb_ANA);
		
		
// Production independent
		// 2m+
		myMELA.setProcess(TVar::H2_g1g5, TVar::ANALYTICAL, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2mplusPid_ANA);
		
		// 2h+
		myMELA.setProcess(TVar::H2_g4, TVar::ANALYTICAL, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2hplusPid_ANA);
		
		// 2b+
		myMELA.setProcess(TVar::H2_g5, TVar::ANALYTICAL, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2bplusPid_ANA);
		
		// 2h-
		myMELA.setProcess(TVar::H2_g8, TVar::ANALYTICAL, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2hminusPid_ANA);
		
		// 2h2+
		myMELA.setProcess(TVar::H2_g2, TVar::ANALYTICAL, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h2plusPid_ANA);
		
		// 2h3+
		myMELA.setProcess(TVar::H2_g3, TVar::ANALYTICAL, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h3plusPid_ANA);
		
		// 2h6+
		myMELA.setProcess(TVar::H2_g6, TVar::ANALYTICAL, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h6plusPid_ANA);
		
		// 2h7+
		myMELA.setProcess(TVar::H2_g7, TVar::ANALYTICAL, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h7plusPid_ANA);
		
		// 2h9-
		myMELA.setProcess(TVar::H2_g9, TVar::ANALYTICAL, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h9minusPid_ANA);
		
		// 2h10-
		myMELA.setProcess(TVar::H2_g10, TVar::ANALYTICAL, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h10minusPid_ANA);
		
		
		
		
		
//    // 1-
//    myMELA.setProcess(TVar::VZZ_4l, TVar::ANALYTICAL, TVar::QQB);
//    myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p1_mela);

//    // Production independent
//    myMELA.setProcess(TVar::VZZ_4l, TVar::ANALYTICAL, TVar::ZZINDEPENDENT);
//    myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p1_decay_mela);

//    // 1+
//    myMELA.setProcess(TVar::AVZZ_4l, TVar::ANALYTICAL, TVar::QQB);
//    myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p1plus_mela);
//
//    // production independent
//    myMELA.setProcess(TVar::AVZZ_4l, TVar::ANALYTICAL, TVar::ZZINDEPENDENT);
//    myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p1plus_decay_mela);

//    // gg->2m+
//    myMELA.setProcess(TVar::TZZ_4l, TVar::ANALYTICAL, TVar::GG);
//    myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2_mela);

//    // qqb->2m+
//    myMELA.setProcess(TVar::TZZ_4l, TVar::ANALYTICAL, TVar::QQB);
//    myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2qqb_mela);

//    // qqb->2m+
//    myMELA.setProcess(TVar::TZZ_4l, TVar::ANALYTICAL, TVar::ZZINDEPENDENT);
//    myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2_decay_mela);
		
//		qqZZ0+
//    myMELA.setProcess(TVar::ZZ_2e2m, TVar::ANALYTICAL, TVar::QQB);
//    myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, bkg_mela);

		

/////////////////////////
// JHUGen calculations //
/////////////////////////
		
// Production dependent
		// 0+
		myMELA.setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p0plus_VA);
		
		// 2m+
		myMELA.setProcess(TVar::H2_g1g5, TVar::JHUGen, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2mplus_VA);
		
		// 2h+
		myMELA.setProcess(TVar::H2_g4, TVar::JHUGen, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2hplus_VA);
		
		// 2b+
		myMELA.setProcess(TVar::H2_g5, TVar::JHUGen, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2bplus_VA);
		
		// 2h-
		myMELA.setProcess(TVar::H2_g8, TVar::JHUGen, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2hminus_VA);
		
		// 2h2+
		myMELA.setProcess(TVar::H2_g2, TVar::JHUGen, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h2plus_VA);
		
		// 2h3+
		myMELA.setProcess(TVar::H2_g3, TVar::JHUGen, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h3plus_VA);
		
		// 2h6+
		myMELA.setProcess(TVar::H2_g6, TVar::JHUGen, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h6plus_VA);
		
		// 2h7+
		myMELA.setProcess(TVar::H2_g7, TVar::JHUGen, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h7plus_VA);
		
		// 2h9-
		myMELA.setProcess(TVar::H2_g9, TVar::JHUGen, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h9minus_VA);
		
		// 2h10-
		myMELA.setProcess(TVar::H2_g10, TVar::JHUGen, TVar::ZZGG);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h10minus_VA);

		
// Production dependent qqb
		// 2m+
		myMELA.setProcess(TVar::H2_g1g5, TVar::JHUGen, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2mplus_qqb_VA);
		
		// 2h+
		myMELA.setProcess(TVar::H2_g4, TVar::JHUGen, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2hplus_qqb_VA);
		
		// 2b+
		myMELA.setProcess(TVar::H2_g5, TVar::JHUGen, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2bplus_qqb_VA);
		
		// 2h-
		myMELA.setProcess(TVar::H2_g8, TVar::JHUGen, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2hminus_qqb_VA);
		
		// 2h2+
		myMELA.setProcess(TVar::H2_g2, TVar::JHUGen, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h2plus_qqb_VA);
		
		// 2h3+
		myMELA.setProcess(TVar::H2_g3, TVar::JHUGen, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h3plus_qqb_VA);
		
		// 2h6+
		myMELA.setProcess(TVar::H2_g6, TVar::JHUGen, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h6plus_qqb_VA);
		
		// 2h7+
		myMELA.setProcess(TVar::H2_g7, TVar::JHUGen, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h7plus_qqb_VA);
		
		// 2h9-
		myMELA.setProcess(TVar::H2_g9, TVar::JHUGen, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h9minus_qqb_VA);
		
		// 2h10-
		myMELA.setProcess(TVar::H2_g10, TVar::JHUGen, TVar::ZZQQB);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h10minus_qqb_VA);
		
		
// Production independent
		// 2m+
		myMELA.setProcess(TVar::H2_g1g5, TVar::JHUGen, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2mplusPid_VA);
		
		// 2h+
		myMELA.setProcess(TVar::H2_g4, TVar::JHUGen, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2hplusPid_VA);
		
		// 2b+
		myMELA.setProcess(TVar::H2_g5, TVar::JHUGen, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2bplusPid_VA);
		
		// 2h-
		myMELA.setProcess(TVar::H2_g8, TVar::JHUGen, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2hminusPid_VA);
		
		// 2h2+
		myMELA.setProcess(TVar::H2_g2, TVar::JHUGen, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h2plusPid_VA);
		
		// 2h3+
		myMELA.setProcess(TVar::H2_g3, TVar::JHUGen, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h3plusPid_VA);
		
		// 2h6+
		myMELA.setProcess(TVar::H2_g6, TVar::JHUGen, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h6plusPid_VA);
		
		// 2h7+
		myMELA.setProcess(TVar::H2_g7, TVar::JHUGen, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h7plusPid_VA);
		
		// 2h9-
		myMELA.setProcess(TVar::H2_g9, TVar::JHUGen, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h9minusPid_VA);
		
		// 2h10-
		myMELA.setProcess(TVar::H2_g10, TVar::JHUGen, TVar::ZZINDEPENDENT);
		myMELA.computeP(mzz, m1, m2, hs, h1, h2, phi, phi1, _channel, p2h10minusPid_VA);
		
		
		
		
		
		
		
//    // qqZZ 
//
//    if ( _channel == 3 ) {
//      myMELA.setProcess(TVar::ZZ_2e2m, TVar::MCFM, TVar::QQB);
//      myMELA.computeP(mzz, m1, m2, 
//		      hs,h1,h2,phi,phi1,_channel, bkg_VAMCFM);
//    } else {
//      myMELA.setProcess(TVar::ZZ_4e, TVar::MCFM, TVar::QQB);
//      myMELA.computeP(mzz, m1, m2, 
//		      hs,h1,h2,phi,phi1,_channel, bkg_VAMCFM);
//    }
//
//    // ggZZ
//    myMELA.setProcess(TVar::GGZZ_4l, TVar::MCFM, TVar::GG);
//    myMELA.computeP(mzz, m1, m2, 
//		    hs,h1,h2,phi,phi1,_channel, ggzz_VAMCFM);
//
//    // ******  qqZZ-> production independent 
//    
//    /*
//    if ( _channel == 3 ) {
//      myMELA.setProcess(TVar::ZZ_2e2m, TVar::MCFM, TVar::ZZINDEPENDENT);
//      myMELA.computeP(mzz, m1, m2, 
//		      hs,h1,h2,phi,phi1,_channel, bkg_decay_VAMCFM);
//    } else {
//      myMELA.setProcess(TVar::ZZ_4e, TVar::MCFM, TVar::ZZINDEPENDENT);
//      myMELA.computeP(mzz, m1, m2, 
//		      hs,h1,h2,phi,phi1,_channel, bkg_decay_VAMCFM);
//    }
//    */
//
//    // 0+
//    myMELA.setProcess(TVar::HZZ_4l, TVar::MCFM, TVar::GG);
//    myMELA.computeP(mzz, m1, m2, hs,h1,h2,phi,phi1,_channel, p0plus_VAMCFM);
//
//    // 1-
//    myMELA.setProcess(TVar::VZZ_4l, TVar::JHUGen, TVar::QQB);
//    myMELA.computeP(mzz, m1, m2, 
//		    hs,h1,h2,phi,phi1,_channel, p1_VAJHU);
//    
//    // production independent
//    myMELA.setProcess(TVar::VZZ_4l, TVar::JHUGen, TVar::ZZINDEPENDENT);
//    myMELA.computeP(mzz, m1, m2, 
//		    hs,h1,h2,phi,phi1,_channel, p1_decay_VAJHU);
//    
//    // 1+
//    myMELA.setProcess(TVar::AVZZ_4l, TVar::JHUGen, TVar::QQB);
//    myMELA.computeP(mzz, m1, m2, 
//		    hs,h1,h2,phi,phi1,_channel, p1plus_VAJHU);
//    
//    // production independent
//    myMELA.setProcess(TVar::AVZZ_4l, TVar::JHUGen, TVar::ZZINDEPENDENT);
//    myMELA.computeP(mzz, m1, m2, 
//		    hs,h1,h2,phi,phi1,_channel, p1plus_decay_VAJHU);
//    
//    // gg->2m+
//    myMELA.setProcess(TVar::TZZ_4l, TVar::JHUGen, TVar::GG);
//    myMELA.computeP(mzz, m1, m2, 
//		    hs,h1,h2,phi,phi1,_channel, p2_VAJHU);
//    
//    // qqb->2m+
//    myMELA.setProcess(TVar::TZZ_4l, TVar::JHUGen, TVar::QQB);
//    myMELA.computeP(mzz, m1, m2, 
//		    hs,h1,h2,phi,phi1,_channel, p2qqb_VAJHU);
//    
//    // qqb->2m+
//    myMELA.setProcess(TVar::TZZ_4l, TVar::JHUGen, TVar::ZZINDEPENDENT);
//    myMELA.computeP(mzz, m1, m2, 
//		    hs,h1,h2,phi,phi1,_channel, p2_decay_VAJHU);

		
		newTree->Fill();
	}
  
	newFile->cd();
	newTree->Write("SelectedTree");
//	newTree->Write();
	newFile->Close();
}