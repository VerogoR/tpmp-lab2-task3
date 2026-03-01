/*
 * Интерфейс (КИС-2): структура NOTE и API для работы с блокнотом.
 */

#ifndef NOTE_H
#define NOTE_H

#include <stddef.h>

#define NOTE_NAME_LEN  64
#define NOTE_TELE_LEN  32
#define BLOCKNOTE_SIZE 10

/* Дата рождения: год, месяц, число */
typedef struct {
    int year;
    int month;
    int day;
} Date;

/* Запись в блокноте: фамилия и инициалы, телефон, дата рождения */
typedef struct {
    char Name[NOTE_NAME_LEN];
    char TELE[NOTE_TELE_LEN];
    Date DATE;
} NOTE;

/*
 * Упорядочивает массив записей по возрастанию даты рождения.
 * blocknote — массив записей, n — количество элементов.
 */
void note_sort_by_date(NOTE *blocknote, size_t n);

/*
 * Ищет запись по номеру телефона.
 * Возвращает указатель на запись или NULL, если не найдено.
 */
const NOTE *note_find_by_phone(const NOTE *blocknote, size_t n, const char *tele);

#endif /* NOTE_H */
