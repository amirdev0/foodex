CC = gcc
SRC_DIR := ./src
BIN_DIR := ./bin

# Source files
SERVER_SRC += \
	$(SRC_DIR)/server/main.c \
	$(SRC_DIR)/server/handlers.c \
	$(SRC_DIR)/server/dbconnector.c
	
CUSTOMER_SRC += \
	$(SRC_DIR)/client/customer/main.c \
	$(SRC_DIR)/client/customer/data_transfer.c \
	$(SRC_DIR)/client/customer/account.c \
	$(SRC_DIR)/client/customer/customer.c
	
RESTAURANT_SRC += \
	$(SRC_DIR)/client/restaurant/main.c \
	$(SRC_DIR)/client/restaurant/data_transfer.c \
	$(SRC_DIR)/client/restaurant/account.c \
	$(SRC_DIR)/client/restaurant/restaurant.c

DASHER_SRC += \
	$(SRC_DIR)/client/dasher/main.c \
	$(SRC_DIR)/client/dasher/data_transfer.c \
	$(SRC_DIR)/client/dasher/account.c \
	$(SRC_DIR)/client/dasher/dasher.c

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

server:
	@echo -e '\nBuilding $@'
	$(CC) $(SERVER_SRC) -o $(BIN_DIR)/$@ $(WFLAGS) $(CFLAGS)

client:
	@echo -e '\nBuilding $@'
	$(CC) $(CUSTOMER_SRC) -o $(BIN_DIR)/customer $(WFLAGS) -g -export-dynamic -lm $(CFLAGS)
	$(CC) $(RESTAURANT_SRC) -o $(BIN_DIR)/restaurant $(WFLAGS) -g -export-dynamic -lm $(CFLAGS)
	$(CC) $(DASHER_SRC) -o $(BIN_DIR)/dasher $(WFLAGS) -g -export-dynamic -lm $(CFLAGS)

.PHONY: clean

clean:
	@echo "Deleting binaries"
	rm -rf -v $(BIN_DIR)/*
	touch $(BIN_DIR)/.gitkeep
