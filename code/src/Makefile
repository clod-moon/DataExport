.PHONY: clean data_export
include ../header.mk

##########################################
# Build options
INCLUDE = -I../../include -I/root/UserApp/services/data_export_service/code//3th_part_code/libghttp-1.0.9/  -I../../include/ive/External/ -I../../include/ive/SCFL -I../../include/ive/SCFL/compatible/include/Public -I../include -I../../include/ive/SCFL/compatible/include/Public/linux
ifeq ($(PLATFORM),x86_64)
LIBRARY	= -L../../lib/x86_64
BIN_PATH = ../../bin/x86_64
endif

ifeq ($(PLATFORM),arm_tk1)
LIBRARY	= -L../../lib/ -L../../lib/Debug  -L../../lib/Debug/SCFL 
BIN_PATH = ../../bin/arm_tk1
endif

LIBRARY+=-lghttp -lwebsockets -lcrypto  -lssl -lpthread -lIVECommonObjectd -lIVE_CORE_SDKd -lSCUtilsd -lasound -liconv -lini -lSCVasNetd -lSCVdod -lVdoPostgresd -lVdoSqlited -lxml2 -lz
######################################################################

###############################################
# Target
COBJS	:= $(patsubst %.c,%.o,$(wildcard *.c))
CPPOBJS	:= $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET := data_export
###############################################

#############################################################
# Build
OBJS	:= $(COBJS) $(CPPOBJS)
all: $(TARGET)

$(TARGET):	depend $(OBJS)
	$(PP) $(CC_OPTS)  $(OBJS) -o $(BIN_PATH)/$@ $(LIBRARY)
	
%.o:%.c depend
	$(CC) $(CC_OPTS) -o $@ -c $< $(INCLUDE) 
%.o:%.cpp depend
	$(PP) $(CC_OPTS) -o $@ -c $< $(INCLUDE) 
	
clean:
	rm -f $(TARGET) *.o .depend

#########################################################################
# Dependency
ifeq (.depend,$(wildcard .depend))
include .depend
endif

SRCS := $(COBJS:.o=.c) $(CPPOBJS:.o=.cpp)
depend dep:
	$(CC) -M $(CC_OPTS) $(INCLUDE) $(SRCS) > .depend
###########################################################################

	




