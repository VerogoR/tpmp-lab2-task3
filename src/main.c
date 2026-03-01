/* Author: Egor Gerdiy */

/*
 * main.c — клиент (КИС-2): ввод с клавиатуры данных в массив BLOCKNOTE,
 * сортировка по дате рождения, вывод списка записей, поиск по номеру
 * телефона и вывод сведений о человеке или сообщения об отсутствии.
 */

#include "note.h"
#include <stdio.h>
#include <string.h>

static void skip_line(void);
static int read_note(NOTE *note);

/*
 * Пропускает символы до конца строки или EOF.
 */
static void skip_line(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/*
 * Читает одну запись NOTE с клавиатуры.
 * Возвращает 0 при успехе, -1 при ошибке ввода.
 */
static int read_note(NOTE *note)
{
    int n;

    printf("Фамилия и инициалы: ");
    if (fgets(note->Name, NOTE_NAME_LEN, stdin) == NULL)
        return -1;
    note->Name[strcspn(note->Name, "\n")] = '\0';

    printf("Номер телефона: ");
    if (fgets(note->TELE, NOTE_TELE_LEN, stdin) == NULL)
        return -1;
    note->TELE[strcspn(note->TELE, "\n")] = '\0';

    printf("Дата рождения (год месяц день): ");
    n = scanf("%d %d %d", &note->DATE.year, &note->DATE.month, &note->DATE.day);
    skip_line();
    if (n != 3)
        return -1;
    return 0;
}

/*
 * Точка входа: ввод 10 записей, сортировка, вывод списка,
 * поиск по введённому номеру телефона.
 */
int main(void)
{
    NOTE BLOCKNOTE[BLOCKNOTE_SIZE];
    char tele[NOTE_TELE_LEN];
    const NOTE *found;
    size_t i;

    printf("Введите данные для %d записей.\n", BLOCKNOTE_SIZE);
    for (i = 0; i < BLOCKNOTE_SIZE; i++) {
        printf("--- Запись %zu ---\n", i + 1);
        if (read_note(&BLOCKNOTE[i]) != 0) {
            fprintf(stderr, "Ошибка ввода.\n");
            return 1;
        }
    }

    note_sort_by_date(BLOCKNOTE, BLOCKNOTE_SIZE);

    printf("\n--- Список записей (по возрастанию даты рождения) ---\n");
    for (i = 0; i < BLOCKNOTE_SIZE; i++) {
        printf("%zu. %s, %s, %04d-%02d-%02d\n",
               i + 1,
               BLOCKNOTE[i].Name,
               BLOCKNOTE[i].TELE,
               BLOCKNOTE[i].DATE.year,
               BLOCKNOTE[i].DATE.month,
               BLOCKNOTE[i].DATE.day);
    }

    printf("\nВведите номер телефона для поиска: ");
    if (fgets(tele, NOTE_TELE_LEN, stdin) == NULL) {
        fprintf(stderr, "Ошибка ввода.\n");
        return 1;
    }
    tele[strcspn(tele, "\n")] = '\0';

    found = note_find_by_phone(BLOCKNOTE, BLOCKNOTE_SIZE, tele);
    if (found != NULL) {
        printf("\nНайдено:\n");
        printf("  Фамилия и инициалы: %s\n", found->Name);
        printf("  Телефон: %s\n", found->TELE);
        printf("  Дата рождения: %04d-%02d-%02d\n",
               found->DATE.year, found->DATE.month, found->DATE.day);
    } else {
        printf("\nЧеловек с таким номером телефона не найден.\n");
    }

    return 0;
}
