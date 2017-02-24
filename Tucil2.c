#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "boolean.h"

/* Variabel Global	*/
int array[1000000];
int Neff = 0;

/* Memindahkan file eksternal ke dalam array di variabel global	*/
void loadfile()
{

    FILE *input;
    int i;
    input = fopen("input.txt", "r");

    while((Neff < 999999) && !(feof(input)))
	{
		fscanf(input, "%d\n", &array[Neff]);
		Neff++;
	}
	fclose(input);
}

/* Awalan dari perhitungan waktu */
void start(double *begin)
{
  *begin = (double) clock();
}

/* Akhiran dari perhitungan waktu */
void stop(double *end)
{
  start(end);
}

/* Prosedur pengurutan dengan menggunakan Selection Sort	*/
void SelectionSort()
{
	int i,j,imaks,temp;
	/* Loop untuk menentukan nilai terbesar awal */
	for (i = Neff; i >= 1; i--)
	{
		imaks = 0;
		/* Loop pencarian untuk dibandingkan dengan nilai terbesar awal */
		for (j = 1; j <= i; j++)
		{
			if(array[j] > array[imaks])
			{
				imaks = j;
			}
		}
		temp = array[imaks];
		array[imaks] = array[i];
		array[i] = temp;
	}
}

/* Prosedur pengurutan dengan menggunakan Insertion Sort */
void InsertionSort()
{
	int i, j, y;
	boolean found;
	/* Proses dimulai dari awal sampai dengan Neff secara traversal */
	for(i = 0; i <= Neff; i++)
	{
		y = array[i];
		j = i - 1;
		found = false;
		while((j >= 0) && !(found))
		{
			/* Bila indeks tidak ditemukan, indeks setelahnya akan bertambah 1 */
			if (y < array[j])
			{
				array[j+1] = array[j];
				j--;
			}
			/* Bila ditemukan, indeks akan tetap, dan found berubah menjadi true */
			else
			{
				found = true;
			}
		}
		/* Proses penukaran */
		array[j+1] = y;
	}
}

/* Prosedur pengurutan dengan menggunakan Quick Sort */
void QuickSort(int f, int l)
{
    int i, j, pivot, temp;
	/* Tentukan elemen first dan last terlebih dahulu */
	if(f < l)
	{
         pivot = f;
         i = f;
         j = l;
         /* Disaat i < j, akan dilakukan beberapa pengujian */
         while(i < j)
         {
			/* Bila i lebih kecil dari pivot, indeks i bergerak maju */ 
            while(array[i] <= array[pivot] && i < l)
            {
                i++;
            }
            /* Bila j lebih besar dari pivot, indeks j bergerak mundur */
            while(array[j] > array[pivot])
			{
				j--;
            }
            /* Apabila i < j sampai dengan mereka bertemu di pivot, i dan j akan ditukar */
            if(i < j)
            {
				temp = array[i];
                array[i] = array[j];
                array[j] = temp;
             }
         }
         /* Akan dilakukan penukaran apabila j = i, terhadap pivot */
         temp = array[pivot];
         array[pivot] = array[j];
         array[j] = temp;
         
         /* Melakukan quick sort di sisi kiri dan kanan array */
         QuickSort(f, j-1);
         QuickSort(j+1, l);
    }
}

/* Prosedur yang digunakan untuk membantu prosedur MergeSort */
/* Membantu dalam hal penggabungan */
/* Persoalan ditinjau dari sisi kiri dan kanan array */
void Merge(int l, int m, int r)
{
	/* Array menggunakan array sementara untuk mempermudah penyimpanan */
	int temp[Neff];
	int i, k1, k2;
	
	/* Inisialisasi terhadap sisi kiri dan kanan array */
	k1 = l;
	k2 = m + 1;
	i = l;
	/* Beberapa penukaran */
	while((k1 <= m) && (k2 <= r))
	{
		/* Perubahan bila terdapat nilai yang lebih besar */
		if(array[k1] <= array[k2])
		{
			temp[i] = array[k1];
			k1++;
		}
		else
		{
			temp[i] = array[k2];
			k2++;
		}
		i++;
	}
	/* Perlakuan untuk sisi kiri */
	while(k1 <= m)
	{
		temp[i] = array[k1];
		k1++;
		i++;
	}
	
	/* Perlakuan untuk sisi kanan */
	while(k2 <= r)
	{
		temp[i] = array[k2];
		k2++;
		i++;
	}

	/* Pengembalian nilai dari array sementara ke array asli */
	for (i = l; i <= r; i++)
	{
		array[i] = temp[i];
	}
}

/* Prosedur pengurutan dengan menggunakan Merge Sort */
void MergeSort(int i, int j)
{
	int k;
	if (i < j)
	{
		/* Pembagian array */
		k = ((i + j - ((i + j) % 2))/2);
		/* Prosedur merge dan penggabungan */
		MergeSort(i, k);
		MergeSort(k + 1, j);
		Merge(i, k, j);
	}
}

/* Program utama */
int main()
{
	double begin, end;
	int i;
    loadfile();
    printf("\n");
    start(&begin);
    InsertionSort();
    stop(&end);
    for(i = 1; i <= Neff; i++)
	{
		printf("%d\n", array[i]);
	}
    /* Perhitungan waktu */
    printf("Durasi : %lg milidetik\n",(end-begin)*1000/CLOCKS_PER_SEC);
    printf("\n");
    return 0;
}
