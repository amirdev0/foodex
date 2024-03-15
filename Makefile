CC = gcc
SRC_DIR := ./src
BIN_DIR := ./bin

# Source files
SERVER_SRC += \
	$(SRC_DIR)/server/main.c \
	$(SRC_DIR)/server/handlers.c \
	$(SRC_DIR)/server/dbconnector.c
	

CLIENT_SRC += \
	$(SRC_DIR)/client/gui/LoginPage.c \
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
CFLAGS += $(shell pkg-config --cflags mysqlclient)
CFLAGS += $(shell pkg-config --libs mysqlclient)

# Warning flags

all: server client
	@echo -e '\nBuilding project'

server: mkdir
	@echo -e '\nBuilding $@'
	$(CC) $(SERVER_SRC) -o $(BIN_DIR)/$@ $(CFLAGS)
	
client: mkdir
	@echo -e '\nBuilding $@'
	$(CC) $(CLIENT_SRC) -o $(BIN_DIR)/$@ -Wall -Wextra -g $(shell pkg-config --cflags --libs gtk+-3.0) -export-dynamic -lm $(CFLAGS)

mkdir:
	@echo -e '\nMaking ' $(BIN_DIR)
	mkdir -p $(BIN_DIR)
	cp $(SRC_DIR)/client/gui/*.glade $(BIN_DIR)/
	cp -r $(SRC_DIR)/client/gui/images $(BIN_DIR)/

.PHONY: clean

clean:
	@echo -e '\nDeleting binaries'
	rm -rf -v $(BIN_DIR)
