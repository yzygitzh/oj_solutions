SOURCE_DIR := src
TARGET_DIR := target

SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
TARGETS := $(patsubst $(SOURCE_DIR)/%.cpp,POJ%,$(SOURCES))

CC := g++

all: clean build

build: mkdir_target $(TARGETS)

clean:
	rm -rf $(TARGET_DIR)

POJ%:
	$(CC) -o $(TARGET_DIR)/$(patsubst POJ%,%,$@) $(SOURCE_DIR)/$(patsubst POJ%,%,$@).cpp

mkdir_target:
	mkdir target
