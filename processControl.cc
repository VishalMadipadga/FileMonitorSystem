//Vishal Madipadga
//CS3377.501
//vrm160030@utdallas.edu
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include "program5.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <csignal>
#include "program5.h"
//function to check if file exists
bool fileExists(string&);
void processControl()
{
  //get watch directory from map
  string directory = commandLine[WATCHDIR];
  //path to .versions
  string versions = "/.versions";
  //append path to get path to .versions
  string watch = directory + versions;
  //get log file from the map
  string  logFile = commandLine[LOGFILE];
 // open the log file
  outfile.open(logFile.c_str());
  //define the pid file
  string pidFile = "cs3377dirmond.pid";
  //if the pid file exists
  if(fileExists(pidFile))
     {
        //log error and exit
	outfile << "Pid file already exists " << endl;
	exit(EXIT_FAILURE);
     }
   //open pid file
  ofstream outputfile;
  outputfile.open(pidFile.c_str());
  //if daemon value in map is true
  if(commandLine[DAEMON] == "TRUE")
    {
    //create pid variables
     pid_t forkvalue;
     pid_t sid;
     //get pid value by calling fork
     forkvalue = fork();
     //create directory .versions in watchdir with appended path from path above
     int status = mkdir(watch.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
     //if folder already exists, just continue
     if(status == -1)
     {

     }

    //if pid is less than 0
     if(forkvalue < 0)
       {
       //error occured, exit
	outfile << "There was an error in the fork. No child was created. " << endl;
	exit(EXIT_FAILURE);
       }
      //if pid is greater than 0, it's the parent
     if(forkvalue > 0)
       {
         //write pid value to log file and exit
	 outputfile << forkvalue << endl;
	 exit(EXIT_FAILURE);

       }
       //unset permissions
       umask(0);
        //set sid 
         sid = setsid();
	 //if sid is less than 0, error out and exit
	 if(sid <  0)
	   {
            outputfile << "This is the child. My pid is: " << getpid() << endl;
           exit(EXIT_FAILURE);
	   }

           /* Change the working directory to the root directory */
	       /* or another appropriated directory */
	  chdir("/");
	  //close file descriptors
	  close(STDIN_FILENO);
	  close(STDOUT_FILENO);
          close(STDERR_FILENO);
	  //register signal handlers
	  signal(SIGINT, signalHandling);
	   signal(SIGTERM, signalHandling);
	  signal(SIGHUP, signalHandling);
	  //start infinite while loop
	  while(1)
	  {
	        //sleep for one second
	        sleep(1);
		//call function to do inotify function
		watchDirectory();
	  } 

         
    }
    
  //if daemon value in map is false
  else if (commandLine[DAEMON] == "FALSE")
     {
        //log not running as daemon
	outfile << "Not running as daemon " << endl;
	//start infinite while loop to do the same thing as when running as a daemon
	while(1)
	{
          sleep(1);
	  watchDirectory();
	}

     }


     
}
//function to check if file exists
bool fileExists(string &file) 
{

       struct stat buf;
        return (stat(file.c_str(), &buf) == 0);
}
