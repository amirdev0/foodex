CC = gcc
SRC_DIR := ./src
BIN_DIR := ./bin

# Source files
SERVER_SRC += \
	$(SRC_DIR)/server/service/main.c \
	$(SRC_DIR)/server/service/handlers.c \
	$(SRC_DIR)/server/service/marshalling.c \
	$(SRC_DIR)/server/db/dbconnector.c

CLIENT_SRC += \
	$(SRC_DIR)/client/connection.c \
	$(SRC_DIR)/client/transmission.c \
	$(SRC_DIR)/client/account_api.c

CUSTOMER_SRC += \
	$(SRC_DIR)/client/customer/main.c \
	$(SRC_DIR)/client/customer/customer_api.c \
	$(SRC_DIR)/client/customer/customer.c
	
RESTAURANT_SRC += \
	$(SRC_DIR)/client/restaurant/main.c \
	$(SRC_DIR)/client/restaurant/restaurant_api.c \
	$(SRC_DIR)/client/restaurant/restaurant.c

DASHER_SRC += \
	$(SRC_DIR)/client/dasher/main.c \
	$(SRC_DIR)/client/dasher/dasher_api.c \
	$(SRC_DIR)/client/dasher/dasher.c

# Include folders common to all targets
INC_FOLDERS += \
	$(SRC_DIR)/ \
	$(SRC_DIR)/client \
	$(SRC_DIR)/server \
	$(SRC_DIR)/server/db
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

all: clean mkdir server client
	@echo -e '\nProject was built'

server:
	@echo -e '\nBuilding $@'
	$(CC) $(SERVER_SRC) -o $(BIN_DIR)/$@ $(WFLAGS) $(CFLAGS)

client: 
	@echo -e '\nBuilding $@'
	$(CC) $(CLIENT_SRC) $(CUSTOMER_SRC) -o $(BIN_DIR)/customer $(WFLAGS) -g -export-dynamic -lm $(CFLAGS)
	$(CC) $(CLIENT_SRC) $(RESTAURANT_SRC) -o $(BIN_DIR)/restaurant $(WFLAGS) -g -export-dynamic -lm $(CFLAGS)
	$(CC) $(CLIENT_SRC) $(DASHER_SRC) -o $(BIN_DIR)/dasher $(WFLAGS) -g -export-dynamic -lm $(CFLAGS)

.PHONY: clean

clean:
	@echo "Deleting binaries"
	rm -rf -v $(BIN_DIR)

mkdir:
	@echo "Making ./bin directory"
	mkdir ./bin
