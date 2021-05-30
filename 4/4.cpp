/*В файле WORK содержатся результаты работы цеха за день.
Элемент файла включает : шифр изделия(8 - символьный код), 
наименование изделия, количество(штук).Построить таблицу, 
содержащую результаты работы за день, считая ключом шифр 
изделия. Элемент таблицы имеет ту же структуру, что и элемент
файла.Содержащаяся в файле информация с равными ключами должны
быть помещена в таблицу один раз с общим количеством штук 
изделия.Организовать таблицу как : а) неупорядоченную.*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
        key[0] = '\0';
        name[0] = '\0';
        hash_code = 0;
        q = 0;
    }

    product(const char* _key, const char* _name, int _q)
    {
        strcpy_s(key, _key);
        strcpy_s(name, _name);
        q = _q;
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

    table(product _elem[Nmax], int _n)
    {
        for (int i = 0; i < Nmax; i++)
            elem[i] = _elem[i];
        n = _n;
    }
};

unsigned int calc_hash(char* key)

{
    int h = int(*key)% Nmax;
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
        i--;

        while (i >= 0)
        {
            G->elem[i + 1] = G->elem[i];
            i--;
        }

        G->elem[0] = e;
        G->n++;

        return 1;
    }

    else
        return 0;

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
        fprintf_s(fout, "\n %8s %12s %10d", G->elem[n].key, G->elem[n].name, G->elem[n].q);
        n++;
    }
}

int main()
{
    FILE* fin = fopen("work.txt", "r");
    FILE* fout = fopen("table.txt", "w");
    table* Table = new table;
    read_table(fin, Table);
    fclose(fin);
    write_table(fout, Table);
    fclose(fout);

    return 0;
}

