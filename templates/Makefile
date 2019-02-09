SOURCE_DIR := src
TEST_DIR := test
DATA_DIR := data
TARGET_DIR := target

CC := g++
TIMEOUT := timeout 1s

clean:
	rm -rf $(TARGET_DIR)

TEMP_%:
	mkdir -p target
	$(CC) -o $(TARGET_DIR)/$(patsubst TEMP_%,%,$@).test $(TEST_DIR)/$(patsubst TEMP_%,%,$@).cpp
	$(TIMEOUT) $(TARGET_DIR)/$(patsubst TEMP_%,%,$@).test < $(DATA_DIR)/$(patsubst TEMP_%,%,$@).in > $(TARGET_DIR)/$(patsubst TEMP_%,%,$@).source.out
	$(CC) -o $(TARGET_DIR)/$(patsubst TEMP_%,%,$@).source $(SOURCE_DIR)/$(patsubst TEMP_%,%,$@).cpp
	$(TIMEOUT) $(TARGET_DIR)/$(patsubst TEMP_%,%,$@).source < $(DATA_DIR)/$(patsubst TEMP_%,%,$@).in > $(TARGET_DIR)/$(patsubst TEMP_%,%,$@).test.out 
	diff -qs $(TARGET_DIR)/$(patsubst TEMP_%,%,$@).source.out $(TARGET_DIR)/$(patsubst TEMP_%,%,$@).test.out 

