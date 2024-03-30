# FoodEx
"Food Express" is full form of FoodEx.
FoodEx - is food delivery system application programmed for Linux (Ubuntu 22.04) in C from scratch.

## Description
Application implements:
- 3 logical layers and 2 physical tiers 
- Client-server architecture
- TCP protocol for networking
- Multithreading concept
- Standard C library only
- Chain of Responsibility design pattern 
- MySQL as primary database

# How to ...?

## Configure
Set up environment configuration for build running:
1. `./scripts/setenv.sh` - script to set up database
2. `source .env.example` - command to set up environment

## Build
Build project with `make all` or `make` commands

## Run
First run server application: `./bin/server [PORT] [IPv4]`
- `[PORT]` - optional self port number (by default is 8080)
- `[IPv4]` - optional self IP address (by default is 127.0.0.1)

Then run client application: `./bin/client [PORT] [IPv4]`
- `[PORT]` - optional server port number (by default is 8080)
- `[IPv4]` - optional server IP address (by default is 127.0.0.1)

#### Example
Running server and client with no arguments on same machine by:
`./bin/server` and `./bin/client`

Running server and client on different machines by:
`./bin/server 8080 $(hostname -I)` and `./bin/client 8080 <SERVER_IPv4>`
- `hostname -I` - command reveals self IPv4 address
- `<SERVER_IPv4>` - is server address which is printed as server runs

##### Test
Test application using credentials:
"+998 99 000 00 01" for phone number and "password" for password
