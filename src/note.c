/* Author: Yahor Babko */

/*
 * note.c — реализация модуля телефонной книги
 * Содержит определения всех функций, объявленных в note.h
*/

#include <stdio.h>
#include <string.h>

#include "note.h"

/* Вспомогательная статическая функция — сравнение двух дат */
/* Возвращает отрицательное значение если a < b */
/* 0 если a == b */
/* положительное значение если a > b. */
static int date_cmp(const DATE *a, const DATE *b)
{
        if (a->year != b->year)
                return a->year - b->year;

        if (a->month != b->month)
                return a->month - b->month;

        return a->day - b->day;
}

/*
 * note_input — ввод одной записи NOTE с клавиатуры.
 * Запрашивает у пользователя фамилию, телефон и дату рождения.
*/
void note_input(NOTE *note)
{
        printf("Фамилия и инициалы: ");
        /* fgets сохраняет '\n', убираем его */
        if (fgets(note->name, NAME_LEN, stdin) != NULL)
                note->name[strcspn(note->name, "\n")] = '\0';

        printf("Номер телефона: ");
        if (fgets(note->tele, TELE_LEN, stdin) != NULL)
                note->tele[strcspn(note->tele, "\n")] = '\0';

        printf("Год рождения: ");
        scanf("%d", &note->date.year);

        printf("Месяц рождения: ");
        scanf("%d", &note->date.month);

        printf("День рождения: ");
        scanf("%d", &note->date.day);
}

/*
 * blocknote_input — ввод всего массива из BLOCKNOTE_SIZE записей.
 * Последовательно вызывает note_input для каждой позиции.
*/
void blocknote_input(BLOCKNOTE book)
{
        int i; /* счётчик цикла */

        for (i = 0; i < BLOCKNOTE_SIZE; i++) {
                printf("\nЗапись %d из %d:\n", i + 1, BLOCKNOTE_SIZE);
                note_input(&book[i]);
        }
}

/*
 * blocknote_sort — сортирует массив book по возрастанию даты рождения.
 * Алгоритм: пузырьковая сортировка с флагом досрочного выхода.
*/
void blocknote_sort(BLOCKNOTE book)
{
        int i; /* внешний счётчик */
        int j; /* внутренний счётчик */
        int swapped; /* флаг перестановки */
        NOTE tmp; /* временная запись для обмена */

        for (i = 0; i < BLOCKNOTE_SIZE - 1; i++) {
                swapped = 0;

                for (j = 0; j < BLOCKNOTE_SIZE - 1 - i; j++) {
                        if (date_cmp(&book[j].date,
                                     &book[j + 1].date) > 0) {
                                /* Обмен записей */
                                tmp        = book[j];
                                book[j]    = book[j + 1];
                                book[j + 1] = tmp;
                                swapped    = 1;
                        }
                }

                /* Массив уже отсортирован — досрочный выход */
                if (!swapped)
                        break;
        }
}

/*
 * blocknote_search — поиск записи по номеру телефона.
 * Выполняет линейный поиск в массиве book.
 * Возвращает указатель на первую подходящую запись или NULL.
*/
NOTE * blocknote_search(BLOCKNOTE book, const char *tele)
{
        int i; /* счётчик цикла */

        for (i = 0; i < BLOCKNOTE_SIZE; i++) {
                if (strcmp(book[i].tele, tele) == 0)
                        return &book[i];
        }

        return NULL;
}

/*
 * note_print — форматированный вывод одной записи на экран.
*/
void note_print(const NOTE *note)
{
        printf("  %-40s  тел: %-20s  дата рождения: %04d-%02d-%02d\n",
               note->name,
               note->tele,
               note->date.year,
               note->date.month,
               note->date.day);
}

/*
 * blocknote_print — вывод всего массива на экран.
 * Выводит заголовок и последовательно печатает каждую запись.
 */
void blocknote_print(BLOCKNOTE book)
{
        int i; /* счётчик цикла */

        printf("\n%-3s  %-40s  %-20s  %s\n",
               "№", "Фамилия и инициалы", "Телефон", "Дата рождения");

        for (i = 0; i < BLOCKNOTE_SIZE; i++) {
                printf("%-3d  ", i + 1);
                note_print(&book[i]);
        }
}
