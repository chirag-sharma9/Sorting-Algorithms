#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

long numComparisons = 0;

//Helper function that prints the array
void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

//Insertion sort
void insertionSort(int arr[], int size) {
  int key;
  int j;
  for (int i = 1; i < size; i++) {
    key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
      numComparisons++;
    }
    arr[j + 1] = key;
  }
}

//Selection Sort
void selectionSort(int arr[], int size) {
  //find min 
  for (int i = 0; i < size; i++) {
    int minValue = arr[i];
    int minIndex = i;
    for (int j = i + 1; j < size; j++) { 
      if (arr[j] < minValue) {
	minValue = arr[j];
	minIndex = j;
	numComparisons++;
      }
    }
    //swap
    int temp = arr[i];
    arr[i] = arr[minIndex];
    arr[minIndex] = temp;
  }
}

//Helper function for Merge Sort
void merge(int arr[], int left, int middle, int right) {

  int merged[10000];
  
  int a = left; //left subarray starting index
  int b = middle + 1;  //right subarray starting index
  int c = left;  //merged subarray starting index
   
  while (a <= middle && b <= right) {
    //comaparing the left and right subarrays and adding the smaller value to the merged array
    if (arr[a] <= arr[b]) { 
      merged[c] = arr[a];
      a++;
    }
    else {
      merged[c] = arr[b];
      b++;
    }
    numComparisons++;
    c++;
  } 
  
  while (a <= middle) { //leftovers from left subarray
    merged[c] = arr[a];
    a++;
    c++;
  }
  
  while (b <= right) { //leftovers from right subarray
    merged[c] = arr[b];
    b++;
    c++;
  }
  
  for (int i = left; i <= right; i++) {
    arr[i] = merged[i];
  }
}

//Merge sort
void mergeSort(int arr[], int left, int right) {
   if (left < right) {
    int middle = (left + right)/2;
    mergeSort(arr, left, middle);
    mergeSort(arr, middle + 1, right);
    merge(arr, left, middle, right);
    numComparisons++;
   } else {
     return;
   }
}

// Helper function for heap sort
void heaple(int arr[], int size, int index) {
  int largest = index; // Index of largest number
  int left = 2 * index + 1; // Gets left child index
  int right = 2 * index + 2; // Get right child index


  if (left < size && arr[left] > arr[largest]) {
    largest = left;
  }

  if (right < size && arr[right] > arr[largest]) {
      largest = right;
  }
 
  if (largest != index) {
    swap(arr[index], arr[largest]);
    heaple(arr, size, largest);
    numComparisons++;
  }
}

// Heap Sort
void heapSort(int arr[], int size)
{
  for (int i = size / 2 - 1; i >= 0; i--) {
    heaple(arr, size, i);
  }
  
  for (int i = size - 1; i > 0; i--) {
    swap(arr[0], arr[i]);
    numComparisons++;
    heaple(arr, i, 0);
  }
}

// Helper function for quick sort
int partition(int arr[], int l, int h)
{
    int pivot = arr[h]; 
    int index = (l - 1); 
 
    for (int i = l; i <= h- 1; i++)
    {
      if (arr[i] <= pivot)
        {
            index++;   
            swap(arr[index], arr[i]);
	    numComparisons++;
        }
    }
    swap(arr[index + 1], arr[h]);
    numComparisons++;
    return (index + 1);
}
 
//Quick sort
void quickSort(int arr[], int l, int h)
{
    if (l < h)
    {
      int pi = partition(arr, l, h);
      numComparisons++;
      // Separately sort elements before
      // partition and after partition
      quickSort(arr, l, pi - 1);
      quickSort(arr, pi + 1, h);
    }
}


int main(int argc, char *argv[]) {
  
  const int ARRAY_SIZE = 10000;
  int values[ARRAY_SIZE];
  int count = 0;
  ifstream inputFile;
  string filename;
  string input;
  
  filename = argv[1];
  inputFile.open(filename);
  
  while (count < ARRAY_SIZE) {
    inputFile >> values[count];
    count++;
  }
  
  inputFile.close();
  
  cout << "(i)insertion sort (s)selection sort (m)merge sort (h)heapsort (q)quicksort" << endl;
  cout << "Enter the algorithm: ";
  cin >> input;
  
  if (input == "i") {
    cout << "Array after applying insertion sort: " << endl;
    cout << endl;
    insertionSort(values, ARRAY_SIZE);
    printArray(values, ARRAY_SIZE);
    cout << "#insertion sort comparisons: " << numComparisons << endl;
  } else if (input == "s") {
    cout << "Array after applying selection sort: " << endl;
    cout << endl;
    selectionSort(values, ARRAY_SIZE);
    printArray(values, ARRAY_SIZE);
    cout << "#selection sort comparisons: " << numComparisons << endl;
  } else if (input == "m") {
    cout << "Array after applying  merge sort" << endl;
    cout << endl;
    mergeSort(values, 0, 9999);
    printArray(values, ARRAY_SIZE);
    cout << "#merge sort comparisons: " << numComparisons << endl;
  } else if (input == "h") {
    cout << "Array after applying heap sort" << endl;
    cout << endl;
    heapSort(values, ARRAY_SIZE);
    printArray(values, ARRAY_SIZE);
    cout << "#heap sort comparisons: " << numComparisons << endl;
  } else if (input == "q") {
    cout << "Array after applying quick sort" << endl;
    cout << endl;
    mergeSort(values, 0, 9999);
    printArray(values, ARRAY_SIZE);
    cout << "#quick sort comparisons: " << numComparisons << endl;
  } else {
    cout << "Inavlid algorithm entered" << endl;
  }
  
}
