#
# Filename              Makefile
# Date                  04/16/19
# Author                Leonel Chacon
# Email                 lxc171030@utdallas.edu
# Course                CS 3377.501 Spring 2019
# Version               1.0
#
# Copyright 2019, All Rights Reserved
#
# Description
#   Makes the object files and executable for CDK Project.
#


PROJECTNAME = CDKProject

CXX = g++
CXXFLAGS = 
CPPFLAGS = -Wall -g -I /scratch/perkins/include

LDFLAGS = -L /scratch/perkins/lib

LDLIBS = -l cdk -lcurses

#
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters

EXECFILE = cdkexample

OBJS = main.o

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ #

$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

#backup target
backup: clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename 'pwd'))
	@$(eval MKBKUPNAME := ~/backups/$(PROJETNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

#Include dependency files
-include $(SRCS:.cc=.d)
