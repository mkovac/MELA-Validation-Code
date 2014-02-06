// C++
#include <iostream>
#include <fstream>
#include <string>

// ROOT
#include "TApplication.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include "TStyle.h"

// My own files
#include "../include/StdArg.hpp"
#include "../include/addProbToTree.hpp"

using namespace std;

void Usage( const char* exename )
{
	cout << endl << "Usage : ./start -debug -limitStat -fileList <files.txt> -out <output.root> -channel <2e2mu/4e/4mu>" << endl;
}

int main( int argc, char *argv[] )
{
  
////////////////////////////////////////////
// Retrieving arguments from command line //
////////////////////////////////////////////

	StdArg arg( argc, argv ); // Call constructor
 
	cout << "======================================================================" << endl;
	for ( int i = 0; i < argc; i++ )
		cout << argv[i] << " ";
		cout << endl;
   cout << "======================================================================" << endl;
   
// Enter all possible flags:
	arg.flags << "-debug" << "-limitStat" << "-interactive";
	
// Enter all possible keys:
	arg.keys << "-fileList" << "-out" << "-channel";

	bool limitStat   = false;
   bool debug       = false;
	bool interactive = false;

	string input   = "data.list";
	string output  = "output.root";
	string channel = "2e2mu";

// Parse command line
	try
	{
      arg.Process();
		debug       = arg.Flag( "-debug" )       ? true: false;
		limitStat   = arg.Flag( "-limitStat" )   ? true: false;
		interactive = arg.Flag( "-interactive" ) ? true: false;
		
		if( arg.Key("-fileList") ) input   = arg.Get<string>( "-fileList" );
		if( arg.Key("-out")      ) output  = arg.Get<string>( "-out"      );
		if( arg.Key("-channel")  ) channel = arg.Get<string>( "-channel"  );
	}
	
	catch ( StdArg::BadInput )
   {
		if (argc > 1) cout << "Input error" << endl;
		// usage in case of error or no parameters
		Usage(argv[0]);
		return 1;
   }
  
/////////////////////
// Load ROOT files //
/////////////////////
	
	TString treeName = "SelectedTree";
	TChain *tree = new TChain( treeName );
   
	if ( interactive )
	{
		TString szROOTFileName = input.c_str();
		if ( tree->Add(szROOTFileName.Data()) )
			cout << "[INFO]: File '" << szROOTFileName << "' has been loaded!" << endl;
		else cout << "[ERROR]: Can't load file '" << szROOTFileName << "'" << endl;
	}
	else
	{
		string szLineFromListOfFiles;

		TString szListOfFiles = input.c_str(); //Contains path to .txt file with list of .root files
		cout << "[INFO]: Load TChain from file: " << szListOfFiles << endl;
		
	// To open .txt file with list of .root files
		ifstream inputROOTFiles(szListOfFiles.Data());
		
		if( !inputROOTFiles )
		{
			cout << "[ERROR]: Can't open file " << szListOfFiles << endl;
			return 1;
		} // end if
	  
		while( getline( inputROOTFiles, szLineFromListOfFiles ))
		{		
			TString szROOTFileName = szLineFromListOfFiles;
		 
			if ( tree->Add(szROOTFileName.Data()) )
				cout << "[INFO]: File '" << szROOTFileName << "' has been loaded!" << endl;
			else cout << "[ERROR]: Can't load file '" << szROOTFileName << "'" << endl;
		} // end while
		inputROOTFiles.close();
	}

	cout << "======================================================================" << endl;
	cout << "Total Number of events = "  << tree->GetEntries() << endl;
	cout << "======================================================================" << endl;
   
	
	cout << "=====================" << endl;
	cout << "Running production..." << endl;
	cout << "=====================" << endl;

	
///////////////
// Launch... //
///////////////

	addProbToTree addMela( tree, channel, limitStat, output);
	addMela.Loop();
	return 0;
}