#
# directories setup
#
GTEST_DIR = /usr/local/src/googletest/googletest
TMP_DIR = tmp

#
# source & other vars setup
#
EXEC = task
TESTS = unittests

SRC = level.cpp search.cpp
EXEC_SRC = main.cpp
TESTS_SRC = $(wildcard test_*.cpp)
HEADERS = $(wildcard *.h)

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h

OBJS = $(addprefix $(TMP_DIR)/, $(SRC:.cpp=.o))
EXEC_OBJS = $(addprefix $(TMP_DIR)/, $(EXEC_SRC:.cpp=.o))
TESTS_OBJS = $(addprefix $(TMP_DIR)/, $(TESTS_SRC:.cpp=.o))

#
# compiler options
#
CPP = clang
CPPFLAGS = -g -std=c++11 -Wall -Wextra \
		   -Wno-c++1z-extensions \
		   -pthread \
		   -isystem $(GTEST_DIR)/include
AR = ar
ARFLAGS = cr
LNK = clang
LNKFLAGS = -lstdc++ -pthread

#
# targets
#
all: $(TMP_DIR) $(EXEC) $(TESTS)
gtest: $(TMP_DIR) gtest.a gtest_main.a

clean:
	rm -rf $(EXEC) $(TESTS) $(TMP_DIR) gtest.a gtest_main.a

$(TMP_DIR):
	mkdir -p $(TMP_DIR)

$(TMP_DIR)/%.o: %.cpp $(HEADERS) $(GTEST_HEADERS)
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(EXEC): $(OBJS) $(EXEC_OBJS)
	$(LNK) $(LNKFLAGS) $^ -o $@

$(TESTS): $(OBJS) $(TESTS_OBJS) gtest_main.a
	$(LNK) $(LNKFLAGS) $^ -o $@

#
# gtest targets
#
GTEST_ALL_OBJ = $(TMP_DIR)/gtest-all.o
GTEST_MAIN_OBJ = $(TMP_DIR)/gtest_main.o
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

$(GTEST_ALL_OBJ): $(GTEST_SRCS_)
	$(CPP) $(CPPFLAGS) -I$(GTEST_DIR) -c \
            $(GTEST_DIR)/src/gtest-all.cc -o $@

$(GTEST_MAIN_OBJ): $(GTEST_SRCS_)
	$(CPP) $(CPPFLAGS) -I$(GTEST_DIR) -c \
            $(GTEST_DIR)/src/gtest_main.cc -o $@

gtest.a: $(GTEST_ALL_OBJ)
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a: $(GTEST_ALL_OBJ) $(GTEST_MAIN_OBJ)
	$(AR) $(ARFLAGS) $@ $^
