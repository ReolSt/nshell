DEPEND_FILE = .depend

CC = gcc
SRCS = main.c file.c parsing.c system.c interpret.c core/Vector.c core/String.c core/Network.c
OBJS = $(SRCS:%.c=%.o)

LIBS = -lreadline

TARGET = nshell

.SUFFIXES: .c .o

all: $(TARGET)

$(TARGET): $(OBJS)
		gcc -o $(TARGET) $(OBJS) $(LIBS) -Wall
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
