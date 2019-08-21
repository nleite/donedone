# Makefile created based on https://hiltmon.com/blog/2015/09/28/the-simple-c-plus-plus-makefile-executable-edition/

UNAME_S := $(shell uname -s)

# CC
ifeq ($(UNAME_S),Darwin)
    CC := g++ -arch x86_64
else
    CC := clang++
endif

# Folders
SRCDIR := src
BUILDDIR := build
TARGETDIR := bin

# Targets
EXECUTABLE := done
TARGET := $(TARGETDIR)/$(EXECUTABLE)

# Final Paths
INSTALLBINDIR := /usr/local/bin

# Code Lists
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

INCDIRS := $(shell find include -name '*.h' -exec dirname {} \; | sort | uniq)
INCLIST := $(patsubst include/%,-I include/%,$(INCDIRS))
BUILDLIST := $(patsubst include/%,$(BUILDDIR)/%,$(INCDIRS))

CFLAGS := -c
INC := -I $(INCLIST) -I /usr/local/include
LIB := -L /usr/local/lib

CFLAGS += -std=c++11 -stdlib=libc++ -O2

$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	@echo "$(CC) $^ -o $(TARGET) $(LIB)"
	@echo "  Linking $(TARGET)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "$(CC) $(CFLAGS) $(INC) -c -o $@ $<"
	@echo "Compiling $<..."; $(CC) $(CFLAGS) $(INC) -c -o $@ $<


clean:
	@echo "Cleaning $(TARGET)..."; $(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean
