CC = gcc
CFLAGS = -D_REENTRANT
CLIBS = -pthread -lreadline
CMDS = shell_server handle_echo

AIRFORCE = AirForce/AirForceVector.c AirForce/AirForceString.c AirForce/AirForceFileStream.c AirForce/AirForceSocket.c


all : $(CMDS)

shell_server : shell_server.c $(AIRFORCE)
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

recv_echo : recv_echo.c $(AIRFORCE)
	$(CC) $^ -o $@ $(CLIBS)

handle_echo : handle_echo.c $(AIRFORCE)
	$(CC) $^ -o $@ $(CLIBS)
