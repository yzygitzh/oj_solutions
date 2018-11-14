SOURCE_DIR := src
TARGET_DIR := target

SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
TARGETS := $(patsubst $(SOURCE_DIR)/%.cpp,LEETCODE%,$(SOURCES))

CC := g++ -std=c++98

all: clean build

build: mkdir_target $(TARGETS)

clean:
	rm -rf $(TARGET_DIR)

LEETCODE%:
	cat before_main.cpp $(SOURCE_DIR)/$(patsubst LEETCODE%,%,$@).cpp main.cpp | $(CC) -o $(TARGET_DIR)/$(patsubst LEETCODE%,%,$@) -x c++ -

mkdir_target:
	mkdir target
