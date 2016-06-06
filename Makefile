# Specify target
TARGET		:= ocr
TARGET_TEST	:= ocr_test

# Compiler, Linker Flags
CC			:= clang++
LINKER		:= $(CC)
CFLAGS		:= -std=c++11 -O3 -DARMA_DONT_USE_WRAPPER -march=native -DBENCHMARK
LFLAGS		:= -L /usr/local/opt/openblas/lib -L lib 
SRCEXT		:= cc

TESTFLAGS	:= $(LFLAGS) -pthread

OPENCVLINK	:= -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml \
				-lopencv_video -lopencv_features2d -lopencv_calib3d \
				-lopencv_objdetect -lopencv_stitching

INC 		:= -I /usr/local/opt/openblas/include -I . -I ./src -I ./include
LIB 		:= -larmadillo -lopenblas -llapack $(OPENCVLINK)
TESTLIB		:= $(LIB) -lgmock -lgtest

# Designate directories
SRCDIR		= src
OBJDIR		= build
BINDIR		= bin
TESTDIR		= test

# Set the main method file
OCR_RUN		:= $(SRCDIR)/main/benchmark.cc
OCR_TEST 	:= $(TESTDIR)/tester.cc

# Programmatically load sources and objects
SRCS		:= $(shell find $(SRCDIR) -type f -name *.$(SRCEXT) ! -path "*/main/*")
OBJS		:= $(SRCS:$(SRCDIR)/%.$(SRCEXT)=$(OBJDIR)/%.o)
RUNOBJ		:= $(OCR_RUN:$(SRCDIR)/%.$(SRCEXT)=$(OBJDIR)/%.o)
TESTS		:= $(shell find $(TESTDIR) -type f -name *.$(SRCEXT))
TESTOBJ 	:= $(filter-out $(BUILD)/*.o, $(OBJS))

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(RUNOBJ) $(OBJS)
	@mkdir -p $(BINDIR)
	$(LINKER) $(LFLAGS) $(LIB) $(RUNOBJ) $(OBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

test: $(OBJS)
	@echo " $(TOBJ)"
	$(CC) $(CFLAGS) $(TESTS) $(TESTOBJ) $(INC) $(LFLAGS) $(TESTFLAGS) $(TESTLIB)\
	 -o $(BINDIR)/$(TARGET_TEST)

clean:
	$(RM) -r $(OBJDIR) $(BINDIR)

.PHONY: clean