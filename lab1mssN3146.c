#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void printbin(unsigned long n);
int main(int argc, char *argv[]) {
    unsigned long number;
    char temp_str_num[17];
    char str_num[17];
    char new_str_num[33];
    int count = 0;
    int new1, new2, old1, old2;
    unsigned long new_number;
    
    if (argc > 2) {          // Если пользователь ввёл два или больше числа, то выводим ошибку:
        printf("Пожалуйста, введите одно число\n");
        return EXIT_FAILURE;
    }
    
    else if (argc == 1) {    // Если пользователь не ввёл число, то задаём случайное:
        srand(time(NULL));
        number = rand();
    }
    
    else {
    	// Проверяем, что пользователь ввёл число:
    	int len = strlen(argv[1]);
    	for (int i = 0; i <= len-1; ++i) {  // (len-1) чтобы не учитывался последний непечатаемый символ, который учитывается операцией strlen
            if ((argv[1][i] > 57) || (argv[1][i] < 48)) { // Проверяем, что каждый символ цифра (втаблице ASCII цифры между 48 и 57 номером)
    	        printf("Ошибка: \'%s\' не является целым неотрицательным числом.\n", argv[1]);
    	        return EXIT_FAILURE;
    	    }
        }
        sscanf(argv[1], "%lu", &number); // Преобразовываем то, что ввёл пользователь в число
    }
    
    
    // Выводим число в двоичной системе счисления
    printf("Исходное число:        ");
    printbin(number);
    
    // Добавляем незначащий ноль, если один байт неполный
    sprintf(temp_str_num, "%lX", number);
    int temp_len_num = strlen(temp_str_num);
    
    if (temp_len_num % 2 != 0) {
    	str_num[0] = '0';
    	for (int i = 1; i <= temp_len_num + 1; ++i)
    	    str_num[i] = temp_str_num[i-1];
    }
    
    else {
    	for (int i = 0; i <= temp_len_num; ++i)
    	    str_num[i] = temp_str_num[i];
    }
    
    // Преобразовываем число
    int len_num = strlen(str_num)-1;
    
    for (int i = 0; i <= len_num; ++i) {
        char st[2], temp_st[2];
        st[0] = str_num[i];
        if (count == 0) { 
            sscanf(st, "%X", &old1); // Первая тетрада в байте
            ++count;
        }
        else { 
            sscanf(st, "%X", &old2);         // Вторая тетрада в байте 
            
            new1 = 0xF^(old1|old2);          // Первая новая тетрада в байте
            new2 = 0xF^(old1&old2);          // Вторая новая тетрада в байте
            
            // Используя промежуточный массив temp_st передаём новые тетрады в массив нового числа
            sprintf(temp_st, "%X", new1);     
            new_str_num[i-1] = temp_st[0];
            sprintf(temp_st, "%X", new2);
            new_str_num[i] = temp_st[0];
            
            count = 0;                        // Обнуляем счётчик, чтобы начался новый байт
        } 
    }
    
    // Преобразуем массив с числом в число
    sscanf(new_str_num, "%lX", &new_number);

    // Выводим новое число
    printf("Преобразованное число: ");
    printbin(new_number);
    
    return EXIT_SUCCESS;
}


void printbin(unsigned long n) {
    char masbin[64];
    int count = 0;
    
    if (n == 0)
    	printf("00000000");
    	
    else {
        // Переводим в двоичную сс
	while (n > 0) {
	    masbin[count] = (n % 2) + 48;  // Прибавляем 30, чтобы получить код 0 или 1 в таблице ASCII
	    ++count;
	    n /= 2;
	}
	// Добавляем незначащие нули
	while (count % 8 != 0) {
	    masbin[count] = '0';
	    ++count;
	}
	    
	// Ставим пробелы между байтами и выводим число
	for (int i = count; i > 0; --i) {
	    if (i != count && i % 8 == 0 && i != 0)
		printf(" ");
            
	    printf("%c", masbin[i-1]); 
	}   
    }
    printf("\n");
}

