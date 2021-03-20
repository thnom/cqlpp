DEFINES=-D__STRICT_ANSI__

SHADOW_WARNING=-Wshadow

WARNINGS=\
-ansi\
-fno-asm\
-pedantic\
-Wall\
-Wcast-align\
-Wconversion\
-Werror\
-Wmissing-prototypes\
-Wno-long-long\
-Wno-parentheses\
-Wnon-virtual-dtor\
-Wpointer-arith\
-Wredundant-decls\
-Wstrict-prototypes\
-Wundef\
-Wwrite-strings\
-W

#-Wno-deprecated\

CCNOWARN=g++ -c -r $(DEBUG) $(DEFINES) $(INCLUDES)
CC_NO_SHADOW=$(CCNOWARN) $(WARNINGS)
CC=$(CC_NO_SHADOW) $(SHADOW_WARNING)

LINK=g++

DEPEND=g++ -M -MF $*.dep $(INCLUDES) $<

%.o: %.cpp
	$(CC) $<

%.dep: %.cpp
	$(DEPEND)

clean::
	- rm *.o *.a *.dep
