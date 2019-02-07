//Vishal Madipadga
//CS3377.501
//vrm160030@utdallas.edu
#include <iostream>
#include <string>
#include <signal.h>
#include <map>
#include "program5.h"
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
using namespace std;
//declaring a global output file for the log file
ofstream outfile;

map <int, string> commandLine;
int main (int argc, char *argv[] )
{

  //calling parseCommand to parse command line
  parseCommand(argc, argv);
 cout << commandLine[CONFIGFILE]<< endl;
 cout << commandLine[DAEMON]<< endl;
 //calling parseCF to parse config file
 parseCF(false);
 cout << commandLine[VERBOSE]<< endl;
 cout << commandLine[LOGFILE]<< endl;
 cout << commandLine[PASSWORD]<< endl;
 cout << commandLine[NUMVERSIONS]<< endl;
 cout << commandLine[WATCHDIR]<< endl;
 //calling process control to fork
  processControl();


 return 0;
}
