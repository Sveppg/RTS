CFLAGS = -W -Wall -Wextra -Werror  -fsanitize=address
CC = gcc

all:   processmodeldemo

processdemo: process.c

queuedemo: queue.c process.c

processmodeldemo: process.c queue.c processmodel.c

clean:
	$(RM) queuedemo processmodeldemo

