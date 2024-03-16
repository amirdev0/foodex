# FoodEx
Food delivery system application for Linux (Ubuntu 22.04) written in C

## Configure
Set up environment configuration for build running:
`./scripts/setenv.sh` - script to set up database
`source .env.example` - command to set up environment

## Build
Build project with `make all` or `make` command

## Run
Run server application `./build/server [PORT] [IPv4]`
- `[PORT]` - optional host port number (by default 8080)
- `[IPv4]` - optional host IP address (by default 127.0.0.1)

Run client application `./build/client [PORT] [IPv4]`
- `[PORT]` - optional server port number (by default 8080)
- `[IPv4]` - optional server IP address (by default 127.0.0.1)

#### Example
Run server and client with no arguments on single machine:
`./bin/server`
`./bin/client`

To reveal host IPv4 use command:
`hostname -I`

Run server and client on different machines:
`./bin/server 8080 $(hostname -I)`
`./bin/client 8080 <SERVER_IPv4>`
- `<SERVER_IPv4>` is printed as server runs

##### Test
Test application using credentials below
phone: +998999686868
password: password
