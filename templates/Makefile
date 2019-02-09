SOURCE_DIR := src
DATA_DIR := data
TARGET_DIR := target

CC := g++
TIMEOUT := timeout 1s

clean:
	rm -rf $(TARGET_DIR)

TEMP_%:
	mkdir -p target
	$(CC) -o $(TARGET_DIR)/$(patsubst TEMP_%,%,$@) $(SOURCE_DIR)/$(patsubst TEMP_%,%,$@).cpp
	$(TIMEOUT) $(TARGET_DIR)/$(patsubst TEMP_%,%,$@) < $(DATA_DIR)/$(patsubst TEMP_%,%,$@).in > $(TARGET_DIR)/$(patsubst TEMP_%,%,$@).out 
	diff -qs $(TARGET_DIR)/$(patsubst TEMP_%,%,$@).out $(DATA_DIR)/$(patsubst TEMP_%,%,$@).out 

