#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <vector>
using namespace std;


const int MAX = 10000000;
const int INCREMENT = 100000;

void merge(vector<int> &vt, int p, int r);
void merge_sort(vector<int> &vt, int p, int r);
void quickSort(vector<int> &arr, int left, int right);

int main()
{
   int size = 100000;
   ofstream fout("MergeSortDataVectors.txt");
   ofstream fout2("QuickSortDataVectors.txt");
   vector<int> numbers;
   vector<int> numbers2;
   
   for (int i = size; size <= MAX; size+= INCREMENT)
   {
      for (int i = 0; i < size; i++)
         numbers.push_back(i);
          
      // shuffle all elements in numbers
      random_shuffle(numbers.begin(), numbers.end());

      numbers2 = numbers;
      
      clock_t start;
      clock_t end;
      
      start = clock();
      merge_sort(numbers, 0, size - 1);
      end = clock();
      
      fout << "Size: " << size << " " << "Time: "
           << (double)(end - start)/CLOCKS_PER_SEC << " seconds" << endl;

      start = clock();
      quickSort(numbers2, 0, size - 1);
      end = clock();
      
      fout2 << "Size: " << size << " " << "Time: "
            << (double)(end - start)/CLOCKS_PER_SEC << " seconds" << endl;
     
     numbers.clear();
     numbers2.clear();
   }
   fout.close();
   fout2.close();
   return 0;
}

void merge(vector<int> &vt, int p, int r)  
{  
    int mid = floor((p+r)/2);  
    int i1 = 0;  
    int i2 = p;  
    int i3 = mid + 1;  
  
    vector<int> t_vt;  
    t_vt.reserve(r-p+1);  
  
    while( i2 <= mid && i3 <= r)  
    {  
        if ( vt[i2] < vt[i3] )  
            t_vt[i1++] = vt[i2++];  
        else  
            t_vt[i1++] = vt[i3++];  
    }  
  
    while (i2 <= mid )  
        t_vt[i1++] = vt[i2++];  
  
    while ( i3 <= r )  
        t_vt[i1++] = vt[i3++];  
  
    for(int i = p; i <= r; i++)  
        vt[i] = t_vt[i-p];   
}  
  
/*Algorithm 
    1> Split the list into two equal parts at the middle 
    2> Apply merge_sort() on each list 
    3> Merge both the lists 
*/
void merge_sort(vector<int> &vt, int p, int r)  
{  
    if(p<r)  
    {  
        int mid = floor((p+r)/2);  
        merge_sort(vt, p, mid);  
        merge_sort(vt, mid+1, r);  
        merge(vt, p, r);  
    }  
}  

void quickSort (vector<int> &arr, int left, int right)
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
