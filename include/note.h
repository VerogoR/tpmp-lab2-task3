/* Author: Egor Gerdiy */

#ifndef NOTE_H
#define NOTE_H

/*
 * note.h — интерфейс (КИС-2) модуля блокнота.
 * Объявлены: типы Date, NOTE; константы размера полей и размера массива;
 * функции note_sort_by_date (сортировка по дате рождения),
 * note_find_by_phone (поиск по номеру телефона).
 */

#include <stddef.h>

#define NOTE_NAME_LEN  64
#define NOTE_TELE_LEN  32
#define BLOCKNOTE_SIZE 10

typedef struct {
    int year;
    int month;
    int day;
} Date;

typedef struct {
    char Name[NOTE_NAME_LEN];
    char TELE[NOTE_TELE_LEN];
    Date DATE;
} NOTE;

void note_sort_by_date(NOTE *blocknote, size_t n);
const NOTE *note_find_by_phone(const NOTE *blocknote, size_t n, const char *tele);

#endif /* NOTE_H */
