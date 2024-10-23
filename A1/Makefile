CFLAGS = -W -Wall -Wextra -Werror
CC = gcc

all: processdemo queuedemo processmodeldemo

processdemo: process.c

queuedemo: queue.c process.c

processmodeldemo: process.c queue.c processmodel.c

clean:
	$(RM) processdemo queuedemo processmodeldemo

