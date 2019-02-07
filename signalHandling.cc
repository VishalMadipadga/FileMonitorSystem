//Vishal Madipadga
//CS3377.501
//vrm160030@utdallas.edu
#include <iostream>
#include <fstream>
#include <csignal>
#include <cstdio>
#include <stdlib.h>
#include "program5.h"
#include <unistd.h>
using namespace std;
//function to catch and handle 3 signals
void signalHandling(int signum )
{
  //if the signal caught was SIGINT or SIGTERM
 if (signum == SIGINT || signum == SIGTERM )
    {
    //get path of home
    char const* path = getenv( "HOME" );
    //convert it to a string
    string s(path);
    //get path to pid file
    string pidfile = "/Program5/cs3377dirmond.pid";
   //get log file
   string logfile = commandLine[LOGFILE];
   //append paths to get path to pid file
   string directory = s + pidfile;
   //log signal received and exiting
   outfile << "Signal recieved, killing daemon, removing pid file, and closing log file" << endl;
   //remove pid file
     remove(directory.c_str());
     //close log file
     outfile.close();
     //exit
     exit(signum);

   }
   //the signal caught was SIGHUP
   else  if (signum == SIGHUP)
    {
    //call function to parse config file with true passed in
     parseCF(true); 

    }






}
