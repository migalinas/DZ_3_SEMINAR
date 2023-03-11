#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<locale.h>

void expand(char* s1, char* s2) {
    int i, j, k;
    int len = strlen(s1);

    for (i = j = 0; i < len; i++) {
        if (s1[i] == '-') {
            if (i == 0 || i == len - 1) {
                // Пропускаем дефис, если он находится в начале или конце строки
                s2[j++] = '-';
            }
            else {
                // Иначе разворачиваем сокращенную запись
                char start = s1[i - 1];
                char end = s1[i + 1];

                // Проверяем, являются ли символы буквами или цифрами
                if (isdigit(start) && isdigit(end)) {
                    for (k = start + 1; k <= end; k++) {
                        s2[j++] = k;
                    }
                }
                else if (islower(start) && islower(end)) {
                    for (k = start + 1; k <= end; k++) {
                        s2[j++] = k;
                    }
                }
                else if (isupper(start) && isupper(end)) {
                    for (k = start + 1; k <= end; k++) {
                        s2[j++] = k;
                    }
                }
                else {
                    // Если символы не являются буквами или цифрами, то просто добавляем дефис
                    s2[j++] = '-';
                }
            }
        }
        else {
            s2[j++] = s1[i];
        }
    }
    s2[j] = '\0';
}

void delete_chars(char* s1, char* s2) {
    int i, j, k;
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    for (i = j = 0; i < len1; i++) {
        int found = 0;
        for (k = 0; k < len2; k++) {
            if (s1[i] == s2[k]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
}

void print_histogram(char* s) {
    int i;
    int freq[10] = { 0 };

    for (i = 0; s[i] != '\0'; i++) {
        if (isdigit(s[i])) {
            freq[s[i] - '0']++;
        }
    }

    printf("Горизонтальная гистограмма:\n");
    for (i = 0; i < 10; i++) {
        printf("%d: ", i);
        for (int j = 0; j < freq[i]; j++) {
            putchar('*');
        }
        putchar('\n');
    }

    printf("\nВертикальная гистограмма:\n");
    int max_freq = freq[0];
    for (i = 1; i < 10; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
        }
    }

    for (i = max_freq; i > 0; i--) {
        printf("%2d |", i);
        for (int j = 0; s[j] != '\0'; j++) {
            if (isdigit(s[j])) {
                if (freq[s[j] - '0'] >= i) {
                    putchar('*');
                }
                else {
                    putchar(' ');
                }
            }
        }
        putchar('\n');
    }

    printf("   ");
    for (i = 0; i < 10; i++) {
        printf("--");
    }
    printf("\n   ");
    for (i = 0; i < 10; i++) {
        printf("%d ", i);
    }
    printf("\n");
}
int main() {
    setlocale(LC_ALL, "Rus");
    char s1[100], s2[100];
    printf("Введите строку для разворачивания сокращенной записи: ");
    fgets(s1, 100, stdin);
    s1[strcspn(s1, "\n")] = '\0'; // Удаляем символ новой строки

    expand(s1, s2);
    printf("Строка после разворачивания: %s\n", s2);

    printf("Введите строку для удаления символов: ");
    fgets(s1, 100, stdin);
    s1[strcspn(s1, "\n")] = '\0'; // Удаляем символ новой строки

    printf("Введите символы для удаления: ");
    fgets(s2, 100, stdin);
    s2[strcspn(s2, "\n")] = '\0'; // Удаляем символ новой строки

    delete_chars(s1, s2);
    printf("Строка после удаления символов: %s\n", s1);

    printf("Введите строку для построения гистограммы: ");
    fgets(s1, 100, stdin);
    s1[strcspn(s1, "\n")] = '\0'; // Удаляем символ новой строки

    print_histogram(s1);

    return 0;
}
