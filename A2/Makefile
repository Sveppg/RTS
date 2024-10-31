CFLAGS = -W -Wall -Wextra -Werror

all: childless zombie enve

childless: childless.c

zombie: zombie.c

enve: LDLIBS = -lreadline 
enve: enve.c 

clean: 
	$(RM) childless zombie enve
