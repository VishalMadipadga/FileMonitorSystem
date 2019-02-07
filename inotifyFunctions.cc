//Vishal Madipadga
//CS3377.501
//vrm160030@utdallas.edu
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include "program5.h"
#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )
using namespace std;
void watchDirectory()
{


    int length;
    int i =0;
    char buffer [BUF_LEN];
    int fileDescriptor;
    //getting file descriptor from inotify_init()
    fileDescriptor  = inotify_init();
    int watchDirectory;
    //getting Watch Directory from map
    string directory = commandLine[WATCHDIR];
    //if fileDescriptor is less than 0, log error
    if(fileDescriptor < 0)
    {
	outfile << "inotify_init " << endl;
    }
    //add a directory to watch with flags to check modifications, creations, and deletions
    watchDirectory = inotify_add_watch(fileDescriptor, directory.c_str(), IN_MODIFY | IN_CREATE | IN_DELETE);
    //get the length
    length = read(fileDescriptor,buffer ,BUF_LEN);
    //if the length is less than 0, log error
    if (length < 0)
    {
      outfile << "read" << endl;

    }
    //while i is less than length
    while (i < length)
    {
    //create an inotify event
     struct inotify_event *event = (struct inotify_event *) &buffer;
     //if verbose if false, log less verbose messages
      if (commandLine[VERBOSE] == "FALSE")
      {
      if(event->len)
      {
        if(event -> mask & IN_CREATE)
	  {
            if(event-> mask & IN_ISDIR)
	      {
		outfile <<  "A directory was created"<< endl;
              }
	      else
	      {
		outfile << "A file was created" << endl;
	      }
	  }
	  else if (event -> mask & IN_DELETE)
	   {
	     if(event ->mask & IN_ISDIR)
	      {
		outfile << "A directory was deleted" << endl;
	      }
	      else
	      {
		outfile << "A file was deleted" << endl;

	      }

	   }
	   else if (event ->mask & IN_MODIFY)
	    {
		if(event->mask & IN_ISDIR)
		 {
		   outfile << "A directory was modified" << endl;

		 }
		 else 
		 {
		 //if file was modified, log file
		   outfile << "A file was modified" << endl;
		   //use popen to run date command and get date
		   FILE* date1 = popen("date +%y.%m.%d-%H:%M:%S", "r");
		   char dateStamp1[30];
		   //store the date in array
		   fgets(dateStamp1, 30, date1);
		   //convert to string
		   string dateFinal1(dateStamp1);
		   //get file name
		   string file1 = event->name;
		   //append file name to date
		   string newFile1 = file1 + dateFinal1;
                   //copy the modified file to .versions
		   system(("cp " + commandLine[WATCHDIR] + "/" + event->name + " "+ commandLine[WATCHDIR] + "/.versions"+"/" + newFile1).c_str());

		   
                   

		 }
            }
	  }
	  //increment i
	  i += EVENT_SIZE + event->len;
	  }
	  //if verbose is true, log more verbose messages
	  else if (commandLine[VERBOSE] == "TRUE")
	  {
	    if(event->len)
	      {
	      //if somethinf was created
		if(event -> mask & IN_CREATE)
		  {
		  //if directory was created, log directory created
		    if(event-> mask & IN_ISDIR)
		      {
			outfile <<  "A directory " << event->name<< " was created"<< endl;
		      }
		      //otherwise, log file that was created
		    else
		      {
			outfile << "A file "<<event ->name << " was created" << endl;
		      }
		  }
		  //otherwise a file or directory was deleted
		else if (event -> mask & IN_DELETE)
		  {
		    if(event ->mask & IN_ISDIR)
		      {
			outfile << "A directory " << event ->name << " was deleted" << endl;
		      }
		    else
		      {
			outfile << "A file " << event ->name << " was deleted" << endl;

		      }

		  }
		else if (event ->mask & IN_MODIFY)
		  {
		    if(event->mask & IN_ISDIR)
		      {
			outfile << "A directory " << event -> name << "  was modified" << endl;

		      }
		    else
		      {
		       //if a file was modified
			outfile << "A file " << event -> name << " was modified" << endl;
			//get the date using popen
			FILE* date = popen("date +%y.%m.%d-%H:%M:%S", "r");
			//define a char array to store the the date
		        char dateStamp[30];
			//get the date and store in array
		        fgets(dateStamp, 30, date);
			//convert array to string
			string dateFinal(dateStamp);
			//get file modified
                       string file = event->name;
		       //append file to date
		       string newFile = file + dateFinal; 
		       //copy file to .versions using system command
		       system(("cp " + commandLine[WATCHDIR] + "/" + event->name + " "+ commandLine[WATCHDIR] + "/.versions"+"/" + newFile).c_str());

		      }
		  }
	      }
	    i += EVENT_SIZE + event->len;

             

	  }
	}
        inotify_rm_watch (fileDescriptor, watchDirectory);
	close (fileDescriptor);    
      

    
    


}
