# Makefile

SHELL   = bash
CC      = g++
LD      = ld
RM      = rm
ECHO    = /bin/echo
CAT     = cat
PRINTF  = printf
MV      = mv
UNTAR   = tar xf
CD      = cd
MAKE    = make

#=================================================================

# Project Name
TARGETexe     = burn

# Project Paths
INSTALL_PATH  =$(PROJECT_ROOT)/bin
PROJECT_ROOT  =.
SRCDIR        =$(PROJECT_ROOT)/src
OBJDIR        =$(PROJECT_ROOT)/obj
BINDIR        =$(PROJECT_ROOT)/bin
LIBDIR        =/usr/lib

# Library Paths
GL_ROOT    =/usr

#Libraries
LIBS = -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS = -g -Wall -std=c++11
LDFLAGS  = -L$(GL_ROOT)/lib

# Colors
NO_COLOR   =\e[0m
OK_COLOR   =\e[1;32m
ERR_COLOR  =\e[1;31m
WARN_COLOR =\e[1;33m
MESG_COLOR =\e[1;34m
FILE_COLOR =\e[1;37m

# Format Strings
OK_STRING   ="[OK]"
ERR_STRING  ="[ERRORS]"
WARN_STRING ="[WARNINGS]"
OK_FMT      ="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT     ="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT    ="${WARN_COLOR}%30s\n${NO_COLOR}"

SRCS        :=$(wildcard $(SRCDIR)/*.cpp)
INCS        :=$(wildcard $(SRCDIR)/*.hpp)
OBJS        :=$(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

MAIN        =$(OBJDIR)/main.o

#=================================================================

.PHONY : exe setup clean

all: setup $(OBJS) $(BINDIR)/$(TARGETexe)

#Note: Putting a space between $(LDFLAGS) and $(LIBS) in the line below makes the linker unable to find -lBox2D.

$(BINDIR)/$(TARGETexe): $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include $(OBJS:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err
	
setup:
	@$(ECHO) "Setting up the compilation..."
	@mkdir -p obj
	@mkdir -p bin
	@$(ECHO) "Done setting up."
	
clean:
	@$(PRINTF) "Cleaning up:"; $(ECHO)
	@$(PRINTF) "$(MESG_COLOR)Removing: $(FILE_COLOR)obj"; $(RM) -rf obj
	@$(PRINTF) "                   $(OK_COLOR)[OK]$(NO_COLOR)"; $(ECHO)
	@$(PRINTF) "$(MESG_COLOR)Removing: $(FILE_COLOR)bin"; $(RM) -rf bin
	@$(PRINTF) "                   $(OK_COLOR)[OK]$(NO_COLOR)"; $(ECHO)
	@$(PRINTF) "All removed, done."; $(ECHO)