# NOTE: Here, "a.out" is the target and "hello.c" is its dependency. If "a.out"
#       does not exist, or if it is older than "hello.c", then the command
#   	"gcc ..." will be run in order to compile "hello.c" into "a.out".
a.out: hello.c
	gcc -Wall -Wextra -Werror -std=c89 -pedantic hello.c
