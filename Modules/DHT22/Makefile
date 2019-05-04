DEVICE = STC89C52
# set compiler path & parameters
CC_ROOT =
CC      = sdcc
CFLAGS  =

# set output folder and target name
OUTPUT_DIR = ./$(DEVICE)
TARGET     = $(OUTPUT_DIR)/$(DEVICE).hex

# set project folder and files (all *.c)
PRJ_ROOT    = .
PRJ_SRC_DIR = $(PRJ_ROOT)/src
PRJ_INC_DIR = $(PRJ_ROOT)/src
# all project sources included by default
PRJ_SOURCE  = $(notdir $(wildcard $(PRJ_SRC_DIR)/*.c))
PRJ_OBJECTS := $(addprefix $(OUTPUT_DIR)/, $(PRJ_SOURCE:.c=.rel))

# collect all include folders
INCLUDE = -I$(PRJ_SRC_DIR)

# collect all source directories
VPATH=$(PRJ_SRC_DIR)

.PHONY: clean

all: $(TARGET)

# $(OUTPUT_DIR)/%.rel: %.c
# 	$(CC) $(CFLAGS) $(INCLUDE) -c $?

$(OUTPUT_DIR)/%.rel: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $? -o $@

$(TARGET): $(PRJ_OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $^

flash: $(TARGET)
	stcflash $(TARGET)

clean:
	rm $(OUTPUT_DIR)/*
