CC = gcc
CFLAGS = -D_REENTRANT
CLIBS = -pthread
CMDS = shell_server recv_echo handle_echo

all : $(CMDS)

shell_server : shell_server.c Rainbow/RainbowVector.c Rainbow/RainbowString.c Rainbow/RainbowFileStream.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

recv_echo : recv_echo.c
	$(CC) $^ -o $@

handle_echo : handle_echo.c
	$(CC) $^ -o $@
