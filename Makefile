SRCS = $(addprefix mandatory/, ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s ft_atoi_base.s ft_list_push_front.s ft_list_size.s ft_list_sort.s ft_list_remove_if.s)
# BSRCS = $(addprefix bonus/, ft_strchr.s)
OBJS = $(SRCS:.s=.o)
BOBJS = $(BSRCS:.s=.o) 

all: libasm.a

libasm.a: $(OBJS)
	@ar rcs $@ $^

%.o: %.s
	@nasm -f elf64 $< -o $@

bonus: all

test: re libasm.a
	@cc -c main.c -o main.o
	@cc main.o -L. -lasm -o test
	@./test
	@rm *test*

verbose_test: re libasm.a
	@cc -c main_verbose.c -o main_verbose.o
	@cc main_verbose.o -L. -lasm -o test
	@./test -v
	@rm *test*
	@rm -f readonly.txt

clean:
	@rm -rf $(OBJS) main.o main_verbose.o

fclean: clean
	@rm -rf libasm.a *test*
	@rm -f readonly.txt
	@rm -f *test*

re: fclean all

rex: re
	valgrind ./testmain

.PHONY: all clean fclean re rex test
