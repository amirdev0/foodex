# FoodEx
Food delivery system application for Linux (Ubuntu 22.04) written in C from scratch.

## Description
3-layer (2-tier) application implements:
- Client-server architecture
- TCP protocol for networking
- Standard C library only
- Chain Of Responsibility design pattern 
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
- `hostname -I` - command reveals server IPv4 address
- `<SERVER_IPv4>` - server address (printed as server runs)

##### Test
Test application using credentials:
"+998 99 000 00 01" for phone number and "password" for password
