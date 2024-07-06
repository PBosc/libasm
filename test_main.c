#include <stdio.h>

int ft_atoi_base(char *str, int base);

int main(void) {
    // Test 1: Binary number
    char binary[] = "101010";
    int result = ft_atoi_base(binary, 2);
    printf("Binary: %s, Decimal: %d\n", binary, result);

    // Test 2: Hexadecimal number
    char hex[] = "FF";
    result = ft_atoi_base(hex, 16);
    printf("Hexadecimal: %s, Decimal: %d\n", hex, result);

    // Test 3: Octal number
    char octal[] = "77";
    result = ft_atoi_base(octal, 8);
    printf("Octal: %s, Decimal: %d\n", octal, result);

    // Test 4: Invalid number
    char invalid[] = "1234";
    result = ft_atoi_base(invalid, 2);
    printf("Invalid: %s, Decimal: %d\n", invalid, result);

    return 0;
}
#include <stdio.h>

int ft_atoi_base(char *str, int base);

int main(void) {
    // Test 1: Binary number
    char binary[] = "101010";
    int result = ft_atoi_base(binary, 2);
    printf("Binary: %s, Decimal: %d\n", binary, result);
    
    // Test 2: Hexadecimal number
    char hex[] = "FF";
    result = ft_atoi_base(hex, 16);
    printf("Hexadecimal: %s, Decimal: %d\n", hex, result);
    
    // Test 3: Octal number
    char octal[] = "77";
    result = ft_atoi_base(octal, 8);
    printf("Octal: %s, Decimal: %d\n", octal, result);
    
    // Test 4: Invalid number
    char invalid[] = "1234";
    result = ft_atoi_base(invalid, 2);
    printf("Invalid: %s, Decimal: %d\n", invalid, result);
    
    // Test 5: Decimal number
    char decimal[] = "123";
    result = ft_atoi_base(decimal, 10);
    printf("Decimal: %s, Decimal: %d\n", decimal, result);
    
    return 0;
}