CC=g++
CPPFLAGS=-std=gnu++11 -O3

sources:=$(wildcard *.c) $(wildcard *.cpp)

objects:=$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(sources)))

dependence:=$(objects:.o=.d)

all: $(objects)
	$(CC) $(CPPFLAGS) $^ -o $@
#	@./$@

%.o: %.c
	$(CC) $(CPPFLAGS) -c $< -o $@

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

include $(dependence)

define gen_dep
set -e; rm -f $@; \
$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
rm -f $@.$$$$
endef

%.d: %.c
	$(gen_dep)

%.d: %.cpp
	$(gen_dep)

.PHONY: clean
clean:
	@rm -f all $(objects) $(dependence)

#echo:
#	@echo sources=$(sources)
#	@echo objects=$(objects)
#	@echo dependence=$(dependence)
#	@echo CPPFLAGS=$(CPPFLAGS)

