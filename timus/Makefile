SOURCE_DIR := src
TARGET_DIR := target

SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
TARGETS := $(patsubst $(SOURCE_DIR)/%.cpp,TIMUS%,$(SOURCES))

CC := g++

all: clean build

build: mkdir_target $(TARGETS)

clean:
	rm -rf $(TARGET_DIR)

TIMUS%:
	$(CC) -o $(TARGET_DIR)/$(patsubst TIMUS%,%,$@) $(SOURCE_DIR)/$(patsubst TIMUS%,%,$@).cpp

mkdir_target:
	mkdir target
