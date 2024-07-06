SRCS = $(addprefix mandatory/, ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s ft_atoi_base.s ft_list_push_front.s ft_list_size.s ft_list_sort.s)
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
	@g++ -c main.cpp -o main.o
	@g++ main.o -L. -lasm -o testmain -no-pie
	@./testmain

clean:
	@rm -rf $(OBJS) main.o

fclean: clean
	@rm -rf libasm.a testmain

re: fclean all

rex: re
	valgrind ./testmain

.PHONY: all clean fclean re rex test
