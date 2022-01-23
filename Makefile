CPP     = g++

CCFLAGS =  -pedantic -fopenmp -O -lm

COMMONLFLAGS = -lm -lgsl -lgslcblas
	
LFLAGS = $(COMMONLFLAGS)  

LDBGFLAGS = $(COMMONLFLAGS) -lpthread
DEBUG = -g -Wall -pedantic 

MDDIR=mddir
SRCDIR=src
OBJDIR=objdir
DBGDIR=dbgdir
HDRDIR=header

VPATH =$(SRCDIR)
sources	= \
	gas.cpp \
	dynFricCommon.cpp\

objects	= $(patsubst %,$(OBJDIR)/%,$(sources:.cpp=.o))
headers	= $(foreach dir ,$(subst :, ,$(VPATH)),\
	$(wildcard $(dir)/*.h))

dbgobj = $(patsubst %, $(DBGDIR)/%, $(sources:.cpp=_dbg.o))

ifneq ($(MAKECMDGOALS),clean)
include $(patsubst %, $(MDDIR)/%,$(sources:.cpp=.d))
endif

main: $(OBJDIR)/main.o $(objects) $(headers)
	$(CPP) $(objects) $(OBJDIR)/main.o \
	$(CCFLAGS) $(LFLAGS) -o dynfric

$(OBJDIR)/%.o: %.cpp %.h
	$(CPP) $(CCFLAGS) -c $< -o $@

$(DBGDIR)/%_dbg.o: %.cpp %.h
	$(CPP) $(DEBUG) -c $< -o $@

debug: $(OBJDIR)/main.o  $(headers) $(dbgobj)
	$(CPP) $(dbgobj) $(OBJDIR)/main.o \
	$(DEBUG) $(LDBGFLAGS) -o dynfric_debug
	
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(OBJDIR)
	$(CPP) -g -c $(SRCDIR)/main.cpp -o $@

default: main

lib: $(objects) $(headers) |$(HDRDIR)
	-cp -r $(SRCDIR)/* $(HDRDIR)/
	-rm -r $(HDRDIR)/*.cpp
	@echo -e '#ifndef ALLHEADER\n#define ALLHEADER\n' >$(HDRDIR)/all.h
	@$(foreach hdr ,$(headers), echo -e '#include "../$(hdr)"\n' >>$(HDRDIR)/all.h;)
	@echo -e '#endif' >>$(HDRDIR)/all.h
	ar crf libGenf.a $(objects)


all: prerequisit main doc

$(MDDIR)/%.d: %.cpp | $(MDDIR)
	@set -e; rm -f $@;\
	$(CPP) -MM $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(OBJDIR)/\1.o $@ : ,g' < $@.$$$$ > $@;\
	rm -f $@.$$$$

prerequisit: $(patsubst %, $(MDDIR)/%,$(sources:.cpp=.d)) $(sources)

.PHONY: clean distclean all

$(objects): | $(OBJDIR)

$(dbgobj): | $(DBGDIR)

$(OBJDIR):
	-mkdir $(OBJDIR)

$(MDDIR):
	-mkdir $(MDDIR)

$(DBGDIR):
	-mkdir $(DBGDIR)
	
$(HDRDIR):
	-mkdir $(HDRDIR)

doc: $(headers)
	doxygen

clean:
	$(RM) -r $(OBJDIR)
	$(RM) -r $(DBGDIR)
docclean:
	$(RM) -r doc
distclean: clean
	$(RM) -r doc
	$(RM) -r $(MDDIR)
	$(RM) dynfric
	$(RM) dynfric_debug

	
