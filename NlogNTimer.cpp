#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
using namespace std;


const int MAX = 10000000;
const int INCREMENT = 100000;

void merge( int arr[], int lb, int mid, int ub );
void mergeSort( int arr[], int lb, int ub );
void quickSort(int arr[], int left, int right);

int main()
{
   int size = 1000;
   ofstream fout("MergeSortData.txt");
   ofstream fout2("QuickSortData.txt");
   
   for (int i = size; size <= MAX; size+= INCREMENT)
   {
      int* numbers = new int[size];
   
      for(int i = 0; i < size; i++)
         numbers[i] = i;
   
      // shuffle all elements in numbers
      random_shuffle(numbers, numbers + size);
      
      int* numbers2 = new int[size];
      //copy shuffled array into new array
      for (int i = 0; i < size; i++)
         numbers2[i] = numbers[i];
   
      clock_t start;
      clock_t end;

      start = clock();
      mergeSort(numbers, 0, size - 1);
      end = clock();
      
      fout << "Size: " << size << " " << "Time: "
           << (double)(end - start)/CLOCKS_PER_SEC << " seconds" << endl;
      delete[] numbers;

      start = clock();
      quickSort(numbers2, 0, size - 1);
      end = clock();
      
      fout2 << "Size: " << size << " " << "Time: "
            << (double)(end - start)/CLOCKS_PER_SEC << " seconds" << endl;
      delete[] numbers2;   
   }
   fout.close();
   fout2.close();
   return 0;
}

void merge( int arr[], int lb, int mid, int ub )
{
   int i, j;
   int size1 = mid - lb + 1;
   int size2 = ub - mid;

    int* tmpArray1 = new int[size1];
    int* tmpArray2 = new int[size2];

    for( i=0; i<size1; i++ )
    {
        tmpArray1[i] = arr[lb + i]; 
    }

    for( j=0; j<size2; j++ )
    {
        tmpArray2[j] = arr[mid + 1 + j];
    }

    i = 0;
    j = i;

    for( int k=lb; k<=ub; k++ )
    {
        if (i == size1) // HANDLES THE CASE WHEN FIRST RANGE IS SMALLER
        {
            arr[k] = tmpArray2[j];
            j++;
        }
        else if (j == size2) // HANDLES THE CASE WHEN SECOND RANGE IS SMALLER
        {
            arr[k] = tmpArray1[i];
            i++;
        }
        else if ( tmpArray1[i] < tmpArray2[j] )
        {
            arr[k] = tmpArray1[i];
            i++;
        }
        else
        {
            arr[k] = tmpArray2[j];
            j++;
        }
    }

    delete[] tmpArray1;
    delete[] tmpArray2;
}

void mergeSort( int arr[], int lb, int ub )
{
    if (ub - lb > 1)
    {
        int mid = (lb + ub) /  2;
        mergeSort(arr, lb, mid);
        mergeSort(arr, mid + 1, ub);
        merge(arr, lb, mid, ub);
    } 
    else // sort a trivial range of 2 elements
    {
        if (arr[ub] < arr[lb])
        {
            int tmp = arr[ub];
            arr[ub] = arr[lb];
            arr[lb] = tmp;
        }
    }
}

void quickSort (int arr[], int left, int right)
{
   int i = left;
   int j = right;
   int temp;
   int pivot = arr[(left + right) / 2];

   while (i <= j)
   {
      while (arr[i] < pivot)
         i++;
      while (arr[j] > pivot)
         j--;
      if (i <= j)
      {
         temp = arr[i];
         arr[i] = arr[j];
         arr[j] = temp;
         i++;
         j--;
      }
   }
   
   if (left < j)
      quickSort(arr, left, j);
   if (i < right)
      quickSort(arr, i, right);
}
