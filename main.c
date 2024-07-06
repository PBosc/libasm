#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int	ft_atoi_base(char *str, char *base);
int ft_strcmp(char *s1, char *s2);
int ft_write(int fd, void *buf, int count);
char *ft_strdup(const char *s);
typedef struct s_list
{
	void *data;
	struct s_list *next;
} t_list;

void ft_swap(void **a, void **b);

int ft_list_size(t_list *begin_list);
void ft_list_push_front(t_list **begin_list, void *data);
void ft_list_sort(t_list **begin_list, int (*cmp)());

void print_list(t_list *list)
{
	t_list *tmp = list;
	while (tmp)
	{
		printf("%p\n", tmp->data);
		tmp = tmp->next;
	}
}


int lower(void *d1, void *d2)
{return ((long long)d1 > (long long)d2);}

int	main(void)
{
	// printf("42:%d\n", ft_atoi_base("2a", "0123456789abcdef"));
	// printf("-42:%d\n", ft_atoi_base("   --------+-2a", "0123456789abcdef"));
	// printf("42:%d\n", ft_atoi_base("   -+-2a", "0123456789abcdef"));
	// printf("0:%d\n", ft_atoi_base("   --------+- 2a", "0123456789abcdef"));
	// printf("0:%d\n", ft_atoi_base("   --------+-z", "0123456789abcdef"));
	// printf("0:%d\n", ft_atoi_base("   --------+-2a", ""));
	// printf("0:%d\n", ft_atoi_base("   --------+-2a", "0"));
	// printf("0:%d\n", ft_atoi_base("   --------+-2a", "+-0"));
	// printf("0:%d\n", ft_atoi_base("   --------+-2a", "\t01"));
	t_list *list = NULL;
	ft_list_push_front(&list, (void*)2);
	ft_list_push_front(&list, (void*)3);
	ft_list_push_front(&list, (void*)4);
	ft_list_push_front(&list, (void*)-1);
	ft_list_push_front(&list, (void*)5);
	ft_list_push_front(&list, (void*)-2);
	ft_list_push_front(&list, (void*)6);
	ft_list_push_front(&list, (void*)-3);
	ft_list_push_front(&list, (void*)0);
	ft_list_push_front(&list, (void*)7);
	print_list(list);
	printf("\n");
	ft_list_sort(&list, lower);
	// printf("%d\n", ft_list_size(list));
	print_list(list);
	// void *a = "a";
	// void *b = "b";
	// printf("%p\n", (char *)a);
	// printf("%p\n", (char *)b);
	// ft_swap(&a, &b);
	// printf("%p\n", (char *)a);
	// printf("%p\n", (char *)b);
	return (0);
}
