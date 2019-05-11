# 89, 12c5a, 12c52, 12cx052
DEVICE = 89
# set compiler path & parameters
CC_ROOT =
CC      = sdcc
CFLAGS  =

# set output folder and target name
OUTPUT_DIR = ./dist/$(DEVICE)
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

$(OUTPUT_DIR)/%.rel: %.c | $(OUTPUT_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $? -o $@

$(TARGET): $(PRJ_OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $^

$(OUTPUT_DIR):
	mkdir -p "$(OUTPUT_DIR)"

flash: $(TARGET)
	stcflash --protocol $(DEVICE) --port /dev/ttyUSB1 $(TARGET)

clean:
	if [ -d "$(OUTPUT_DIR)" ]; then /bin/rm -rf $(OUTPUT_DIR)/*; fi
