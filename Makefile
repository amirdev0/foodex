CC = gcc
SRC_DIR := ./src
BIN_DIR := ./bin

# Source files
SERVER_SRC += \
	$(SRC_DIR)/server/main.c \
	$(SRC_DIR)/server/handlers.c \
	$(SRC_DIR)/server/dbconnector.c
	
CLIENT_SRC += \
	$(SRC_DIR)/client/main.c \
	$(SRC_DIR)/client/data_transfer.c \
	$(SRC_DIR)/client/account.c \
	$(SRC_DIR)/client/customer.c \
	$(SRC_DIR)/client/restaurant.c \
	$(SRC_DIR)/client/dasher.c

# Include folders common to all targets
INC_FOLDERS += $(SRC_DIR)/common
INC_PARAMS=$(foreach d, $(INC_FOLDERS), -I$d)

# Optimization flags
OPT += -O3 -g3

# C flags common to all targets
#CFLAGS += $(OPT)
CFLAGS += $(INC_PARAMS)
CFLAGS += $(shell pkg-config --cflags --libs mysqlclient)

# Warning flags
WFLAGS += -Wall
WFLAGS += -Wextra

all: clean server client
	@echo -e '\nProject was built'

server: mkdir
	@echo -e '\nBuilding $@'
	$(CC) $(SERVER_SRC) -o $(BIN_DIR)/$@ $(WFLAGS) $(CFLAGS)

client: mkdir
	@echo -e '\nBuilding $@'
	$(CC) $(CLIENT_SRC) -o $(BIN_DIR)/$@ $(WFLAGS) -g -export-dynamic -lm $(CFLAGS)

mkdir:
	@echo -e '\nMaking ' $(BIN_DIR)
	mkdir $(BIN_DIR)

.PHONY: clean

clean:
	@echo "Deleting binaries"
	rm -rf -v $(BIN_DIR)
