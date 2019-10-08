#include <ctime>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <string>

using namespace std;

const int SIZE = 10;
const int SIZE2 = 100;
const int SIZE3 = 1000;
const int seconds = 0;

int comparisonCounter = 0;

time_t time0;
time_t time1;

// A utility function to print an array of size n 
void writeArray(int arr[], string sortType, int max, time_t time, int comparisonCounter)
{
	//Creates file object for a given sort of a given size
	ofstream file;
	file.open(sortType + "_Size" + to_string(max) + ".txt");

	for (int i = 0; i < max; i++) {
		//cout << arr[i] << " ";
		//cout << "\n";
		file << arr[i] << ", "; 
		
	}
	file << "\nElapsed sorting time for " << sortType << ": " << time << " microseconds.\n";
	file << "Number of comparisons for " << sortType << ": " << comparisonCounter << " comparisons performed.\n\n";
	
	

}

void populateArray(int arr[], int max)
{
	//populate array with random numbers
	srand((unsigned)time(0));
	for (int i = 0; i < max; i++)
	{
		arr[i] = (rand() % 1000) + 1;
	}
}

//*************
//MergeSort - O(n log n)
//*************

// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int *L = new int[n1];
	int *R = new int[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;

		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;

		//****increment comparison counter****
		comparisonCounter += 1;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
	delete[] L;
	delete[] R;
}


/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{

	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}


}

void callMergeSort(int arr[], int l, int r, int max)
{
	//Reset comparison counter
	comparisonCounter = 0;

	auto time0 = std::chrono::high_resolution_clock::now(); // get current time.
	mergeSort(arr, l, r);
	auto time1 = std::chrono::high_resolution_clock::now(); // get current time after mergeSort().
	auto time_elapsed = time1 - time0;
	printf("Sorted array using Merge sort:    \n");
	cout << "Elapsed sorting time for Merge Sort: "<< time_elapsed / std::chrono::microseconds(1) << " microseconds.\n";
	cout << "Number of comparisons for Merge Sort: " << comparisonCounter << " comparisons performed.\n\n";
	writeArray(arr, "merge_sort", max, time_elapsed / std::chrono::microseconds(1), comparisonCounter);


}

//---------------------------------------------------------------------------------

//*************
//InsertionSort - Best case = O(n), Average case = O(n^2)
//*************

void insertionSort(int arr[], int max)
{
	//Reset comparison counter
	comparisonCounter = 0;

	auto time0 = std::chrono::high_resolution_clock::now(); // get current time.

	int i, key, j;

	for (i = 1; i < max; i++) {
		key = arr[i];
		j = i - 1;
		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */

		

		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;

			//****Increment comparison counter****
			comparisonCounter += 1;

		}

		arr[j + 1] = key;
	}

	auto time1 = std::chrono::high_resolution_clock::now(); // get current time after time pass.
	auto time_elapsed = time1 - time0;
	printf("Sorted array using Insertion sort:    \n");
	cout << "Elapsed sorting time for Insertion Sort: " << time_elapsed / std::chrono::microseconds(1) << " microseconds.\n";
	cout << "Number of comparisons for Insetion Sort: " << comparisonCounter << " comparisons performed.\n\n";
	writeArray(arr, "insertion_sort", max, time_elapsed / std::chrono::microseconds(1), comparisonCounter);

}

//Function to pass already sorted array and get the best case time
void insertionSortBest(int arr[], int max)
{
	//Reset comparison counter
	comparisonCounter = 0;

	auto time0 = std::chrono::high_resolution_clock::now(); // get current time.

	int i, key, j;

	for (i = 1; i < max; i++) {
		key = arr[i];
		j = i - 1;
		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */


		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;

			//****Increment comparison counter****
			comparisonCounter += 1;

		}

		arr[j + 1] = key;
	}

	auto time1 = std::chrono::high_resolution_clock::now(); // get current time after time pass.
	auto time_elapsed = time1 - time0;
	printf("Sorted array using Insertion sort:    \n");
	cout << "Elapsed sorting time for Insertion Sort BEST CASE: " << time_elapsed / std::chrono::microseconds(1) << " microseconds.\n";
	cout << "Number of comparisons for Insertion Sort BEST CASE: " << comparisonCounter << " comparisons performed.\n\n";
	writeArray(arr, "insertion_sort_best", max,time_elapsed / std::chrono::microseconds(1), comparisonCounter );

}

//----------------------------------------------------------------------------------

//*************
//HeapSort - O(n log n)
//*************

// To heapify a subtree rooted with node i which is 
// an index in arr[]. n is SIZE2 of heap 
void heapify(int arr[], int n, int i)
{
	int largest = i; // Initialize largest as root 
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 

					   // If left child is larger than root 
	if (l < n && arr[l] > arr[largest])
		largest = l;

	// If right child is larger than largest so far 
	if (r < n && arr[r] > arr[largest])
		largest = r;

	// If largest is not root 
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// Recursively heapify the affected sub-tree 
		heapify(arr, n, largest);
	}
}

// main function to do heap sort 
//O(nLogn)
void heapSort(int arr[], int max)
{
	//Reset comparison counter
	comparisonCounter = 0;

	auto time0 = std::chrono::high_resolution_clock::now(); // get current time.

				  // Build heap (rearrange array) 
	for (int i = max / 2 - 1; i >= 0; i--)
		heapify(arr, max, i);

	// One by one extract an element from heap 
	for (int i = max - 1; i >= 0; i--)
	{
		//****Increment comparison counter****
		comparisonCounter += 1;

		// Move current root to end 
		swap(arr[0], arr[i]);

		// call max heapify on the reduced heap 
		heapify(arr, i, 0);
	}

	auto time1 = std::chrono::high_resolution_clock::now(); // get current time after time pass.
	auto time_elapsed = time1 - time0;
	printf("Sorted array using Heap sort:    \n");
	cout << "Elapsed sorting time for Heap Sort: " << time_elapsed / std::chrono::microseconds(1) << " microseconds.\n";
	cout << "Number of comparisons for Heap Sort: " << comparisonCounter << " comparisons performed.\n\n";
	writeArray(arr, "heap_sort", max, time_elapsed / std::chrono::microseconds(1), comparisonCounter);

}

//------------------------------------------------------------------------------

//*************
//QuickSort - O(n log n)
//*************

// A utility function to swap two elements  
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partitionWorstCase(int arr[], int low, int high)
{
	int pivot = arr[high]; // pivot  
	int i = (low - 1); // Index of smaller element  

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot  
		if (arr[j] < pivot)
		{
			i++; // increment index of smaller element  
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

int partition(int arr[], int low, int high)
{
	int mid = low + (high - low) / 2;
	int pivot = arr[mid]; // pivot  
	int i = (low - 1); // Index of smaller element  

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot  
		if (arr[j] < pivot)
		{
			i++; // increment index of smaller element  
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		//****Increment comparison counter****
		comparisonCounter += 1;

		// Separately sort elements before  
		// partition and after partition  
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void quickSortWorstCase(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partitionWorstCase(arr, low, high);

		//****Increment comparison counter****
		comparisonCounter += 1;

		// Separately sort elements before  
		// partition and after partition  
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}


void callQuickSort(int arr[], int low, int high, int max)
{
	//Reset comparison counter
	comparisonCounter = 0;

	auto time0 = std::chrono::high_resolution_clock::now(); // get current time.
	quickSort(arr, low, high);
	auto time1 = std::chrono::high_resolution_clock::now(); // get current time after mergeSort().
	auto time_elapsed = time1 - time0;
	printf("Sorted array using Quick sort:    \n");
	cout << "Elapsed sorting time for Quick Sort: " << time_elapsed / std::chrono::microseconds(1) << " microseconds.\n";
	cout << "Number of comparisons for Quick Sort: " << comparisonCounter << " comparisons performed.\n\n";
	writeArray(arr, "Quick_Sort", max, time_elapsed / std::chrono::microseconds(1), comparisonCounter);

}


void callQuickSortWorst(int arr[], int low, int high, int max)
{
	//Reset comparison counter
	comparisonCounter = 0;
	
	auto time0 = std::chrono::high_resolution_clock::now(); // get current time.
	quickSortWorstCase(arr, low, high);
	auto time1 = std::chrono::high_resolution_clock::now(); // get current time after mergeSort().
	auto time_elapsed = time1 - time0;
	printf("Sorted array using Quick sort:    \n");
	cout << "Elapsed sorting time for Quick Sort WORST CASE: " << time_elapsed / std::chrono::microseconds(1) << " microseconds.\n";
	cout << "Number of comparisons for Quick Sort WORST CASE: " << comparisonCounter << " comparisons performed.\n\n";
	writeArray(arr, "Quick_Sort_Worst", max, time_elapsed / std::chrono::microseconds(1), comparisonCounter);

}

//-------------------------------------------------------


// Driver for sort execution.
void executeSorts(int arr[], int max)
{
	populateArray(arr, max);
	//Creates a dummy array to reset the value of arr[] to
	int* cloneArr = new int[max];
	for (int i = 0; i < max; i++)
		cloneArr[i] = arr[i];
	//writeArray(cloneArr, 'baseArray', max);
	cout << "Performing sorts for array size " << max << "...\n\n";
	insertionSort(arr, max);
	*arr = *cloneArr;
	insertionSortBest(arr, max); //Get data for best case insertion sort
	callMergeSort(arr, 0, max - 1, max);
	*arr = *cloneArr;
	heapSort(arr, max);
	*arr = *cloneArr;
	callQuickSort(arr, 0, max - 1, max);
	callQuickSortWorst(arr, 0, max - 1, max); //Get data for worst case insertion sort

	delete[] cloneArr;
	cloneArr = NULL;

}




// Driver program to test above functions. 
int main()
{
	//Initialize dynamically allocated array using SIZE constant
	int* arr = NULL;
	arr = new int[SIZE];
	executeSorts(arr, SIZE);
	cout << "Output files for array size 10 written to project directory. Please check the output for more information.\n\n\n";
	delete[] arr;
	arr = NULL;

	//Initialize dynamically allocated array using SIZE2 constant
	int* arr2 = NULL;
	arr2 = new int[SIZE2];
	executeSorts(arr2, SIZE2);
	cout << "Output files for array size 100 written to project directory. Please check the output for more information.\n\n\n";
	delete[] arr2;
	arr2 = NULL;

	//Initialize dynamically allocated array using SIZE3 constant
	int* arr3 = NULL;
	arr3 = new int[SIZE3];
	executeSorts(arr3, SIZE3);
	cout << "Output files for array size 1000 written to project directory. Please check the output for more information.\n\n\n";
	delete[] arr3;
	arr3 = NULL;

	system("pause");
	return 0;
}



//SOURCES
//------------------------------------------
//GeeksForGeeks. Insertion.
//https://www.geeksforgeeks.org/insertion-sort/
//
//Heapsort Algorithm sourced from GeeksForGeeks.org
// https://www.geeksforgeeks.org/heap-sort/
//
//Merge Sort algorithm sourced from GeeksForGeeks.org
//https://www.geeksforgeeks.org/merge-sort/
//
//Quick Sort algorithm sourced from GeeksForGeeks.org
//https://www.geeksforgeeks.org/quick-sort/
