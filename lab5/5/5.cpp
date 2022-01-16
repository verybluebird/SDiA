/*Упорядочить таблицу, построенную в лабораторной работе № 4 
вариант 2.а 
по не убыванию значений ключа методом:
а) быстрой сортировки;
Включить информацию, хранимую в этой таблице, в таблицу 
продукции, имеющейся на складе. Таблица продукции упорядочена
по возрастанию ключа. Элемент таблицы включает: шифр изделия 
(это ключ ),
наименование, количество ( штук ), цена ( за штуку ). 
Цену изделия брать из 
таблицы – прейскурант, элемент которой содержит:
шифр изделия, цена ( за штуку ). 
Эта таблица также упорядочена по возрастанию шифров изделий. Для поиска
элементов в таблице использовать:
а) последовательный поиск;
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#pragma warning(disable : 4996)

const double HashMult = 0.1;
const int TableSize = 10;
const int Nmax = 9;

struct product
{
    char key[Nmax];
    char name[Nmax];
    int q;
    unsigned long hash_code;

    product()
    {
        key[0] = '0';
        name[0] = '0';
        hash_code = 0;
        q = 0;
    }

};

struct table
{
    product elem[TableSize];
    int n;

    table()
    {
        for (int i = 0; i < TableSize; i++)
            elem[i] = product();
        n = 0;
    }
};

int int_from_key(char* key) {
    int k = 0;
    int digit = 0;
    int mult = 0;
    for (int i = 0; i < 8; i++) {
        digit = *(key + i) - '0';
        mult = pow(10 , (7 - i));
        k += digit*mult;
    }
    return k;
}

int search(table* T, product p)
{
    for (int i = 0; i < T->n; i++) // просматриваем все элементы в цикле
    {
        if (T->elem[i].key == p.key)      // если находим элемент со значением key,
            return i;     // возвращаем его индекс
    }
    return -1;  // возвращаем -1 - элемент не найден
}

unsigned int calc_hash(char* key)

{
    int h = int(*key) % Nmax;
    return h;
}

int insert_elem(table* G, product e)

{
    int i = 0;
    e.hash_code = calc_hash(e.key);
    if (G->n < TableSize)
    {
        while (i < G->n)
        {
            if (G->elem[i].hash_code == e.hash_code)//ищем строку с тем же хешем
                if (!strcmp(G->elem[i].key, e.key))
                {
                    G->elem[i].q += e.q;
                    strcpy_s(G->elem[i].name, e.name);

                    return 1;
                }
            i++;
        }

        G->elem[i] = e;
        G->n++;
        return 1;
    }

    else
        return 0;

}


int quicksort(table* T, int low, int high) {
    if ((T->n) < 2)
        return 1;
    else {
        table* Less = new table();
        table* Greater = new table();
        product pivot = T->elem[(T->n) / 2];
        product temp;
        int i = low, j = high;
        int pivotKey = int_from_key(pivot.key);
        while (i <= j)
        {
            while (int_from_key(T->elem[i].key) < pivotKey)
                i++;
            while (int_from_key(T->elem[j].key) < pivotKey)
                j--;
            if (i <= j)
            {
                temp = T->elem[i];
                T->elem[i] = T->elem[j];
                T->elem[j] = temp;
                i++;
                j--;
            }
        }
        if (j > low)
            quicksort(T, low, j);
        if (i < high)
            quicksort(T, i, high);
        return 1;
    }
 }

    

    
    


void read_table(FILE* fin, table* G)
{
    product item;
    while (fscanf_s(fin, "%s%s%i", item.key, Nmax, item.name, Nmax, &(item.q)) != EOF)
    {
        insert_elem(G, item);
    }
}

void write_table(FILE* fout, table* G)
{
    int n = 0;

    for (int i = 0; i < G->n; i++)
    {
        while (G->elem[n].key[0] == '\0')
            n++;
        fprintf(fout, "\n %8s %12s %10d", G->elem[n].key, G->elem[n].name, G->elem[n].q);
        n++;
    }
}

int main()
{
    FILE* fin = fopen("table.txt", "r");
    FILE* fout = fopen("product.txt", "w");
    table* Table = new table;
    read_table(fin, Table);
    fclose(fin);
    quicksort(Table,0,Table->n);
    write_table(fout, Table);
    fclose(fout);

    return 0;
}