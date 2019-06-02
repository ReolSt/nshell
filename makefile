DEPEND_FILE = .depend

CC = gcc -g
SRCS = main.c file.c parsing.c system.c interpret.c Rainbow/RainbowVector.c Rainbow/RainbowString.c Rainbow/RainbowFileStream.c Rainbow/RainbowSocket.c
OBJS = $(SRCS:%.c=%.o)

LIBS = -lreadline

TARGET = nshell

.SUFFIXES: .c .o

all: $(TARGET)

$(TARGET): $(OBJS)
		gcc -o $(TARGET) $(OBJS) $(LIBS)
		rm $(OBJS)

depend:
		$(CC) -MM $(SRCS) > $(DEPEND_FILE)

clean:
		rm -f $(OBJS) $(TARGET) $(DEPEND_FILE)

ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), depend)
ifneq ($(SRCS),)
-include $(DEPEND_FILE)
endif
endif
endif
