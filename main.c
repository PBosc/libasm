#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <malloc.h>
// #define ft_write write
#define ERROR 0

int	ft_atoi_base(char *str, char *base);
int ft_strlen(char *str);
int ft_strcmp(char *s1, char *s2);
int ft_strcpy(char *dest, char *src);
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);
char *ft_strdup(const char *s);
typedef struct s_list
{
	void *data;
	struct s_list *next;
} t_list;

void ft_swap(void **a, void **b);

int ft_list_size(t_list *begin_list);
void ft_list_push_front(t_list **begin_list, void *data);
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
void ft_list_sort(t_list **begin_list, int (*cmp)());

void print_list(t_list *list)
{
	t_list *tmp = list;
	while (tmp)
	{
		printf("%c\n", *(char *)(tmp->data));
		tmp = tmp->next;
	}
}

int lower(void *d1, void *d2)
{return ((long long)d1 > (long long)d2);}

void list_free(t_list *list)
{
	t_list *tmp;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

int equal(void *d1, void *d2)
{return (*(char*)d1 - *(char*)d2);}
void removes(void *s)
{
	*(char*)s = 'X';
}

void test_strlen() {
    // Test 1: Empty string
    assert(ft_strlen("") == strlen(""));

    // Test 2: Single character string
    assert(ft_strlen("a") == strlen("a"));

    // Test 3: Regular string
    assert(ft_strlen("hello") == strlen("hello"));

    // Test 4: String with spaces
    assert(ft_strlen("hello world") == strlen("hello world"));

    // Test 5: String with special characters
    assert(ft_strlen("!@#$%^&*()") == strlen("!@#$%^&*()"));

    // Test 6: String with escape sequences
    assert(ft_strlen("hello\nworld\t!") == strlen("hello\nworld\t!"));

    // Test 7: Long string
    char longString[1001];
    memset(longString, 'a', 1000);
    longString[1000] = '\0'; // Null-terminate the string
    assert(ft_strlen(longString) == 1000);

    // Test 8: Unicode characters - Note: This is not a valid test for strlen as strlen counts bytes, not characters.
    assert(ft_strlen("你好") == strlen("你好")); // This would fail, as strlen would return the number of bytes, not characters.

    printf("\033[0;32mAll tests for ft_strlen passed successfully.\033[0m\n");
}

void test_strcpy() {
    char src[50], dest[50];

    // Test 1: Copy normal string
    strcpy(src, "Hello World");
    ft_strcpy(dest, src);
    assert(strcmp(dest, "Hello World") == 0);

    // Test 2: Copy empty string
    strcpy(src, "");
    ft_strcpy(dest, src);
    assert(strcmp(dest, "") == 0);

    // Test 3: Copy string with spaces
    strcpy(src, "Hello World from C");
    ft_strcpy(dest, src);
    assert(strcmp(dest, "Hello World from C") == 0);

    // Test 4: Copy string with special characters
    strcpy(src, "!@#$%^&*()");
    ft_strcpy(dest, src);
    assert(strcmp(dest, "!@#$%^&*()") == 0);

    // Test 5: Copy string with null character in the middle
    src[0] = 'H'; src[1] = 'i'; src[2] = '\0'; src[3] = '!';
    ft_strcpy(dest, src);
    assert(strcmp(dest, "Hi") == 0 && dest[3] != '!');

    printf("\033[0;32mAll tests for ft_strcpy passed successfully.\033[0m\n");
}

void test_strcmp() {
    // Test 1: Compare identical strings
    assert(ft_strcmp("Hello", "Hello") == strcmp("Hello", "Hello"));

    // Test 2: Compare different strings (s1 < s2)
    assert((ft_strcmp("Hello", "World") < 0) == (strcmp("Hello", "World") < 0));

    // Test 3: Compare different strings (s1 > s2)
    assert((ft_strcmp("World", "Hello") > 0) == (strcmp("World", "Hello") > 0));

    // Test 4: Compare string with empty string (s1 > s2)
    assert((ft_strcmp("Hello", "") > 0) == (strcmp("Hello", "") > 0));

    // Test 5: Compare empty string with non-empty string (s1 < s2)
    assert((ft_strcmp("", "Hello") < 0) == (strcmp("", "Hello") < 0));

    // Test 6: Compare two empty strings
    assert(ft_strcmp("", "") == strcmp("", ""));

    // Test 7: Compare strings with first character different
    assert((ft_strcmp("a", "b") < 0) == (strcmp("a", "b") < 0));

    // Test 8: Compare strings with last character different
    assert((ft_strcmp("Helloa", "Hellob") < 0) == (strcmp("Helloa", "Hellob") < 0));

    printf("\033[0;32mAll tests for ft_strcmp passed successfully.\033[0m\n");
}

void test_write() {
    int fd;
    ssize_t ret, ft_ret;
    char *test_str = "Hello, world!";
    size_t len = strlen(test_str);
    char buffer[100];
    int saved_errno;

    // Test 1: Successful write
    fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    ret = write(fd, test_str, len);
    saved_errno = errno;
    close(fd);

    fd = open("ft_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    ft_ret = ft_write(fd, test_str, len);
    assert(ret == ft_ret && "Successful write: return value mismatch");
    assert(errno == saved_errno && "Successful write: errno changed");
    close(fd);

    // Test 2: Write to invalid file descriptor
    ret = write(-1, test_str, len);
    saved_errno = errno;
    ft_ret = ft_write(-1, test_str, len);
    assert(ret == ft_ret && "Invalid FD write: return value mismatch");
    assert(errno == saved_errno && "Invalid FD write: errno mismatch");

    // Test 3: Write with NULL buffer
    ret = write(fd, NULL, len);
    saved_errno = errno;
    ft_ret = ft_write(fd, NULL, len);
    assert(ret == ft_ret && "NULL buffer write: return value mismatch");
    assert(errno == saved_errno && "NULL buffer write: errno mismatch");

    // Test 4: Write zero bytes
    fd = open("zero_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    ret = write(fd, test_str, 0);
    saved_errno = errno;
    ft_ret = ft_write(fd, test_str, 0);
    assert(ret == ft_ret && "Zero bytes write: return value mismatch");
    assert(errno == saved_errno && "Zero bytes write: errno changed");
    close(fd);

    printf("\033[0;32mAll tests for ft_write passed successfully.\033[0m\n");
	// Additional Test 5: Write to a file with bad permissions
	const char *readonly_file = "readonly.txt";
	// Ensure the file exists and has read-only permissions before this test
	fd = open(readonly_file, O_WRONLY);
	ret = write(fd, test_str, len);
	saved_errno = errno;
	close(fd); // Close immediately after to avoid keeping an invalid fd open

	fd = open(readonly_file, O_WRONLY);
	ft_ret = ft_write(fd, test_str, len);
	assert(ret == ft_ret && "Read-only file write: return value mismatch");
	assert(errno == saved_errno && "Read-only file write: errno mismatch");
	close(fd);

	// Additional Test 6: Write to a non-existent file without O_CREAT
	fd = open("nonexistent.txt", O_WRONLY);
	ret = write(fd, test_str, len);
	saved_errno = errno;
	close(fd); // Close immediately after to avoid keeping an invalid fd open

	fd = open("ft_nonexistent.txt", O_WRONLY);
	ft_ret = ft_write(fd, test_str, len);
	assert(ret == ft_ret && "Non-existent file write: return value mismatch");
	assert(errno == saved_errno && "Non-existent file write: errno mismatch");
	close(fd);

	// Additional Test 7: Write to a directory (assuming /tmp is always available)
	fd = open("/tmp", O_WRONLY);
	ret = write(fd, test_str, len);
	saved_errno = errno;
	close(fd); // Close immediately after to avoid keeping an invalid fd open

	fd = open("/tmp", O_WRONLY);
	ft_ret = ft_write(fd, test_str, len);
	assert(ret == ft_ret && "Directory write: return value mismatch");
	assert(errno == saved_errno && "Directory write: errno mismatch");
	close(fd);

	printf("\033[0;32mAll extended tests for ft_write passed successfully.\033[0m\n");
}

void test_read() {
    int fd;
    ssize_t ret, ft_ret;
    char buffer[100], ft_buffer[100];
    int saved_errno;

    // Test 1: Successful read
    fd = open("test.txt", O_RDONLY);
    memset(buffer, 0, sizeof(buffer));
    ret = read(fd, buffer, sizeof(buffer));
    saved_errno = errno;
    close(fd);

    fd = open("test.txt", O_RDONLY);
    memset(ft_buffer, 0, sizeof(ft_buffer));
    ft_ret = ft_read(fd, ft_buffer, sizeof(ft_buffer));
    assert(ret == ft_ret && "Successful read: return value mismatch");
    assert(strcmp(buffer, ft_buffer) == 0 && "Successful read: buffer content mismatch");
    assert(errno == saved_errno && "Successful read: errno changed");
    close(fd);

    // Test 2: Read from invalid file descriptor
    ret = read(-1, buffer, sizeof(buffer));
    saved_errno = errno;
    ft_ret = ft_read(-1, ft_buffer, sizeof(ft_buffer));
    assert(ret == ft_ret && "Invalid FD read: return value mismatch");
    assert(errno == saved_errno && "Invalid FD read: errno mismatch");

    // Test 3: Read with NULL buffer
    ret = read(fd, NULL, sizeof(buffer));
    saved_errno = errno;
    ft_ret = ft_read(fd, NULL, sizeof(ft_buffer));
    assert(ret == ft_ret && "NULL buffer read: return value mismatch");
    assert(errno == saved_errno && "NULL buffer read: errno mismatch");

    // Test 4: Read zero bytes
    fd = open("test.txt", O_RDONLY);
    ret = read(fd, buffer, 0);
    saved_errno = errno;
    ft_ret = ft_read(fd, ft_buffer, 0);
    assert(ret == ft_ret && "Zero bytes read: return value mismatch");
    assert(errno == saved_errno && "Zero bytes read: errno changed");
    close(fd);

    printf("\033[0;32mAll tests for ft_read passed successfully.\n");    // Test 5: Reading from a file that does not \033[0mexist
    fd = open("nonexistent_file.txt", O_RDONLY);
    if (fd == -1) { // Expected to fail
		ret = read(fd, buffer, sizeof(buffer));
        saved_errno = errno;
        ft_ret = ft_read(fd, ft_buffer, sizeof(ft_buffer));
        assert(ft_ret == -1 && "Nonexistent file read: return value mismatch");
        assert(errno == saved_errno && "Nonexistent file read: errno mismatch");
    }

    // Test 6: Reading from a directory (assuming /tmp is a directory)
    fd = open("/tmp", O_RDONLY);
    ret = read(fd, buffer, sizeof(buffer));
    saved_errno = errno;
    ft_ret = ft_read(fd, ft_buffer, sizeof(ft_buffer));
    assert(ret == ft_ret && "Directory read: return value mismatch");
    assert(errno == saved_errno && "Directory read: errno mismatch");
    close(fd);

    // Test 7: Reading with a closed file descriptor
    fd = open("test.txt", O_RDONLY);
    close(fd);
    ft_ret = ft_read(fd, ft_buffer, sizeof(ft_buffer));
    assert(ft_ret == -1 && "Closed FD read: return value mismatch");
    assert(errno == EBADF && "Closed FD read: errno mismatch");

    printf("\033[0;32mAll extended errno tests for ft_read passed successfully.\033[0m\n");
}

void test_ft_strdup() {
    char *original;
    char *duplicate;

    // Test 1: Basic Functionality Test
    original = "Hello, World!";
    duplicate = ft_strdup(original);
    assert(strcmp(original, duplicate) == 0 && "Basic Functionality Test failed");
    free(duplicate);

    // Test 2: Empty String Test
    original = "";
    duplicate = ft_strdup(original);
    assert(strcmp(original, duplicate) == 0 && "Empty String Test failed");
    free(duplicate);

    // Test 3: Long String Test
    original = "This is a very long string. It is so long that it might cause problems if the duplication is not handled properly.";
    duplicate = ft_strdup(original);
    assert(strcmp(original, duplicate) == 0 && "Long String Test failed");
    free(duplicate);

    // Note: The NULL String Test is not included because duplicating a NULL pointer is undefined behavior.
    // If your implementation of ft_strdup handles NULL, you can add a test for it, but it's not standard behavior.

    size_t allocated_size;

    // Test 1: Basic Functionality Test with memory size check
    original = "Hello, World!";
    duplicate = ft_strdup(original);
    allocated_size = malloc_usable_size(duplicate);
    assert(strcmp(original, duplicate) == 0 && "Basic Functionality Test failed");
    assert(allocated_size >= strlen(original) + 1 && "Memory allocation size is incorrect");
    free(duplicate);

    // Test 2: Empty String Test with memory size check
    original = "";
    duplicate = ft_strdup(original);
    allocated_size = malloc_usable_size(duplicate);
    assert(strcmp(original, duplicate) == 0 && "Empty String Test failed");
    assert(allocated_size >= strlen(original) + 1 && "Memory allocation size for empty string is incorrect");
    free(duplicate);

	// Test 3: Special Characters Test with memory size check
    original = "!@#$%^&*()_+";
    duplicate = ft_strdup(original);
    allocated_size = malloc_usable_size(duplicate);
    assert(strcmp(original, duplicate) == 0 && "Special Characters Test failed");
    assert(allocated_size >= strlen(original) + 1 && "Memory allocation size for special characters is incorrect");
    free(duplicate);

    // Test 4: Whitespace String Test with memory size check
    original = "   \t\n";
    duplicate = ft_strdup(original);
    allocated_size = malloc_usable_size(duplicate);
    assert(strcmp(original, duplicate) == 0 && "Whitespace String Test failed");
    assert(allocated_size >= strlen(original) + 1 && "Memory allocation size for whitespace string is incorrect");
    free(duplicate);

    // Test 5: Very Long String Test with memory size check
    original = "This is a very long string. It is so long that it might cause problems if the duplication is not handled properly. This string is intended to test the robustness of the ft_strdup function in handling long inputs without causing buffer overflows or memory allocation issues.";
    duplicate = ft_strdup(original);
    allocated_size = malloc_usable_size(duplicate);
    assert(strcmp(original, duplicate) == 0 && "Very Long String Test failed");
    assert(allocated_size >= strlen(original) + 1 && "Memory allocation size for very long string is incorrect");
    free(duplicate);

    printf("\033[0;32mAll tests for ft_strdup passed successfully.\033[0m\n");
}

void test_atoi_base() {
    // Valid conversions
    assert(ft_atoi_base("123", "0123456789") == 123);
    assert(ft_atoi_base("1A", "0123456789ABCDEF") == 26);
    assert(ft_atoi_base("1010", "01") == 10);

    // Invalid bases
    assert(ft_atoi_base("123", "0123 56789") == ERROR);
    assert(ft_atoi_base("123", "012345678+9") == ERROR);
    assert(ft_atoi_base("123", "0123456789-") == ERROR);
    assert(ft_atoi_base("123", "01234567890") == ERROR);
    assert(ft_atoi_base("123", "") == ERROR);
    
    // Invalid characters for the base
    assert(ft_atoi_base("1G", "0123456789ABCDEF") == 1);
    
    // Special cases
    assert(ft_atoi_base("", "0123456789") == 0);
    assert(ft_atoi_base(NULL, "0123456789") == ERROR);
    assert(ft_atoi_base("123", NULL) == ERROR);
	// Handling of signs
	assert(ft_atoi_base("-123", "0123456789") == -123); // Odd number of '-' signs
	assert(ft_atoi_base("--123", "0123456789") == 123); // Even number of '-' signs
	assert(ft_atoi_base("+++123", "0123456789") == 123); // '+' signs

	// Stopping at invalid characters
	assert(ft_atoi_base("123x456", "0123456789") == 123); // Stops at 'x'
	assert(ft_atoi_base("FFG", "0123456789ABCDEF") == 255); // Stops at 'G'

	// Combination of signs and invalid characters
	assert(ft_atoi_base("-123x456", "0123456789") == -123); // Negative number, stops at 'x'
	assert(ft_atoi_base("--123G456", "0123456789ABCDEF") == 291); // Positive number, stops at 'G'
	assert(ft_atoi_base("+++123A456", "0123456789") == 123); // Positive number, stops at 'A'

	// Base with punctuation
	assert(ft_atoi_base("!@!", "!@#") == 3);
	assert(ft_atoi_base("@@@", "!@#") == 13);

	// Base with symbols
	assert(ft_atoi_base("&*(&", "&*(") == 15);
	assert(ft_atoi_base("*(**", "&*(") == 49);

	// Mixed characters
	assert(ft_atoi_base("|%|", "|%$") == 3);
	assert(ft_atoi_base("$$%", "|%$") == 25);


    printf("\033[0;32mAll tests for atoi_base passed successfully.\033[0m\n");
}

void free_list(t_list *list) {
	t_list *tmp;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

void free_list_and_data(t_list *list) {
	t_list *tmp;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->data);
		free(tmp);
	}
}

void test_list_size() {
    t_list *head = NULL;
    assert(ft_list_size(head) == 0); // Test empty list

    ft_list_push_front(&head, "data1");
    assert(ft_list_size(head) == 1); // Test size after adding one item

    ft_list_push_front(&head, "data2");
    assert(ft_list_size(head) == 2); // Test size after adding another item
	free_list(head);
}


void test_list_push_front() {
    t_list *head = NULL;
    ft_list_push_front(&head, "data1");
    assert(strcmp(head->data, "data1") == 0); // Test if data1 is at the front

    ft_list_push_front(&head, "data2");
    assert(strcmp(head->data, "data2") == 0); // Test if data2 is now at the front
	free_list(head);
}

int cmp(void *data1, void *data2) {
    return strcmp((char *)data1, (char *)data2);
}

void free_fct(void *data) {
    free(data);
}


void test_list_remove_if() {
    t_list *head = NULL;
    ft_list_push_front(&head, strdup("data1"));
    ft_list_push_front(&head, strdup("data2"));
    ft_list_push_front(&head, strdup("data3"));

    ft_list_remove_if(&head, "data2", cmp, free_fct);
    assert(ft_list_size(head) == 2); // Test size after removal
    assert(strcmp(head->data, "data3") == 0); // Test if head is correct
    assert(strcmp(head->next->data, "data1") == 0); // Test if second element is correct
	free_list_and_data(head);
}

void test_list_sort() {
    t_list *head = NULL;
    ft_list_push_front(&head, strdup("b"));
    ft_list_push_front(&head, strdup("c"));
    ft_list_push_front(&head, strdup("a"));

    ft_list_sort(&head, cmp);
    assert(strcmp(head->data, "a") == 0); // Test if first element is 'a'
    assert(strcmp(head->next->data, "b") == 0); // Test if second element is 'b'
    assert(strcmp(head->next->next->data, "c") == 0); // Test if third element is 'c'
	free_list_and_data(head);
}

int	main(void)
{
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
	test_read();
	test_ft_strdup();
	printf("\033[0;32mAll mandatory tests passed successfully.\033[0m\n");
	printf("\033[0;35mStarting bonus tests....\033[0m\n");
	test_atoi_base();
	printf("\033[0;35mTesting link lists....\033[0m\n");
	test_list_size();
    test_list_push_front();
    test_list_remove_if();
    test_list_sort();
	printf("\033[0;32mAll link list tests passed successfully.\033[0m\n");
	printf("\033[0;34mAll bonus tests passed successfully.\033[0m\n");
	return (0);
}
