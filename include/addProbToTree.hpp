#ifndef addProbToTree_h
#define addProbToTree_h

// C++
#include <iostream>

//ROOT
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TF1.h>
#include <TDirectory.h>
#include <TLorentzVector.h>
#include <TSystem.h>


using namespace std;

class addProbToTree
{

public:
	addProbToTree(TTree *, TString, int, TString);
	~addProbToTree();

	void Loop();
   
	
private:
	
	bool _includePathIsSet;
	
	int _max, _limitStat, _channel;
	
	float m1, m2, mzz, h1, h2, hs, phi, phi1, l1m_pT, l1p_pT, l2m_pT, l2p_pT, l1m_eta, l1p_eta, l2m_eta, l2p_eta;
	unsigned int _flavorType, flavorType;
	
	// SM signal probablities
	float	p0plus_ANA, p0plus_VA;
	
	// Probabilities for exotic spin 2 models
	float p2mplus_VA, p2hplus_VA, p2bplus_VA, p2hminus_VA, p2h2plus_VA, p2h3plus_VA, p2h6plus_VA, p2h7plus_VA, p2h9minus_VA, p2h10minus_VA;
	float p2mplus_qqb_VA, p2hplus_qqb_VA, p2bplus_qqb_VA, p2hminus_qqb_VA, p2h2plus_qqb_VA, p2h3plus_qqb_VA, p2h6plus_qqb_VA, p2h7plus_qqb_VA, p2h9minus_qqb_VA, p2h10minus_qqb_VA;
	float p2mplusPid_VA, p2hplusPid_VA, p2bplusPid_VA, p2hminusPid_VA, p2h2plusPid_VA, p2h3plusPid_VA, p2h6plusPid_VA, p2h7plusPid_VA, p2h9minusPid_VA, p2h10minusPid_VA;
	float p2mplus_ANA, p2hplus_ANA, p2bplus_ANA, p2hminus_ANA, p2h2plus_ANA, p2h3plus_ANA, p2h6plus_ANA, p2h7plus_ANA, p2h9minus_ANA, p2h10minus_ANA;
	float p2mplus_qqb_ANA, p2hplus_qqb_ANA, p2bplus_qqb_ANA, p2hminus_qqb_ANA, p2h2plus_qqb_ANA, p2h3plus_qqb_ANA, p2h6plus_qqb_ANA, p2h7plus_qqb_ANA, p2h9minus_qqb_ANA, p2h10minus_qqb_ANA;
	float p2mplusPid_ANA, p2hplusPid_ANA, p2bplusPid_ANA, p2hminusPid_ANA, p2h2plusPid_ANA, p2h3plusPid_ANA, p2h6plusPid_ANA, p2h7plusPid_ANA, p2h9minusPid_ANA, p2h10minusPid_ANA;

	TFile *newFile;
	TTree *newTree, *sigTree;
	
	TString _outputFileName;
	
};

#endif