//Vishal Madipadga
//CS3377.501
//vrm160030@utdallas.edu
#include <iostream>
#include <map>
#include <tclap/CmdLine.h>
#include <string>
#include "program5.h"
using namespace std;

void parseCommand (int argc, char* argv[])
{
//try catch block
 try{
  string daemonOption; 
  //create Cmdlin object
  TCLAP::CmdLine cmd("CS3377dirmond Directory Monitor Daemon", ' ', " ");
  //create SwitchArg for daemon flag
  TCLAP::SwitchArg daemon ("d","daemon","Run in daemon mode (forks to run as a daemon)", cmd, false );
  //create UnlabeledValueArg for configfile
  TCLAP::UnlabeledValueArg<string> configFile( "", "The name of the configuration file. Defaults to cs3377dirmond.conf",false, "cs3377dirmond.conf", "config filename", true );
  //add argument to Cmdline object
  cmd.add(configFile);
  //parse commandline
  cmd.parse (argc , argv);
  //get values from commandline
  string configfile = configFile.getValue();
  bool daemonCheck = daemon.getValue();
  //check value of daemon flag, convert value to a string
  if (daemonCheck)
     {
	daemonOption = "TRUE";
     }
  else 
  {
  daemonOption = "FALSE";
  }
   //add parsed values to map with corresponding enum
   commandLine.insert(pair <int  , string> (CONFIGFILE , configfile));
   commandLine.insert(pair <int , string> (DAEMON, daemonOption));
      
} catch (TCLAP::ArgException &e) 
{
  //display error message
  cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
}
  

}
