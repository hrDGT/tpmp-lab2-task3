/* Author: Yahor Babko */

#ifndef NOTE_H
#define NOTE_H

/*
 * note.h — интерфейс модуля телефонной книги.
 *
 * Определяет структуру NOTE и BLOCKNOTE.
 * Предоставляет функции:
 *   note_input — ввод одной записи с клавиатуры;
 *   blocknote_input — ввод массива из SIZE записей;
 *   blocknote_sort — сортировка по дате рождения (возрастание);
 *   blocknote_search — поиск записи по номеру телефона;
 *   blocknote_print — вывод всего массива на экран;
 *   note_print — вывод одной записи на экран.
 */

/* Максимальный размер строковых полей */
#define NAME_LEN 64 /* длина фамилии с инициалами */
#define TELE_LEN 20 /* длина номера телефона */

/* Размер телефонной книги */
#define BLOCKNOTE_SIZE  10

/* Структура даты рождения */
typedef struct {
        int year;
        int month;
        int day;
} DATE;

/* Структура записи телефонной книги */
typedef struct {
        char name[NAME_LEN];
        char tele[TELE_LEN];
        DATE date;
} NOTE;

/* Тип: массив из BLOCKNOTE_SIZE записей */
typedef NOTE BLOCKNOTE[BLOCKNOTE_SIZE];

/* Прототипы функций */

/* Ввод одной записи NOTE с клавиатуры */
void    note_input(NOTE *note);

/* Ввод всего массива BLOCKNOTE с клавиатуры */
void    blocknote_input(BLOCKNOTE book);

/*
 * Сортировка массива book по возрастанию даты рождения.
 * Используется метод пузырьковой сортировки.
 */
void blocknote_sort(BLOCKNOTE book);

/*
 * Поиск записи по номеру телефона tele в массиве book.
 * Возвращает указатель на найденную запись или NULL.
 */
NOTE *blocknote_search(BLOCKNOTE book, const char *tele);

/* Вывод всего массива book на экран */
void blocknote_print(BLOCKNOTE book);

/* Вывод одной записи note на экран */
void note_print(const NOTE *note);

#endif /* NOTE_H */
