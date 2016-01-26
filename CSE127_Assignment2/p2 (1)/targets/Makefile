##############################################################################
#   WARNING: If you change how the targets are compiled in any way, your     #
#            exploits may not work when we test them. So don't do that!      #
##############################################################################

# tools
CC := gcc
CXX := g++
RM := rm -f
CP := cp

# flags
CFLAGS := -ggdb -O1 -zexecstack -fno-stack-protector -U_FORTIFY_SOURCE
CXXFLAGS := $(CFLAGS)
LDFLAGS :=
LDLIBS :=

# sources
targets := target0 target1 target2 target3 
installed_targets := $(addprefix /tmp/,$(targets))

# gmake magic
.PHONY: all clean install generate

#targets
all: generate $(targets)

generate:  
	./base/generatesrc.py

target3: target3.cc
	$(CXX) $(CXXFLAGS) -fstack-protector $(LDFLAGS) -o $@ $<

install: $(targets)
	sudo $(CP) $(targets) /tmp
	sudo chown root:root $(installed_targets)
	sudo chmod 04755 $(installed_targets)

clean:
	$(RM) $(targets)
	sudo $(RM) $(installed_targets)

