// ROOT includes
#include "TFile.h"
#include "TStyle.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TString.h"
#include "TPaveText.h"
#include "TText.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TSystem.h"
#include "TLegend.h"

// C++ includes
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>

// Parameters to be changed by the user
bool tuned = 1;
bool is_gg = 0;

// mkdir commands
TString mkdirMinusP = "mkdir -p ";
TString mkdir = "mkdir ";

// Models
enum models { p2mPlus, p2bPlus, p2hPlus, p2h2Plus, p2h3Plus, p2h6Plus, p2h7Plus, p2hMinus, p2h9Minus, p2h10minus, numOfModels };

// Channels
TString channel[3] = { "4e", "4mu", "2e2mu" };

TString sample_gg[10] =
{
	"HZZ4lTree_jhuGenV3GravPMH126",
	"HZZ4lTree_jhuGenV3Grav2PBH126",
	"HZZ4lTree_jhuGenV3Grav2PHH126",
	"Graviton2PH2ToZZTo4L_M-125p6_8TeV-JHUGenV3_false",
	"Graviton2PH3ToZZTo4L_M-125p6_8TeV-JHUGenV3_false",
	"Graviton2PH6ToZZTo4L_M-125p6_8TeV-JHUGenV3_false",
	"Graviton2PH7ToZZTo4L_M-125p6_8TeV-JHUGenV3_false",
	"HZZ4lTree_jhuGenV3Grav2MHH126",
	"Graviton2MH9ToZZTo4L_M-125p6_8TeV-JHUGenV3_false",
	"Graviton2MH10ToZZTo4L_M-125p6_8TeV-JHUGenV3_false"
};

TString sample_qqb[10] =
{
	"HZZ4lTree_jhuGenV3qqGravH126",
	"qqbar_Graviton2BPToZZTo4L_M-125p6_8TeV-JHUGenV3_false",
	"qqbar_Graviton2HPToZZTo4L_M-125p6_8TeV-JHUGenV3_false",
	"qqbar_Graviton2PH2ToZZTo4L_M-125p6_8TeV-JHUGenV3_false",
	"qqbar_Graviton2PH3ToZZTo4L_M-125p6_8TeV-JHUGenV3_false",
	"qqbar_Graviton2PH6ToZZTo4L_M-125p6_8TeV-JHUGenV3_false",
	"qqbar_Graviton2PH7ToZZTo4L_M-125p6_8TeV-JHUGenV3_false",
	"qqbar_Graviton2HMToZZTo4L_M-125p6_8TeV-JHUGenV3_false",
	"qqbar_Graviton2MH9ToZZTo4L_M-125p6_8TeV-JHUGenV3_false",
	"qqbar_Graviton2MH10ToZZTo4L_M-125p6_8TeV-JHUGenV3_false"
};

TString legendLabel[10] =
{
	"J^{P} = 2^{+}_{m}",
	"J^{P} = 2^{+}_{b}",
	"J^{P} = 2^{+}_{h}",
	"J^{P} = 2^{+}_{h 2}",
	"J^{P} = 2^{+}_{h 3}",
	"J^{P} = 2^{+}_{h 6}",
	"J^{P} = 2^{+}_{h 7}",
	"J^{P} = 2^{-}_{h}",
	"J^{P} = 2^{-}_{h 9}",
	"J^{P} = 2^{-}_{h 10}"
};

TString legendLabel_pid[10] =
{
   "J^{P} = 2^{+}_{m} dec",
   "J^{P} = 2^{+}_{b} dec",
	"J^{P} = 2^{+}_{h} dec",
	"J^{P} = 2^{+}_{h 2} dec",
	"J^{P} = 2^{+}_{h 3} dec",
	"J^{P} = 2^{+}_{h 6} dec",
	"J^{P} = 2^{+}_{h 7} dec",
	"J^{P} = 2^{-}_{h} dec",
	"J^{P} = 2^{-}_{h 9} dec",
	"J^{P} = 2^{-}_{h 10} dec"
};

TString ALT_variable_gg[10] =
{
	"p2mplus",
	"p2bplus",
	"p2hplus",
	"p2h2plus",
	"p2h3plus",
	"p2h6plus",
	"p2h7plus",
	"p2hminus",
	"p2h9minus",
	"p2h10minus"
};

TString ALT_variable_qqb[10] =
{
	"p2mplus_qqb",
	"p2bplus_qqb",
	"p2hplus_qqb",
	"p2h2plus_qqb",
	"p2h3plus_qqb",
	"p2h6plus_qqb",
	"p2h7plus_qqb",
	"p2hminus_qqb",
	"p2h9minus_qqb",
	"p2h10minus_qqb"
};

TString ALT_variablePid[10] =
{
	"p2mplusPid",
	"p2bplusPid",
	"p2hplusPid",
	"p2h2plusPid",
	"p2h3plusPid",
	"p2h6plusPid",
	"p2h7plusPid",
	"p2hminusPid",
	"p2h9minusPid",
	"p2h10minusPid"
};


using namespace std;

//=========================
void plot( models myModel )
{
	TString sample[10];
	TString ALT_variable[10];
	TString usedSample;
	
	for ( int k = 0; k < 10; k++ )
	{
		sample[k] = ( is_gg ? sample_gg[k] : sample_qqb[k] );
		ALT_variable[k] = ( is_gg ? ALT_variable_gg[k] : ALT_variable_qqb[k] );
	}
	
	usedSample = ( is_gg ? "GG" : "QQB" );
//	cout << endl << ALT_variable[2] << endl << endl;

	// Set environment
	if ( tuned )
	{
		TString filePath8TeV = "/home/llr/cms/kovac/CMS/Analysis/SpinParity/Validation/CMSSW_5_3_9/src/ZZMatrixElement/MELA/test/Validation/output-trees/8TeV/tuned/no-cuts/";
		TString plots = "plots/8TeV/tuned/no-cuts/";
      
      cout << "[INFO] Creating directory for plots..." << endl;
      gSystem->Exec( mkdirMinusP + plots );
      for ( int dir = 0; dir < 3; dir++  )
      {
         gSystem->Exec( mkdir + plots + channel[k] );
      }
      
      const int n = 100;
		float mzz_low = 120.;
		float mzz_high = 130.;
		float low = 0;
   }
	else
	{
		TString filePath8TeV = "/home/llr/cms/kovac/CMS/Analysis/SpinParity/MELA/CMSSW_5_3_9/src/ZZMatrixElement/MELA/test/outputTreesNoTuning/8TeV";
		TString plots = "plots";
		
		const int n = 50000;
		float mzz_low = 120.;
		float mzz_high = 130.;
		float low = 0.99999;
	}
	
	float mzz, w = 0;
	float psigM4l, pbkgM4l;
	float p0plus_VA, p0plus_ANA, pALT_VA, pALT_PidVA, pALT_ANA, pALT_PidANA;
	double SM_JHUGenKD, AltJHUGenKD, SM_AnaKD, AltAnaKD;
	double SM_JHUGenPidKD, AltJHUGenPidKD, SM_AnaPidKD, AltAnaPidKD;

	// Arrays for Graphing
	float SM_JHUGenKD_Eff[n], AltJHUGenKD_Eff[n], SM_AnaKD_Eff[n], AltAnaKD_Eff[n];
	float SM_JHUGenPidKD_Eff[n], AltJHUGenPidKD_Eff[n], SM_AnaPidKD_Eff[n], AltAnaPidKD_Eff[n];
	
	for ( int c = 2; c < 3; c++ )
	{

		// TChains
		TChain* tSM = new TChain("SelectedTree");
      TChain* tALT = new TChain("SelectedTree");
//		TChain* tBKG = new TChain("SelectedTree");
		
		// Add files to TChains
		if ( (is_gg && (myModel == 0 || myModel == 1 || myModel == 2 || myModel == 7)) || (!is_gg && myModel == 0) )
			tSM->Add(filePath8TeV  + "/" + channel[c] + "/HZZ4lTree_powheg15jhuGenV3H126.root");
		else
			tSM->Add(filePath8TeV  + "/" + channel[c] + "/ggtoHtoZZ4l_VariousKDs_0+m.root");
		
		tALT->Add(filePath8TeV + "/" + channel[c] + "/" + sample[myModel] + ".root");
//		tBKG->Add(filePath8TeV + "/" + channel[c] + "/HZZ4lTree_ZZTo*.root");
//		tBKG->Add(filePath8TeV + "/" + channel[c] + "/HZZZ4lTree_ggZZ*.root");
	
//		cout << filePath8TeV + "/" + channel[c] + "/" + sample[myModel] + "_MELA.root" << endl;

		// Connect variables
		tSM->SetBranchAddress("ZZMass",	   &mzz);
		tSM->SetBranchAddress("p0plus_VA",  &p0plus_VA);
		tSM->SetBranchAddress("p0plus_ANA", &p0plus_ANA);
		tSM->SetBranchAddress(ALT_variable[myModel] + "_VA",  &pALT_VA);
		tSM->SetBranchAddress(ALT_variable[myModel] + "_ANA", &pALT_ANA);
		tSM->SetBranchAddress(ALT_variablePid[myModel] + "_VA",  &pALT_PidVA);
		tSM->SetBranchAddress(ALT_variablePid[myModel] + "_ANA", &pALT_PidANA);
	
//		cout << ALT_variable[myModel] + "_VA" << endl;

		tALT->SetBranchAddress("ZZMass",		  &mzz);
		tALT->SetBranchAddress("p0plus_VA",   &p0plus_VA);
		tALT->SetBranchAddress("p0plus_ANA",  &p0plus_ANA);
		tALT->SetBranchAddress(ALT_variable[myModel] + "_VA",  &pALT_VA);
		tALT->SetBranchAddress(ALT_variable[myModel] + "_ANA", &pALT_ANA);
		tALT->SetBranchAddress(ALT_variablePid[myModel] + "_VA",  &pALT_PidVA);
		tALT->SetBranchAddress(ALT_variablePid[myModel] + "_ANA", &pALT_PidANA);
		
//		tBKG->SetBranchAddress("p0plus_VA",   &p0plus_VA);
//		tBKG->SetBranchAddress("p2hplus_VA",  &p2hplus_VA);
//		tBKG->SetBranchAddress("p0plus_ANA",  &p0plus_ANA);
//		tBKG->SetBranchAddress("p2hplus_ANA", &p2hplus_ANA);

		TH1F* hSM_KD_VA  = new TH1F("SM JHUGen KD", "SM JHUGen KD",           n, low, 1.); // 0.99999
		TH1F* hSM_KD_ANA = new TH1F("SM Analytical KD", "SM Analytical KD",   n, low, 1.);
		TH1F* hAltKD_VA  = new TH1F("Alt JHUGen KD", "Alt JHUGen KD",         n, low, 1.);
		TH1F* hAltKD_ANA = new TH1F("Alt Analytical KD", "Alt Analytical KD", n, low, 1.);
		TH1F* hSM_PidKD_VA  = new TH1F("SM JHUGen PidKD", "SM JHUGen PidKD",           n, low, 1.); // 0.99999
		TH1F* hSM_PidKD_ANA = new TH1F("SM Analytical PidKD", "SM Analytical PidKD",   n, low, 1.);
		TH1F* hAltPidKD_VA  = new TH1F("Alt JHUGen PidKD", "Alt JHUGen PidKD",         n, low, 1.);
		TH1F* hAltPidKD_ANA = new TH1F("Alt Analytical PidKD", "Alt Analytical PidKD", n, low, 1.);
		
//		TH1F* ALT_std = new TH1F("ALT pdALTD","ALT_pdALTD",n,0.,1.01);
//		TH1F* SM_pi = new TH1F("SM piALTD","SM_piALTD",n,0.,1.01);
//		TH1F* ALT_pi = new TH1F("ALT piALTD","SM_piALTD",n,0.,1.01);
//		TH1F* SM_skd = new TH1F("SM pdSKD","SM_pdSKD",n,0.,1.01);
//		TH1F* SM_PIskd = new TH1F("SM piSKD","SM_piSKD",n,0.,1.01);
//		TH1F* BKG_skd = new TH1F("BKG pdSKD","BKG_pdSKD",n,0.,1.01);
//		TH1F* BKG_PIskd = new TH1F("BKG piSKD","BKG_piSKD",n,0.,1.01);


		// Fill SM KD
		for ( int i = 0; i < tSM->GetEntries(); i++ )
		{
			tSM->GetEntry(i);
			
			if ( mzz < mzz_low || mzz > mzz_high )
			{
				continue;
			}
			
//			cout << "Got SM" << endl << pALT_VA << endl;
			
			SM_JHUGenKD    = (p0plus_VA)/(p0plus_VA   + pALT_VA);
			SM_AnaKD       = (p0plus_ANA)/(p0plus_ANA + pALT_ANA);
			SM_JHUGenPidKD = (p0plus_VA)/(p0plus_VA   + pALT_PidVA);
			SM_AnaPidKD    = (p0plus_ANA)/(p0plus_ANA + pALT_PidANA);
			
			hSM_KD_VA->Fill(SM_JHUGenKD);
			hSM_KD_ANA->Fill(SM_AnaKD);
			hSM_PidKD_VA->Fill(SM_JHUGenPidKD);
			hSM_PidKD_ANA->Fill(SM_AnaPidKD);
			
//			cout.precision(12);
//			cout << SM_JHUGenKD << endl;
		}


		// Fill Alternative KD
		for ( int i = 0; i < tALT->GetEntries(); i++ )
		{
			tALT->GetEntry(i);
			
			if ( mzz < mzz_low || mzz > mzz_high )
			{
				continue;
			}
			
//			cout << "Got ALT" << endl << pALT_VA << endl;
			
			AltJHUGenKD    = (p0plus_VA)/(p0plus_VA   + pALT_VA);
			AltAnaKD       = (p0plus_ANA)/(p0plus_ANA + pALT_ANA);
			AltJHUGenPidKD = (p0plus_VA)/(p0plus_VA   + pALT_PidVA);
			AltAnaPidKD    = (p0plus_ANA)/(p0plus_ANA + pALT_PidANA);
			
			hAltKD_VA->Fill(AltJHUGenKD);
			hAltKD_ANA->Fill(AltAnaKD);
			hAltPidKD_VA->Fill(AltJHUGenPidKD);
			hAltPidKD_ANA->Fill(AltAnaPidKD);
		}

		// Scale
		hAltKD_VA->Scale(1./hAltKD_VA->Integral());
		hAltKD_ANA->Scale(1./hAltKD_ANA->Integral());
		hSM_KD_VA->Scale(1./hSM_KD_VA->Integral());
		hSM_KD_ANA->Scale(1./hSM_KD_ANA->Integral());
		
		hAltPidKD_VA->Scale(1./hAltPidKD_VA->Integral());
		hAltPidKD_ANA->Scale(1./hAltPidKD_ANA->Integral());
		hSM_PidKD_VA->Scale(1./hSM_PidKD_VA->Integral());
		hSM_PidKD_ANA->Scale(1./hSM_PidKD_ANA->Integral());
		
//		hSM_KD_VA->Draw();

		
		// Calculate efficiency
		for ( int iCut = 1; iCut < n+1; iCut++ )
		{
//			cout << iCut << endl;
			
			SM_JHUGenKD_Eff[iCut-1] = hSM_KD_VA->Integral(iCut, n);
			SM_AnaKD_Eff[iCut-1]    = hSM_KD_ANA->Integral(iCut, n);
			AltJHUGenKD_Eff[iCut-1] = hAltKD_VA->Integral(iCut, n);
			AltAnaKD_Eff[iCut-1]    = hAltKD_ANA->Integral(iCut, n);
			
			SM_JHUGenPidKD_Eff[iCut-1] = hSM_PidKD_VA->Integral(iCut, n);
			SM_AnaPidKD_Eff[iCut-1]    = hSM_PidKD_ANA->Integral(iCut, n);
			AltJHUGenPidKD_Eff[iCut-1] = hAltPidKD_VA->Integral(iCut, n);
			AltAnaPidKD_Eff[iCut-1]    = hAltPidKD_ANA->Integral(iCut, n);
			
//			cout << "SM_JHUGenKD_Eff " << SM_JHUGenKD_Eff[iCut-1] << endl;
//			cout << "AltJHUGenKD_Eff " << AltJHUGenKD_Eff[iCut-1] << endl;
//			cout << "SM_AnaKD_Eff " << SM_AnaKD_Eff[iCut-1] << endl;
//			cout << "AltAnaKD_Eff " << AltAnaKD_Eff[iCut-1] << endl;
		}
		
		TCanvas* cROC_gg  = new TCanvas( usedSample + " ROC curves", usedSample + " ROC curves", 800, 800);
		TCanvas* cROC_pid = new TCanvas( usedSample + " pid ROC curves", usedSample + " pid ROC curves", 800, 800);
		TCanvas* cROC_all = new TCanvas( usedSample + " all ROC curves", usedSample + " all ROC curves", 800, 800);
      
		TMultiGraph *KD_Multi_gg = new TMultiGraph();
      KD_Multi_gg->SetTitle( usedSample + " KD ROC curves " + channel[c] + ";#epsilon_{  0^{+}}; #epsilon_{  " + legendLabel[myModel] + "}");

		TMultiGraph *KD_Multi_pid = new TMultiGraph();
      KD_Multi_pid->SetTitle( usedSample + " pid KD ROC curves " + channel[c] + ";#epsilon_{  0^{+}}; #epsilon_{  " + legendLabel_pid[myModel] + "}");

		TMultiGraph *KD_Multi_all = new TMultiGraph();
      KD_Multi_all->SetTitle( usedSample + " KD ROC curves " + channel[c] + ";#epsilon_{  0^{+}}; #epsilon_{  " + legendLabel_pid[myModel] + "}");
		
		
      TGraph *JHUGenKD_ROC = new TGraph(n, SM_JHUGenKD_Eff, AltJHUGenKD_Eff);
		JHUGenKD_ROC->SetLineColor(kOrange+7);
		JHUGenKD_ROC->SetLineWidth(2);
		JHUGenKD_ROC->SetMarkerColor(1);
      JHUGenKD_ROC->SetMarkerStyle(7);
		JHUGenKD_ROC->SetMinimum(0);
		JHUGenKD_ROC->SetMaximum(1);
      KD_Multi_gg->Add(JHUGenKD_ROC);
		
		TGraph* ANA_KD_ROC = new TGraph(n, SM_AnaKD_Eff, AltAnaKD_Eff);
      ANA_KD_ROC->SetLineColor(kBlue-7);
		ANA_KD_ROC->SetLineWidth(2);
		ANA_KD_ROC->SetLineStyle(7);
		ANA_KD_ROC->SetMarkerColor(1);
      ANA_KD_ROC->SetMarkerStyle(7);
		ANA_KD_ROC->SetMinimum(0);
		ANA_KD_ROC->SetMaximum(1);
      KD_Multi_gg->Add(ANA_KD_ROC);
		
		TGraph *JHUGenPidKD_ROC = new TGraph(n, SM_JHUGenPidKD_Eff, AltJHUGenPidKD_Eff);
		JHUGenPidKD_ROC->SetLineColor(kOrange+7);
		JHUGenPidKD_ROC->SetLineWidth(2);
		JHUGenPidKD_ROC->SetMarkerColor(1);
      JHUGenPidKD_ROC->SetMarkerStyle(7);
		JHUGenPidKD_ROC->SetMinimum(0);
		JHUGenPidKD_ROC->SetMaximum(1);
      KD_Multi_pid->Add(JHUGenPidKD_ROC);
		
		TGraph* ANA_PidKD_ROC = new TGraph(n, SM_AnaPidKD_Eff, AltAnaPidKD_Eff);
      ANA_PidKD_ROC->SetLineColor(kBlue-7);
		ANA_PidKD_ROC->SetLineWidth(2);
		ANA_PidKD_ROC->SetLineStyle(7);
		ANA_PidKD_ROC->SetMarkerColor(1);
      ANA_PidKD_ROC->SetMarkerStyle(7);
		ANA_PidKD_ROC->SetMinimum(0);
		ANA_PidKD_ROC->SetMaximum(1);
      KD_Multi_pid->Add(ANA_PidKD_ROC);

      TLegend* legend_gg = new TLegend(.2,.65,.5,.85);
		legend_gg->SetBorderSize(0);
      legend_gg->SetFillColor(0);
      legend_gg->AddEntry(JHUGenKD_ROC, "JHUGen MELA "   + channel[c], "l");
      legend_gg->AddEntry(ANA_KD_ROC, "Analytical MELA " + channel[c], "l");
		
		TLegend* legend_pid = new TLegend(.2,.65,.5,.85);
		legend_pid->SetBorderSize(0);
      legend_pid->SetFillColor(0);
      legend_pid->AddEntry(JHUGenPidKD_ROC, "JHUGen MELA "   + channel[c], "l");
      legend_pid->AddEntry(ANA_PidKD_ROC, "Analytical MELA " + channel[c], "l");
		
		
		cROC_gg->cd();
      KD_Multi_gg->Draw("ac");
		KD_Multi_gg->GetXaxis()->SetLimits(0., 1.);
		cROC_gg->Modified();
      legend_gg->Draw();
      cROC_gg->SaveAs(plots + channel[c] + "/" + usedSample + "_" + ALT_variable[myModel] + "_" + channel[c] + ".png");
		cROC_gg->SaveAs(plots + channel[c] + "/" + usedSample + "_" + ALT_variable[myModel] + "_" + channel[c] + ".pdf");
		
		cROC_pid->cd();
      KD_Multi_pid->Draw("ac");
		KD_Multi_pid->GetXaxis()->SetLimits(0., 1.);
		cROC_pid->Modified();
      legend_pid->Draw();
      cROC_pid->SaveAs(plots + channel[c] + "/" + usedSample + "_" + ALT_variablePid[myModel] + "_" + channel[c] + ".png");
		cROC_pid->SaveAs(plots + channel[c] + "/" + usedSample + "_" + ALT_variablePid[myModel] + "_" + channel[c] + ".pdf");

		
		// All ROC curves on one histo
		JHUGenPidKD_ROC->SetLineColor(kTeal-5);
		ANA_PidKD_ROC->SetLineColor(kRed-3);
		KD_Multi_all->Add(JHUGenKD_ROC);
		KD_Multi_all->Add(ANA_KD_ROC);
		KD_Multi_all->Add(JHUGenPidKD_ROC);
		KD_Multi_all->Add(ANA_PidKD_ROC);
		
		TLegend* legend_all = new TLegend(.2,.65,.5,.85);
      legend_all->SetFillColor(0);
		legend_all->SetBorderSize(0);
      legend_all->AddEntry(JHUGenKD_ROC, "JHUGen MELA "   + channel[c], "l");
      legend_all->AddEntry(ANA_KD_ROC, "Analytical MELA " + channel[c], "l");
      legend_all->AddEntry(JHUGenPidKD_ROC, "PID JHUGen MELA "   + channel[c], "l");
      legend_all->AddEntry(ANA_PidKD_ROC, "PID Analytical MELA " + channel[c], "l");
		
      cROC_all->cd();
      KD_Multi_all->Draw("ac");
      KD_Multi_all->GetXaxis()->SetLimits(0., 1.);
		cROC_all->Modified();
      legend_all->Draw();
      cROC_all->SaveAs(plots + channel[c] + "/" + usedSample + "_" + ALT_variable[myModel] + "_all_" + channel[c] + ".png");
      cROC_all->SaveAs(plots + channel[c] + "/" + usedSample + "_" + ALT_variable[myModel] + "_all_" + channel[c] + ".pdf");
		
      delete hSM_KD_ANA;
      delete hSM_KD_VA;
      delete hAltKD_ANA;
      delete hAltKD_VA;
      delete hSM_PidKD_ANA;
      delete hSM_PidKD_VA;
      delete hAltPidKD_ANA;
      delete hAltPidKD_VA;
 
	} // End for channel
} // End main
//=========================



//============
void plotROC()
{
	for ( int i = 0; i < models::numOfModels; i++ )
//	for ( int i = 6; i < 7; i++ )
	{
		plot(i);
	}
}
//===========