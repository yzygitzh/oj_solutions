SOURCE_DIR := src
TARGET_DIR := target

SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
TARGETS := $(patsubst $(SOURCE_DIR)/%.cpp,ICPC%,$(SOURCES))

CC := g++

all: clean build

build: mkdir_target $(TARGETS)

clean:
	rm -rf $(TARGET_DIR)

ICPC%:
	$(CC) -o $(TARGET_DIR)/$(patsubst ICPC%,%,$@) $(SOURCE_DIR)/$(patsubst ICPC%,%,$@).cpp

mkdir_target:
	mkdir target
