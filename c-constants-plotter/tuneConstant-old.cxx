#include <algorithm>

// ROOT includes
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TLorentzVector.h"
#include "TMath.h"
//#include "RooFit.h"

// C++ includes
#include <fstream>
#include <sstream>
#include <iostream>
#include "map"

TString inputDir = "/home/llr/cms/kovac/CMS/Analysis/SpinParity/MELA/CMSSW_5_3_9/src/ZZMatrixElement/MELA/test/outputTrees/8TeV/";
//TString inputDir = "/home/llr/cms/kovac/CMS/Analysis/SpinParity/MELA/CMSSW_5_3_9/src/ZZMatrixElement/MELA/test/outputTreesNoTuning/8TeV/";
TString saveString = "c_plots";
//TString saveString = "c_plotsNoTuning";

enum model { p2mplus, p2hplus, p2hminus, p2bplus, p2h2plus, p2h3plus, p2h6plus, p2h7plus, p2h9minus, p2h10minus, numOfModels };

//TString bins = "(1000, -3, 3)";
TString bins = "(5000, -5, 45)";


TString saveTag[10] =
{
	"2mplus",
	"2hplus",
	"2hminus",
	"2bplus",
	"2h2plus",
	"2h3plus",
	"2h6plus",
	"2h7plus",
	"2h9minus",
	"2h10minus"
};

TString sampleName[10] =
{
	"HZZ4lTree_jhuGenV3GravPMH126",
	"HZZ4lTree_jhuGenV3Grav2PHH126",
	"HZZ4lTree_jhuGenV3Grav2MHH126",
	"HZZ4lTree_jhuGenV3Grav2PBH126",
	"Graviton2PH2ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu",
	"Graviton2PH3ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu",
	"Graviton2PH6ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu",
	"Graviton2PH7ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu",
	"Graviton2MH9ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu",
	"Graviton2MH10ToZZTo4L_M-125p6_8TeV-JHUGenV3_false_2e2mu"
};

TString legendTag[10] =
{
	"J^{P} = 2^{+}_{m}",
	"J^{P} = 2^{+}_{h}",
	"J^{P} = 2^{-}_{h}",
	"J^{P} = 2^{+}_{b}",
	"J^{P} = 2^{+}_{h 2}",
	"J^{P} = 2^{+}_{h 3}",
	"J^{P} = 2^{+}_{h 6}",
	"J^{P} = 2^{+}_{h 7}",
	"J^{P} = 2^{-}_{h 9}",
	"J^{P} = 2^{-}_{h 10}"
};


//TString axisLabel[3] =
//{
//	"#it{D}_{2^{+}_{h}}",
//	"#it{D}_{2^{-}_{h}}",
//	"#it{D}_{2^{+}_{b}}"
//};

TString drawStringVA[10] =
{
	"log(p0plus_VA/p2mplus_VA)",
	"log(p0plus_VA/p2hplus_VA)",
	"log(p0plus_VA/p2hminus_VA)",
	"log(p0plus_VA/p2bplus_VA)",
	"log(p0plus_VA/p2h2plus_VA)",
	"log(p0plus_VA/p2h3plus_VA)",
	"log(p0plus_VA/p2h6plus_VA)",
	"log(p0plus_VA/p2h7plus_VA)",
	"log(p0plus_VA/p2h9minus_VA)",
	"log(p0plus_VA/p2h10minus_VA)"
};

TString drawString_qqbVA[10] =
{
	"log(p0plus_VA/p2mplus_qqb_VA)",
	"log(p0plus_VA/p2hplus_qqb_VA)",
	"log(p0plus_VA/p2hminus_qqb_VA)",
	"log(p0plus_VA/p2bplus_qqb_VA)",
	"log(p0plus_VA/p2h2plus_qqb_VA)",
	"log(p0plus_VA/p2h3plus_qqb_VA)",
	"log(p0plus_VA/p2h6plus_qqb_VA)",
	"log(p0plus_VA/p2h7plus_qqb_VA)",
	"log(p0plus_VA/p2h9minus_qqb_VA)",
	"log(p0plus_VA/p2h10minus_qqb_VA)"
};

TString drawStringPidVA[10] =
{
	"log(p0plus_VA/p2mplusPid_VA)",
	"log(p0plus_VA/p2hplusPid_VA)",
	"log(p0plus_VA/p2hminusPid_VA)",
	"log(p0plus_VA/p2bplusPid_VA)",
	"log(p0plus_VA/p2h2plusPid_VA)",
	"log(p0plus_VA/p2h3plusPid_VA)",
	"log(p0plus_VA/p2h6plusPid_VA)",
	"log(p0plus_VA/p2h7plusPid_VA)",
	"log(p0plus_VA/p2h9minusPid_VA)",
	"log(p0plus_VA/p2h10minusPid_VA)"
};

TString drawStringANA[10] =
{
	"log(p0plus_ANA/p2mplus_ANA)",
	"log(p0plus_ANA/p2hplus_ANA)",
	"log(p0plus_ANA/p2hminus_ANA)",
	"log(p0plus_ANA/p2bplus_ANA)",
	"log(p0plus_ANA/p2h2plus_ANA)",
	"log(p0plus_ANA/p2h3plus_ANA)",
	"log(p0plus_ANA/p2h6plus_ANA)",
	"log(p0plus_ANA/p2h7plus_ANA)",
	"log(p0plus_ANA/p2h9minus_ANA)",
	"log(p0plus_ANA/p2h10minus_ANA)"
};

TString drawString_qqbANA[10] =
{
	"log(p0plus_ANA/p2mplus_qqb_ANA)",
	"log(p0plus_ANA/p2hplus_qqb_ANA)",
	"log(p0plus_ANA/p2hminus_qqb_ANA)",
	"log(p0plus_ANA/p2bplus_qqb_ANA)",
	"log(p0plus_ANA/p2h2plus_qqb_ANA)",
	"log(p0plus_ANA/p2h3plus_qqb_ANA)",
	"log(p0plus_ANA/p2h6plus_qqb_ANA)",
	"log(p0plus_ANA/p2h7plus_qqb_ANA)",
	"log(p0plus_ANA/p2h9minus_qqb_ANA)",
	"log(p0plus_ANA/p2h10minus_qqb_ANA)"

TString drawStringPidANA[10] =
{
	"log(p0plus_ANA/p2mplusPid_ANA)",
	"log(p0plus_ANA/p2hplusPid_ANA)",
	"log(p0plus_ANA/p2hminusPid_ANA)",
	"log(p0plus_ANA/p2bplusPid_ANA)",
	"log(p0plus_ANA/p2h2plusPid_ANA)",
	"log(p0plus_ANA/p2h3plusPid_ANA)",
	"log(p0plus_ANA/p2h6plusPid_ANA)",
	"log(p0plus_ANA/p2h7plusPid_ANA)",
	"log(p0plus_ANA/p2h9minusPid_ANA)",
	"log(p0plus_ANA/p2h10minusPid_ANA)"
};


TString cutString;

void doCalculation( model myModel )
{

	gROOT->ProcessLine(".L ./tdrstyleC.C");
	setTDRStyle();
	gStyle->SetOptTitle(1);
	TGaxis::SetMaxDigits(3);
	gStyle->SetTitleX(0.65); //title X location
	gStyle->SetTitleY(0.9); //title Y location

	cutString = "ZZMass > 106. && ZZMass < 141.";

	
////////////////////
// Standard model //
////////////////////
	
//	TChain *SM_8_4eAnd4mu = new TChain("SelectedTree");
	TChain *SM_8_2e2mu    = new TChain("SelectedTree");
//	SM_8_4eAnd4mu->Add(inputDir+"PRODFSR_8TeV/4mu/HZZ4lTree_jhuGenV2H126.root");
//	SM_8_4eAnd4mu->Add(inputDir+"PRODFSR_8TeV/4e/HZZ4lTree_jhuGenV2H126.root");
	SM_8_2e2mu->Add(inputDir + "2e2mu/ggtoHtoZZ4l_VariousKDs_0+m_MELA.root");

//	TChain *SM_7_4eAnd4mu = new TChain("SelectedTree");
//	TChain *SM_7_2e2mu    = new TChain("SelectedTree");
//	SM_7_4eAnd4mu->Add(inputDir+"PRODFSR/4mu/HZZ4lTree_jhuGenV2H126.root");
//	SM_7_4eAnd4mu->Add(inputDir+"PRODFSR/4e/HZZ4lTree_jhuGenV2H126.root");
//	SM_7_2e2mu->Add(inputDir+"PRODFSR/2mu2e/HZZ4lTree_jhuGenV2H126.root");
	
	
// 7TeV

// 2e2mu
//	SM_7_2e2mu->Draw(drawString[myModel] + ">>SM7_2e2muHisto" + bins);
//	TH1F *SM7_2e2muHisto = (TH1F*) gDirectory->Get("SM7_2e2muHisto");
////	SM7_2e2muHisto->SetBins(nBins, xLow, xUp);
//	SM7_2e2muHisto->Scale(1/SM7_2e2muHisto->GetEntries());
	
// 4e/4mu
//	SM_7_4eAnd4mu->Draw( drawString[myModel] + ">>SM7_4eAnd4muHisto" + bins);
//	TH1F *SM7_4eAnd4muHisto = (TH1F*) gDirectory->Get("SM7_4eAnd4muHisto");
////	SM7_4eAnd4muHisto->SetBins(nBins, xLow, xUp);
//	SM7_4eAnd4muHisto->Scale(1/SM7_4eAnd4muHisto->GetEntries());

	
// 8TeV

	SM_8_2e2mu->Draw(drawStringVA[myModel] + ">>SM8_2e2mu_VA_Histo" + bins);
	TH1F *SM8_2e2mu_VA_Histo = (TH1F*) gDirectory->Get("SM8_2e2mu_VA_Histo");
//	SM8_2e2mu_VA_Histo->SetBins(nBins, xLow, xUp);
	SM8_2e2mu_VA_Histo->Scale(1/SM8_2e2mu_VA_Histo->GetEntries());

	SM_8_2e2mu->Draw(drawString_qqbVA[myModel] + ">>SM8_2e2mu_qqbVA_Histo" + bins);
	TH1F *SM8_2e2mu_qqbVA_Histo = (TH1F*) gDirectory->Get("SM8_2e2mu_qqbVA_Histo");
//	SM8_2e2mu_qqbVA_Histo->SetBins(nBins, xLow, xUp);
	SM8_2e2mu_qqbVA_Histo->Scale(1/SM8_2e2mu_qqbVA_Histo->GetEntries());
	
	SM_8_2e2mu->Draw(drawStringPidVA[myModel] + ">>SM8_2e2mu_PidVA_Histo" + bins);
	TH1F *SM8_2e2mu_PidVA_Histo = (TH1F*) gDirectory->Get("SM8_2e2mu_PidVA_Histo");
//	SM8_2e2mu_VA_Histo->SetBins(nBins, xLow, xUp);
	SM8_2e2mu_PidVA_Histo->Scale(1/SM8_2e2mu_PidVA_Histo->GetEntries());

	SM_8_2e2mu->Draw(drawStringANA[myModel] + ">>SM8_2e2mu_ANA_Histo" + bins);
	TH1F *SM8_2e2mu_ANA_Histo = (TH1F*) gDirectory->Get("SM8_2e2mu_ANA_Histo");
//	SM8_2e2mu_ANA_Histo->SetBins(nBins, xLow, xUp);
	SM8_2e2mu_ANA_Histo->Scale(1/SM8_2e2mu_ANA_Histo->GetEntries());

	SM_8_2e2mu->Draw(drawString_qqbANA[myModel] + ">>SM8_2e2mu_qqbANA_Histo" + bins);
	TH1F *SM8_2e2mu_qqbANA_Histo = (TH1F*) gDirectory->Get("SM8_2e2mu_qqbANA_Histo");
//	SM8_2e2mu_qqbANA_Histo->SetBins(nBins, xLow, xUp);
	SM8_2e2mu_qqbANA_Histo->Scale(1/SM8_2e2mu_qqbANA_Histo->GetEntries());
	
	SM_8_2e2mu->Draw(drawStringPidANA[myModel] + ">>SM8_2e2mu_PidANA_Histo" + bins);
	TH1F *SM8_2e2mu_PidANA_Histo = (TH1F*) gDirectory->Get("SM8_2e2mu_PidANA_Histo");
//	SM8_2e2mu_PidsANA_Histo->SetBins(nBins, xLow, xUp);
	SM8_2e2mu_PidANA_Histo->Scale(1/SM8_2e2mu_PidANA_Histo->GetEntries());
	
//	SM_8_4eAnd4mu->Draw( drawString[myModel] + ">>SM8_4eAnd4muHisto" + bins);
//	TH1F *SM8_4eAnd4muHisto = (TH1F*) gDirectory->Get("SM8_4eAnd4muHisto");
////	SM8_4eAnd4muHisto->SetBins(nBins, xLow, xUp);
//	SM8_4eAnd4muHisto->Scale(1/SM8_4eAnd4muHisto->GetEntries());
	
	


	
///////////////////////
// Atlernative model //
///////////////////////
	
//	TChain *PS_8_4eAnd4mu = new TChain("SelectedTree");
	TChain *PS_8_2e2mu    = new TChain("SelectedTree");
//	PS_8_4eAnd4mu->Add(inputDir+"PRODFSR_8TeV/4mu/HZZ4lTree_"+sampleName[myModel]+".root");
//	PS_8_4eAnd4mu->Add(inputDir+"PRODFSR_8TeV/4e/HZZ4lTree_"+sampleName[myModel]+".root");
	PS_8_2e2mu->Add(inputDir + "2e2mu/" + sampleName[myModel] + "_MELA.root");

//	TChain *PS_7_4eAnd4mu = new TChain("SelectedTree");
//	TChain *PS_7_2e2mu    = new TChain("SelectedTree");
//	PS_7_4eAnd4mu->Add(inputDir+"PRODFSR/4mu/HZZ4lTree_"+sampleName[myModel]+".root");
//	PS_7_4eAnd4mu->Add(inputDir+"PRODFSR/4e/HZZ4lTree_"+sampleName[myModel]+".root");
//	PS_7_2e2mu->Add(inputDir+"PRODFSR/2mu2e/HZZ4lTree_"+sampleName[myModel]+".root");

	
// 7TeV
	
//	PS_7_2e2mu->Draw(drawString[myModel] + ">>PS7_2e2muHisto" + bins);
//	TH1F *PS7_2e2muHisto = (TH1F*) gDirectory->Get("PS7_2e2muHisto");
////	PS7_2e2muHisto->SetBins(nBins, xLow, xUp);
//	PS7_2e2muHisto->Scale(1/PS7_2e2muHisto->GetEntries());
	
//	PS_7_4eAnd4mu->Draw( drawString[myModel] + ">>PS7_4eAnd4muHisto" + bins);
//	TH1F *PS7_4eAnd4muHisto = (TH1F*) gDirectory->Get("PS7_4eAnd4muHisto");
////	PS7_4eAnd4muHisto->SetBins(nBins, xLow, xUp);
//	PS7_4eAnd4muHisto->Scale(1/PS7_4eAnd4muHisto->GetEntries());

	
// 8TeV
	
	PS_8_2e2mu->Draw(drawStringVA[myModel] + ">>PS8_2e2mu_VA_Histo" + bins);
	TH1F *PS8_2e2mu_VA_Histo = (TH1F*) gDirectory->Get("PS8_2e2mu_VA_Histo");
//	PS8_2e2mu_VA_Histo->SetBins(nBins, xLow, xUp);
	PS8_2e2mu_VA_Histo->Scale(1/PS8_2e2mu_VA_Histo->GetEntries());
	
	PS_8_2e2mu->Draw(drawString_qqbVA[myModel] + ">>PS8_2e2mu_qqbVA_Histo" + bins);
	TH1F *PS8_2e2mu_qqbVA_Histo = (TH1F*) gDirectory->Get("PS8_2e2mu_qqbVA_Histo");
//	PS8_2e2mu_qqbVA_Histo->SetBins(nBins, xLow, xUp);
	PS8_2e2mu_qqbVA_Histo->Scale(1/PS8_2e2mu_qqbVA_Histo->GetEntries());
	
	PS_8_2e2mu->Draw(drawStringPidVA[myModel] + ">>PS8_2e2mu_PidVA_Histo" + bins);
	TH1F *PS8_2e2mu_PidVA_Histo = (TH1F*) gDirectory->Get("PS8_2e2mu_PidVA_Histo");
//	PS8_2e2mu_PidVA_Histo->SetBins(nBins, xLow, xUp);
	PS8_2e2mu_PidVA_Histo->Scale(1/PS8_2e2mu_PidVA_Histo->GetEntries());
	
	PS_8_2e2mu->Draw(drawStringANA[myModel] + ">>PS8_2e2mu_ANA_Histo" + bins);
	TH1F *PS8_2e2mu_ANA_Histo = (TH1F*) gDirectory->Get("PS8_2e2mu_ANA_Histo");
//	PS8_2e2mu_ANA_Histo->SetBins(nBins, xLow, xUp);
	PS8_2e2mu_ANA_Histo->Scale(1/PS8_2e2mu_ANA_Histo->GetEntries());
	
	PS_8_2e2mu->Draw(drawString_qqbANA[myModel] + ">>PS8_2e2mu_qqbANA_Histo" + bins);
	TH1F *PS8_2e2mu_qqbANA_Histo = (TH1F*) gDirectory->Get("PS8_2e2mu_qqbANA_Histo");
//	PS8_2e2mu_qqbANA_Histo->SetBins(nBins, xLow, xUp);
	PS8_2e2mu_qqbANA_Histo->Scale(1/PS8_2e2mu_qqbANA_Histo->GetEntries());
	
	PS_8_2e2mu->Draw(drawStringPidANA[myModel] + ">>PS8_2e2mu_PidANA_Histo" + bins);
	TH1F *PS8_2e2mu_PidANA_Histo = (TH1F*) gDirectory->Get("PS8_2e2mu_PidANA_Histo");
//	PS8_2e2mu_PidANA_Histo->SetBins(nBins, xLow, xUp);
	PS8_2e2mu_PidANA_Histo->Scale(1/PS8_2e2mu_PidANA_Histo->GetEntries());

//	PS_8_4eAnd4mu->Draw( drawString[myModel] + ">>PS8_4eAnd4muHisto" + bins);
//	TH1F *PS8_4eAnd4muHisto = (TH1F*) gDirectory->Get("PS8_4eAnd4muHisto");
////	PS8_4eAnd4muHisto->SetBins(nBins, xLow, xUp);
//	PS8_4eAnd4muHisto->Scale(1/PS8_4eAnd4muHisto->GetEntries());


////////////////////////////////////////
// Alternative and Standard model sum //
////////////////////////////////////////
	
//	TH1F *sum7_2e2mu = (TH1F*)SM7_2e2muHisto->Clone("sum7_2e2mu");
//	sum7_2e2mu->Add(PS7_2e2muHisto);
//	sum7_2e2mu->SetMaximum(0.012);
//	sum7_2e2mu->SetTitle("2e2#mu, 7TeV");

	TH1F *sum8_2e2mu_VA = (TH1F*)SM8_2e2mu_VA_Histo->Clone("sum8_2e2mu_VA");
	sum8_2e2mu_VA->Add(PS8_2e2mu_VA_Histo);
//	sum8_2e2mu_VA->SetMaximum(0.012);
	sum8_2e2mu_VA->SetTitle("2e2#mu, 8TeV");

	TH1F *sum8_2e2mu_qqbVA = (TH1F*)SM8_2e2mu_qqbVA_Histo->Clone("sum8_2e2mu_qqbVA");
	sum8_2e2mu_qqbVA->Add(PS8_2e2mu_qqbVA_Histo);
//	sum8_2e2mu_qqbVA->SetMaximum(0.012);
	sum8_2e2mu_qqbVA->SetTitle("2e2#mu, 8TeV");
	
	TH1F *sum8_2e2mu_PidVA = (TH1F*)SM8_2e2mu_PidVA_Histo->Clone("sum8_2e2mu_PidVA");
	sum8_2e2mu_PidVA->Add(PS8_2e2mu_PidVA_Histo);
//	sum8_2e2mu_PidVA->SetMaximum(0.012);
	sum8_2e2mu_PidVA->SetTitle("2e2#mu, 8TeV");
	
	TH1F *sum8_2e2mu_ANA = (TH1F*)SM8_2e2mu_ANA_Histo->Clone("sum8_2e2mu_ANA");
	sum8_2e2mu_ANA->Add(PS8_2e2mu_ANA_Histo);
//	sum8_2e2mu_ANA->SetMaximum(0.012);
	sum8_2e2mu_ANA->SetTitle("2e2#mu, 8TeV");

	TH1F *sum8_2e2mu_qqbANA = (TH1F*)SM8_2e2mu_qqbANA_Histo->Clone("sum8_2e2mu_qqbANA");
	sum8_2e2mu_qqbANA->Add(PS8_2e2mu_qqbANA_Histo);
//	sum8_2e2mu_qqbANA->SetMaximum(0.012);
	sum8_2e2mu_qqbANA->SetTitle("2e2#mu, 8TeV");
	
	TH1F *sum8_2e2mu_PidANA = (TH1F*)SM8_2e2mu_PidANA_Histo->Clone("sum8_2e2mu_PidANA");
	sum8_2e2mu_PidANA->Add(PS8_2e2mu_PidANA_Histo);
//	sum8_2e2mu_PidANA->SetMaximum(0.012);
	sum8_2e2mu_PidANA->SetTitle("2e2#mu, 8TeV");
	
	
//	TH1F *sum7_4eAnd4mu = (TH1F*)SM7_4eAnd4muHisto->Clone("sum7_4eAnd4mu");
//	sum7_4eAnd4mu->Add(PS7_4eAnd4muHisto);
//	sum7_4eAnd4mu->SetMaximum(0.009);
//	sum7_4eAnd4mu->SetTitle("4e/4#mu, 7TeV");
//
//	TH1F *sum8_4eAnd4mu = (TH1F*)SM8_4eAnd4muHisto->Clone("sum8_4eAnd4mu");
//	sum8_4eAnd4mu->Add(PS8_4eAnd4muHisto);
//	sum8_4eAnd4mu->SetMaximum(0.009);
//	sum8_4eAnd4mu->SetTitle("4e/4#mu, 8TeV");

	
///////////////
// Cosmetics //
///////////////
	
//	sum7_2e2mu->SetFillColor(kAzure+7);
//	sum7_2e2mu->SetLineColor(kAzure+7);
//	sum7_2e2mu->GetXaxis()->SetTitle("ln(ME_{signal}/ME_{alt signal})");
//	sum7_2e2mu->GetYaxis()->SetTitle("# of events");
	
	sum8_2e2mu_VA->SetFillColor(kAzure+7);
	sum8_2e2mu_VA->SetLineColor(kAzure+7);
	sum8_2e2mu_VA->GetXaxis()->SetTitle("VA: ln(ME_{signal}/ME_{gg alt. signal})");
	sum8_2e2mu_VA->GetYaxis()->SetTitle("# of events");

	sum8_2e2mu_qqbVA->SetFillColor(kAzure+7);
	sum8_2e2mu_qqbVA->SetLineColor(kAzure+7);
	sum8_2e2mu_qqbVA->GetXaxis()->SetTitle("VA: ln(ME_{signal}/ME_{qqb alt. signal})");
	sum8_2e2mu_qqbVA->GetYaxis()->SetTitle("# of events");
	
	sum8_2e2mu_PidVA->SetFillColor(kAzure+7);
	sum8_2e2mu_PidVA->SetLineColor(kAzure+7);
	sum8_2e2mu_PidVA->GetXaxis()->SetTitle("VA: ln(ME_{signal}/ME_{pid alt. signal})");
	sum8_2e2mu_PidVA->GetYaxis()->SetTitle("# of events");
	
	sum8_2e2mu_ANA->SetFillColor(kAzure+7);
	sum8_2e2mu_ANA->SetLineColor(kAzure+7);
	sum8_2e2mu_ANA->GetXaxis()->SetTitle("ANA: ln(ME_{signal}/ME_{gg alt. signal})");
	sum8_2e2mu_ANA->GetYaxis()->SetTitle("# of events");

	sum8_2e2mu_qqbANA->SetFillColor(kAzure+7);
	sum8_2e2mu_qqbANA->SetLineColor(kAzure+7);
	sum8_2e2mu_qqbANA->GetXaxis()->SetTitle("ANA: ln(ME_{signal}/ME_{qqb alt. signal})");
	sum8_2e2mu_qqbANA->GetYaxis()->SetTitle("# of events");
	
	sum8_2e2mu_PidANA->SetFillColor(kAzure+7);
	sum8_2e2mu_PidANA->SetLineColor(kAzure+7);
	sum8_2e2mu_PidANA->GetXaxis()->SetTitle("ANA: ln(ME_{signal}/ME_{pid alt. signal})");
	sum8_2e2mu_PidANA->GetYaxis()->SetTitle("# of events");
	
//	sum7_4eAnd4mu->SetFillColor(kAzure+7);
//	sum7_4eAnd4mu->SetLineColor(kAzure+7);
//	sum7_4eAnd4mu->GetXaxis()->SetTitle("ln(ME_{signal}/ME_{alt signal})");
//	sum7_4eAnd4mu->GetYaxis()->SetTitle("# of events");
	
//	sum8_4eAnd4mu->SetFillColor(kAzure+7);
//	sum8_4eAnd4mu->SetLineColor(kAzure+7);
//	sum8_4eAnd4mu->GetXaxis()->SetTitle("ln(ME_{signal}/ME_{alt signal})");
//	sum8_4eAnd4mu->GetYaxis()->SetTitle("# of events");

//	SM7_2e2muHisto->SetLineColor(kOrange+1);
//	SM7_2e2muHisto->SetFillColor(kOrange+1);
//	PS7_2e2muHisto->SetLineColor(kTeal-7);
//	PS7_2e2muHisto->SetFillColor(kTeal-7);
	
	SM8_2e2mu_VA_Histo->SetLineColor(kOrange+1);
	SM8_2e2mu_VA_Histo->SetFillColor(kOrange+1);
	
	SM8_2e2mu_qqbVA_Histo->SetLineColor(kOrange+1);
	SM8_2e2mu_qqbVA_Histo->SetFillColor(kOrange+1);
	
	SM8_2e2mu_PidVA_Histo->SetLineColor(kOrange+1);
	SM8_2e2mu_PidVA_Histo->SetFillColor(kOrange+1);
	
	SM8_2e2mu_ANA_Histo->SetLineColor(kOrange+1);
	SM8_2e2mu_ANA_Histo->SetFillColor(kOrange+1);
	
	SM8_2e2mu_qqbANA_Histo->SetLineColor(kOrange+1);
	SM8_2e2mu_qqbANA_Histo->SetFillColor(kOrange+1);
	
	SM8_2e2mu_PidANA_Histo->SetLineColor(kOrange+1);
	SM8_2e2mu_PidANA_Histo->SetFillColor(kOrange+1);
	
	PS8_2e2mu_VA_Histo->SetLineColor(kTeal-7);
	PS8_2e2mu_VA_Histo->SetFillColor(kTeal-7);
	
	PS8_2e2mu_qqbVA_Histo->SetLineColor(kTeal-7);
	PS8_2e2mu_qqbVA_Histo->SetFillColor(kTeal-7);
	
	PS8_2e2mu_PidVA_Histo->SetLineColor(kTeal-7);
	PS8_2e2mu_PidVA_Histo->SetFillColor(kTeal-7);
	
	PS8_2e2mu_ANA_Histo->SetLineColor(kTeal-7);
	PS8_2e2mu_ANA_Histo->SetFillColor(kTeal-7);
	
	PS8_2e2mu_qqbANA_Histo->SetLineColor(kTeal-7);
	PS8_2e2mu_qqbANA_Histo->SetFillColor(kTeal-7);
	
	PS8_2e2mu_PidANA_Histo->SetLineColor(kTeal-7);
	PS8_2e2mu_PidANA_Histo->SetFillColor(kTeal-7);
	
//	SM7_4eAnd4muHisto->SetLineColor(kOrange+1);
//	SM7_4eAnd4muHisto->SetFillColor(kOrange+1);
//	PS7_4eAnd4muHisto->SetLineColor(kTeal-7);
//	PS7_4eAnd4muHisto->SetFillColor(kTeal-7);
	
//	SM8_4eAnd4muHisto->SetLineColor(kOrange+1);
//	SM8_4eAnd4muHisto->SetFillColor(kOrange+1);
//	PS8_4eAnd4muHisto->SetLineColor(kTeal-7);
//	PS8_4eAnd4muHisto->SetFillColor(kTeal-7);

//	Double_t median7_2e2mu = median(sum7_2e2mu);
	Double_t median8_2e2mu_VA = median(sum8_2e2mu_VA);
	Double_t median8_2e2mu_qqbVA = median(sum8_2e2mu_qqbVA);
	Double_t median8_2e2mu_PidVA = median(sum8_2e2mu_PidVA);
	Double_t median8_2e2mu_ANA = median(sum8_2e2mu_ANA);
	Double_t median8_2e2mu_qqbANA = median(sum8_2e2mu_qqbANA);
	Double_t median8_2e2mu_PidANA = median(sum8_2e2mu_PidANA);
//	Double_t median7_4eAnd4mu = median(sum7_4eAnd4mu);
//	Double_t median8_4eAnd4mu = median(sum8_4eAnd4mu);

//	TLine *line1 = new TLine(median7_2e2mu, 0, median7_2e2mu, sum7_2e2mu->GetMaximum());
//	line1->SetLineWidth(2);
	
	TLine *line2_VA = new TLine(median8_2e2mu_VA, 0, median8_2e2mu_VA, sum8_2e2mu_VA->GetMaximum());
	line2_VA->SetLineWidth(2);

	TLine *line2_qqbVA = new TLine(median8_2e2mu_qqbVA, 0, median8_2e2mu_qqbVA, sum8_2e2mu_qqbVA->GetMaximum());
	line2_qqbVA->SetLineWidth(2);
	
	TLine *line2_PidVA = new TLine(median8_2e2mu_PidVA, 0, median8_2e2mu_PidVA, sum8_2e2mu_PidVA->GetMaximum());
	line2_PidVA->SetLineWidth(2);
	
	TLine *line2_ANA = new TLine(median8_2e2mu_ANA, 0, median8_2e2mu_ANA, sum8_2e2mu_ANA->GetMaximum());
	line2_ANA->SetLineWidth(2);
	
	TLine *line2_qqbANA = new TLine(median8_2e2mu_qqbANA, 0, median8_2e2mu_qqbANA, sum8_2e2mu_qqbANA->GetMaximum());
	line2_qqbANA->SetLineWidth(2);
	
	TLine *line2_PidANA = new TLine(median8_2e2mu_PidANA, 0, median8_2e2mu_PidANA, sum8_2e2mu_PidANA->GetMaximum());
	line2_PidANA->SetLineWidth(2);

//	TLine *line3 = new TLine(median7_4eAnd4mu, 0, median7_4eAnd4mu, sum7_4eAnd4mu->GetMaximum());
//	line3->SetLineWidth(2);

//	TLine *line4 = new TLine(median8_4eAnd4mu, 0, median8_4eAnd4mu, sum8_4eAnd4mu->GetMaximum());
//	line4->SetLineWidth(2);

	
	
//	TPaveText *info = new TPaveText( 0.7, 0.7, 0.9, 0.9, "brNDC" );
//	info->SetBorderSize(0);
//	info->SetTextAlign(12);
//	info->SetFillStyle(0);
//	info->SetTextFont(42);
//	info->SetTextSize(0.03);
//	TText *text = info->AddText(0.01, 0.5, "CMS preliminary");
//	text = pt->AddText(0.3,0.6,"#sqrt{s} = 7 TeV, L = 5.1 fb^{-1}  #sqrt{s} = 8 TeV, L = 19.6 fb^{-1}");
//	pt->Draw();

	TCanvas *c8_2e2mu = new TCanvas( "can", "can", 900, 400 );
	TCanvas *c8_2e2mu_qqb = new TCanvas( "can", "can", 900, 400 );
	TCanvas *c8_2e2mu_pid = new TCanvas( "can", "can", 900, 400 );

	c8_2e2mu->Divide(1,2);
	c8_2e2mu_qqb->Divide(1,2);
	c8_2e2mu_pid->Divide(1,2);
	
//	can->cd(1);
//	sum7_2e2mu->Draw("LF2");
//	SM7_2e2muHisto->Draw("same");
//	PS7_2e2muHisto->Draw("same");
//	line1->Draw("same");

// gg
	c8_2e2mu->cd();
	
	c8_2e2mu->cd(1);
	sum8_2e2mu_VA->Draw();
	SM8_2e2mu_VA_Histo->Draw("same");
	PS8_2e2mu_VA_Histo->Draw("same");
	line2_VA->Draw("same");
	
	c8_2e2mu->cd(2);
	sum8_2e2mu_ANA->Draw();
	SM8_2e2mu_ANA_Histo->Draw("same");
	PS8_2e2mu_ANA_Histo->Draw("same");
	line2_ANA->Draw("same");
	
// qqb
	c8_2e2mu_qqb->cd();
	
	c8_2e2mu_qqb->cd(1);
	sum8_2e2mu_qqbVA->Draw();
	SM8_2e2mu_qqbVA_Histo->Draw("same");
	PS8_2e2mu_qqbVA_Histo->Draw("same");
	line2_qqbVA->Draw("same");
	
	c8_2e2mu_qqb->cd(1);
	sum8_2e2mu_qqbANA->Draw();
	SM8_2e2mu_qqbANA_Histo->Draw("same");
	PS8_2e2mu_qqbANA_Histo->Draw("same");
	line2_qqbANA->Draw("same");

// pid
	c8_2e2mu_pid->cd();
	
	c8_2e2mu_pid->cd(1);
	sum8_2e2mu_PidVA->Draw();
	SM8_2e2mu_PidVA_Histo->Draw("same");
	PS8_2e2mu_PidVA_Histo->Draw("same");
	line2_PidVA->Draw("same");
	
	c8_2e2mu_pid->cd(1);
	sum8_2e2mu_PidANA->Draw();
	SM8_2e2mu_PidANA_Histo->Draw("same");
	PS8_2e2mu_PidANA_Histo->Draw("same");
	line2_PidANA->Draw("same");
	
	
//	can->cd(3);
//	sum7_4eAnd4mu->Draw();
//	SM7_4eAnd4muHisto->Draw("same");
//	PS7_4eAnd4muHisto->Draw("same");
//	line3->Draw("same");

//	can->cd(4);
//	sum8_4eAnd4mu->Draw();
//	SM8_4eAnd4muHisto->Draw("same");
//	PS8_4eAnd4muHisto->Draw("same");
//	line4->Draw("same");

	
	c8_2e2mu->SaveAs(saveString + "/gg_" + saveTag[myModel] + ".pdf");
	c8_2e2mu_qqb->SaveAs(saveString + "/qqb_" + saveTag[myModel] + ".pdf");
	c8_2e2mu_pid->SaveAs(saveString + "/pid_" + saveTag[myModel] + ".pdf");
	
//	cout << "7TeV, 2e2mu, median = " << median7_2e2mu << endl;
//	cout << "7TeV, 2e2mu, c = " << exp(median7_2e2mu) << endl;

	cout << saveTag[myModel] << endl;
//	cout << "8TeV, 2e2mu, VA median = " << median8_2e2mu_VA << endl;
	cout << "8TeV, 2e2mu, VA c = " << exp(median8_2e2mu_VA) << endl;
//	cout << "8TeV, 2e2mu, qqbVA median = " << median8_2e2mu_qqbVA << endl;
	cout << "8TeV, 2e2mu, qqbVA c = " << exp(median8_2e2mu_qqbVA) << endl;
//	cout << "8TeV, 2e2mu, PidVA median = " << median8_2e2mu_PidVA << endl;
	cout << "8TeV, 2e2mu, PidVA c = " << exp(median8_2e2mu_PidVA) << endl;
//	cout << "8TeV, 2e2mu, ANA median = " << median8_2e2mu_ANA << endl;
	cout << "8TeV, 2e2mu, ANA c = " << exp(median8_2e2mu_ANA) << endl;
//	cout << "8TeV, 2e2mu, qqbANA median = " << median8_2e2mu_qqbANA << endl;
	cout << "8TeV, 2e2mu, qqbANA c = " << exp(median8_2e2mu_qqbANA) << endl;
//	cout << "8TeV, 2e2mu, PidANA median = " << median8_2e2mu_PidANA << endl;
	cout << "8TeV, 2e2mu, PidANA c = " << exp(median8_2e2mu_PidANA) << endl;
	cout << endl;

//	cout << "7TeV, 4e/4mu, median = " << median7_4eAnd4mu << endl;
//	cout << "7TeV, 4e/4mu, c = " << exp(median7_4eAnd4mu) << endl;
//	cout << "8TeV, 4e/4mu, median = " << median8_4eAnd4mu << endl;
//	cout << "8TeV, 4e/4mu, c = " << exp(median8_4eAnd4mu) << endl;

//	delete sum7_2e2mu;
//	delete sum8_2e2mu;
//	delete sum7_4eAnd4mu;
//	delete sum8_4eAnd4mu;


//	TLegend *leg = new TLegend(.2,.65,.6,.9);
//	leg->SetFillColor(0);
//	leg->SetBorderSize(0);
//
//	leg->AddEntry(datahisto,"data","p");
//	leg->AddEntry(SMhisto,"0^{+}, m_{H}=126 GeV","l");
//	if(myModel!=0) leg->AddEntry(PShisto,legendTag[myModel]+", m_{H}=126 GeV","l");
//	leg->AddEntry(qqZZhisto,"ZZ/Z#gamma^{*}","f");
//	leg->AddEntry(ZXhisto,"Z+X","f");
//
//	leg->Draw();
//
//	datahisto->Draw("E1same");
//	gPad->RedrawAxis();

}

Double_t median( TH1F *h1 )
{
// Compute the median for 1-d histogram h1
   Int_t nbins = h1->GetXaxis()->GetNbins();
   Double_t *x = new Double_t[nbins];
   Double_t *y = new Double_t[nbins];

	for (Int_t i = 0; i < nbins; i++)
	{
      x[i] = h1->GetXaxis()->GetBinCenter(i+1);
      y[i] = h1->GetBinContent(i+1);
   }
	
   Double_t median = TMath::Median(nbins,x,y);
   delete x;
   delete y;
   return median;
}


void tuneConstant(){

	for ( model i = 0; i < model::numOfModels; i++)
	{
		doCalculation(i);
	}
}