CC = gcc
CFLAGS = -D_REENTRANT
CLIBS = -pthread -lreadline
CMDS = shell_server recv_echo handle_echo

RAINBOW = Rainbow/RainbowVector.c Rainbow/RainbowString.c Rainbow/RainbowFileStream.c Rainbow/RainbowSocket.c


all : $(CMDS)

shell_server : shell_server.c $(RAINBOW)
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

recv_echo : recv_echo.c $(RAINBOW)
	$(CC) $^ -o $@ $(CLIBS)

handle_echo : handle_echo.c $(RAINBOW)
	$(CC) $^ -o $@ $(CLIBS)
