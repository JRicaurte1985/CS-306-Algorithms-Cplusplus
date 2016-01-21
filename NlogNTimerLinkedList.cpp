#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
using namespace std;


const int MAX = 10000000;
const int INCREMENT = 100000;

struct node
{
    int data;
    node *next;
};

void makeRandomList(node*, int);
void displayList(node*);
node* merge(node* list1, node* list2,int size1,int size2);
node* mergesort(node *start, int size);

int main()
{
   int size = 100000;
   ofstream fout("MergeSortLinkedListData.txt");
   ofstream fout2("QuickSortLinkedListData.txt");
   node* head;
   srand(time(NULL));
   
   for (int i = size; size <= MAX; size+= INCREMENT)
   {
      makeRandomList(head, size);
      displayList(head);
      clock_t start;
      clock_t end;

      start = clock();
      node* newhead = mergesort(head, size);
      end = clock();
      
      node* temp = newhead;
      int count = 0;
      while(count!=size-1)
      {
         temp=temp->next;
         count++;
      }
      temp->next = NULL;
      cout << "Sorted list is" << endl;
      displayList(newhead);
      
      fout << "Size: " << size << " " << "Time: "
           << (double)(end - start)/CLOCKS_PER_SEC << " seconds" << endl;
      
      //start = clock();
      //quickSort(numbers2, 0, size - 1);
      //end = clock();
      
      // fout2 << "Size: " << size << " " << "Time: "
      //<< (double)(end - start)/CLOCKS_PER_SEC << " seconds" << endl;
      
   }
   fout.close();
   fout2.close();
   return 0;
}

// Helper function to make a Random list
void makeRandomList(node* head, int len)
{
    int count = 0;
    node* current;

    while(count!=len)
    {
        if(count==0)
        {
            head = new node;
            head->data = rand()%len;
            head->next = NULL;
            current = head;
        }
        else
        {
            node* temp = new node;
            temp->data = rand()%len;
            temp->next = NULL;
            current->next = temp;
            current = temp;
        }
        count++;
    }
}

// Helper function to Display the list
void displayList(node* head)
{
    node* temp = head;
    while(temp!=NULL)
    {
        cout << temp->data << "-";
        temp = temp->next;
    }
    cout << endl;
}

// It merges two sorted lists into one list
node* merge(node* list1, node* list2, int size1, int size2)
{
    // Trivial cases
    if(size1 == 0)
        return list2;

    if(size2 == 0)
        return list1;

    // Choose the bigger element from the front of the two lists
    // and put it at the head of the new list and call merge 
    // again with the sub lists

    if(list1->data < list2->data || list1->data == list2->data)
    {
        list1->next = merge(list1->next,list2,size1-1,size2);
        return list1;
    }
    else
    {
        list2->next = merge(list1,list2->next,size1,size2-1);
        return list2;
    }
}

// It calls mergesort over two smaller sublists that are half
// in size of the original list and then calls merge over them 
// to join them again. It does this untill the size of the list 
// is equal to one and from that point onwards the merging of the
// sublists is done using the merge function
node* mergesort(node *start, int size)
{
    if(size > 1)
    {
        int midSize = size/2;
        int count = midSize;
        node* mid = start;
        while(count)
        {
            mid = mid->next;
            count--; 
        }
        return merge(mergesort(start,midSize),
                     mergesort(mid,size - midSize),midSize,size - midSize);
    }
    else
        return start;
}

