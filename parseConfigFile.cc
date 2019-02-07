//Vishal Madipadga
//CS3377.501
//vrm160030@utdallas.edu
#include <iostream>
#include <fstream>
#include <rude/config.h>
#include "program5.h"
#include <stdlib.h>
using namespace std;

//function to parse config file
void parseCF(bool set )
{
//delcaring a config object
 rude::Config config;
 //getting the path for home directory using getenv
 char const* path = getenv( "HOME" );
 //turning path into string
 string s(path);
 string verbose;
 //getting rest of path
 string program = "/Program5/";
 //getting configuration file from map
 string confFile = commandLine[CONFIGFILE];
 //setting comment value
 char commentchar = '#';
 config.setCommentCharacter(commentchar);
 //appending paths to get directory to configfile
 string directory = s + program + confFile;
 //load config file
 if (config.load(directory.c_str() ))
   { 
   //set section 
    config.setSection("Parameters" );
    //check if verbose definiton doesn't exist
    
     if(!config.exists("Verbose"))
       {
         cout << "Verbose definition does not exist "<< endl;
	 exit (EXIT_FAILURE );
       }
       //if it exists
      else
      {
      //get its value and put it in map
	bool verboseVal = config.getBoolValue("Verbose" );
	if(verboseVal)
	{
	 verbose = "TRUE";
	}
	else 
	{
	 verbose = "FALSE";
	}
	commandLine.insert(pair<int, string> (VERBOSE, verbose ));
	if(set == true)
	{
         outfile << verbose << endl;
	}
      }
      
   
      //check if log file doesn't exist
     if(!config.exists("LogFile"))
     {
	cout << "LogFile does not exist  " << endl;
	 exit (EXIT_FAILURE );

     }
     //if log file exists put it into map
     else
     {
	string logFile = config.getStringValue("LogFile" );
	commandLine.insert(pair<int, string > (LOGFILE, logFile ) );

     }
     //check if boolean passed i
     if(set == false)
     {
       if(!config.exists("Password" ))
        {
	  cout << "Password definition does not exist " << endl;
	  exit (EXIT_FAILURE );

        }
       else
        {
	  string password = config.getStringValue("Password" );
	  commandLine.insert(pair<int, string > (PASSWORD, password ) );

        }
     }
     else if (set == true)
     {
       outfile << "Cannot change password" << endl;
       config.setStringValue("Password", commandLine[PASSWORD].c_str());

     }
     if(!config.exists("Num Versions" ))
     {
	cout << "Num Versions definition does not exist " << endl;
	exit (EXIT_FAILURE);
     }
     else
     {
	string numVersions = config.getStringValue("Num Versions" );
	commandLine.insert(pair<int, string > (NUMVERSIONS, numVersions ) );


     }
     if(set == false)
     {
       if(!config.exists("WatchDir" ))
        {
	  cout << "WatchDir definition does not exist " << endl;
	  exit(EXIT_FAILURE );
        }
        else
         {
	   string directory = config.getStringValue("WatchDir" );
	   commandLine.insert(pair<int, string > (WATCHDIR, directory ) );


         }
     }
     else if(set == true)
        {
         outfile << "Cannot change WatchDir location" << endl;
          config.setStringValue("WatchDir", commandLine[WATCHDIR].c_str());
        }


     
   }


}
