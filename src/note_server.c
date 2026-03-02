/* Author: Egor Gerdiy */

/*
 * note_server.c — сервер (КИС-2): реализация сортировки массива NOTE
 * по возрастанию даты рождения и поиска записи по номеру телефона.
 */

#include "note.h"
#include <string.h>

static int date_compare(const Date *d1, const Date *d2);

/*
 * Сравнивает две даты.
 * Возвращает: < 0 если d1 раньше d2, 0 если равны, > 0 если d1 позже d2.
 */
static int date_compare(const Date *d1, const Date *d2)
{
    if (d1->year != d2->year)
        return d1->year - d2->year;
    if (d1->month != d2->month)
        return d1->month - d2->month;
    return d1->day - d2->day;
}

/*
 * Упорядочивает массив записей по возрастанию даты рождения.
 */
void note_sort_by_date(NOTE *blocknote, size_t n)
{
    size_t i, j;
    NOTE tmp;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (date_compare(&blocknote[j].DATE, &blocknote[i].DATE) < 0) {
                tmp = blocknote[i];
                blocknote[i] = blocknote[j];
                blocknote[j] = tmp;
            }
        }
    }
}

/*
 * Ищет запись по номеру телефона.
 * Возвращает указатель на запись или NULL, если не найдено.
 */
const NOTE *note_find_by_phone(const NOTE *blocknote, size_t n, const char *tele)
{
    size_t i;

    for (i = 0; i < n; i++) {
        if (strcmp(blocknote[i].TELE, tele) == 0)
            return &blocknote[i];
    }
    return NULL;
}
