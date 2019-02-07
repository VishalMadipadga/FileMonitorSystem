# CS3377.501
#  Vishal Madipadga
#  vrm160030@utdallas.edu


CXX = g++
CXXFLAGS = 
CPPFLAGS = -Wall
LDFLAGS = -L/home/012/v/vr/vrm160030/lib/rude/lib
LDLIBS = -lrudeconfig
EXECFILE = program5
OBJS = program5.o parseCMD.o parseConfigFile.o processControl.o signalHandling.o inotifyFunctions.o
PROJECTNAME = CS3377.Program5

all: $(EXECFILE)

$(EXECFILE): $(OBJS)  
	$(CXX) -static -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)
parseCMD.o: parseCMD.cc 
	$(CXX)  -c  -o parseCMD.o  -I ~/include/tclap/include parseCMD.cc  
parseConfigFile.o: parseConfigFile.cc
	$(CXX) -c -o parseConfigFile.o -I ~/include/rude/include   parseConfigFile.cc
clean: 
	rm -f  $(OBJS) *~ 
backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
