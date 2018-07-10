SOURCE_DIR := src
TARGET_DIR := target

SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
TARGETS := $(patsubst $(SOURCE_DIR)/%.cpp,USACO%,$(SOURCES))

CC := g++

all: clean build

build: mkdir_target $(TARGETS)

clean:
	rm -rf $(TARGET_DIR)

USACO%:
	$(CC) -o $(TARGET_DIR)/$(patsubst USACO%,%,$@) $(SOURCE_DIR)/$(patsubst USACO%,%,$@).cpp

mkdir_target:
	mkdir target
