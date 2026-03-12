/* Author: Yahor Babko */

/*
 * main.c — точка входа программы «Телефонная книга».
 *
 * Сценарий работы:
 *   1. Ввод 10 записей типа NOTE с клавиатуры.
 *   2. Сортировка массива по возрастанию даты рождения.
 *   3. Вывод отсортированного массива на экран.
 *   4. Запрос номера телефона у пользователя.
 *   5. Поиск и вывод найденной записи или сообщения об отсутствии.
 */

#include <stdio.h>
#include <string.h>

#include "note.h"

int main(void)
{
        BLOCKNOTE book; /* массив из 10 записей */
        NOTE *found; /* результат поиска */
        char query[TELE_LEN]; /* номер телефона для поиска */

        printf("Введите %d записей\n", BLOCKNOTE_SIZE);

	/* ввод */
        blocknote_input(book);

        /* сортировка по дате рождения */
        blocknote_sort(book);

        /* вывод отсортированного массива */
        blocknote_print(book);

        /* запрос номера телефона */
        printf("\nВведите номер телефона для поиска: ");
        if (fgets(query, TELE_LEN, stdin) != NULL)
                query[strcspn(query, "\n")] = '\0';

        /* поиск и вывод результата */
        found = blocknote_search(book, query);
        if (found != NULL) {
                printf("\nЗапись найдена:\n");
                note_print(found);
        } else {
                printf("\nЧеловек с номером телефона \"%s\" не найден.\n",
                       query);
        }

        /* Сбрасываем буфер перед fgets */
        while (getchar() != '\n')
                ;

        if (fgets(query, TELE_LEN, stdin) != NULL)
                query[strcspn(query, "\n")] = '\0';  /* убираем '\n' */

        /* поиск и вывод результата */
        found = blocknote_search(book, query);

        if (found != NULL) {
                printf("\nЗапись найдена:\n");
                note_print(found);
        } else {
                printf("\nЧеловек с номером телефона \"%s\" не найден.\n", query);
        }

        return 0;
}
