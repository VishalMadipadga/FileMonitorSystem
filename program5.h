//Vishal Madipadga
//vrm160030@utdallas.edu
//CS3377.501
#ifndef _PROGRAM5_H
#define _PROGRAM5_H
//include statements
#include <string>
#include <map>
using namespace std;
//enum list that maps to each argument from command line
enum  ParseCommands {CONFIGFILE, DAEMON, VERBOSE, LOGFILE, PASSWORD, NUMVERSIONS, WATCHDIR };
//map commandLine declared
extern map <int, string> commandLine;
//function prototypes
void parseCommand(int, char**  );
void parseCF(bool);
void processControl();
void signalHandling (int);
void watchDirectory();
extern ofstream outfile;
#endif
