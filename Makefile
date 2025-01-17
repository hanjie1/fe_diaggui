#
# File:
#    Makefile
#
# Description:
#
# $Date$
# $Rev$
#

CROSS_COMPILE		=
CC			= $(CROSS_COMPILE)g++
AR                      = ar
RANLIB                  = ranlib
CFLAGS			= -O2 -fno-exceptions -fPIC -I/usr/include\
			-I. \
			-I./src \
			-I./src/CTP \
			-I./src/DCRB \
			-I./src/DCRBScalers \
			-I./src/DSC \
			-I./src/FADC \
			-I./src/GTP \
			-I./src/GTP_HPS \
			-I./src/SD \
			-I./src/SSP \
			-I./src/SSP_HPS \
			-I./src/SSP_MPD \
			-I./src/TID \
			-I./src/V1495Pulser \
			-I./src/VSCM \
			-I./src/FADCScalers_HPS \
			-I./src/RICH \
			-I./src/vetroc \
			-I./src/VTP_COMPTON \
			-I./src/VTP_SOLIDECAL \
			-I./src/VTP_EC \
			-I./src/VTP_GT \
			-I./src/VTP_HPS \
			-I./src/SSP_GT \
			-L. -DJLAB \
			`root-config --cflags`
LINKLIBS		= -lrt \
			`root-config --libs` \
			`root-config --glibs`
PROGS			= DiagGUI 
HEADERS			= $(wildcard *.h)
SRC			= ./src/DiagGUI.cxx ./src/main.cxx
OBJS			= $(SRC:.C=.o)

all: $(PROGS) $(HEADERS)

clean distclean:
	@rm -f $(PROGS) *~ *.o outlinkDef.{C,h}

%.o:	%.C Makefile
	@echo "Building $@"
	$(CC) $(CFLAGS) \
	-c $<

$(PROGS): $(OBJS) $(SRC) $(HEADERS) Makefile
	@echo "Building $@"
	$(CC) $(CFLAGS) -o $@ \
	$(LINKLIBS) \
	$(OBJS)


.PHONY: all clean distclean
