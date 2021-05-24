#include<stdio.h>
#define INF 999

typedef int ElemType;

/*
* Auther: Au-c
* Date: 2021-5-24
* Blog: https://au-c.github.io/Blog/
* Github: https://github.com/Au-c
*/

/*
* �򵥲�������
* @param arr {Array} Ŀ������
* @param n {int} Ԫ������
*/
void InsertSort(ElemType arr[], int n)
{
	int i, j;
	for (i = 2; i <= n; i++)
	{
		arr[0] = arr[i];
		if (arr[0] < arr[i - 1])
		{
			// ǰ��Ԫ�غ���
			for (j = i - 1; arr[j] > arr[0]; j--)
			{
				arr[j + 1] = arr[j];
			}
			// ���뵱ǰԪ��
			arr[j + 1] = arr[0];
		}
	}
}

/*
* �۰��������
* @param arr {Array} Ŀ������
* @param n {int} Ԫ������
*/
void BInsertSort(ElemType arr[], int n)
{
	int i, j, low, high, mid;
	for (i = 2; i <= n ; i++)
	{
		arr[0] = arr[i];
		low = 1;
		high = i - 1;
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (arr[0] < arr[mid]) high = mid - 1;
			else low = mid + 1;
		} // ����ѭ����high < key < low
		for (j = i - 1; j >= high + 1; j--) arr[j + 1] = arr[j]; // Ԫ�غ���
		arr[high + 1] = arr[0];
	}
}

/*
* ϣ������ - ����
* @param arr {Array} Ŀ������
* @param dk {int} ����
* @param n {int} Ԫ������
*/
void ShellInsert(ElemType arr[], int dk, int n)
{
	int i, j;
	for (i = dk + 1; i <= n; i++)
	{
		if (arr[i - dk] > arr[i])
		{
			arr[0] = arr[i];
			// Ԫ�غ���
			for (j = i - dk; j > 0 && arr[j] > arr[0]; j-=dk)
			{
				arr[j + dk] = arr[j];
			}
			arr[j + dk] = arr[0];
		}
	}
}
/*
* ϣ������
* @param arr {Array} Ŀ������
* @param dk {Array} ��������
* @param n {int} arr[] ���鳤��
* @param t {int} dk[] ���鳤��
*/
void ShellSort(ElemType arr[], int dk[], int n, int t)
{
	for (int i = 0; i < t; i++)
	{
		ShellInsert(arr, dk[i], n);
	}
}

/*
* ð������
*/
void BubbleSort(ElemType arr[], int n)
{
	int i, j, flag;
	for (i = 1; i <= n; i++)
	{
		flag = 0;
		for (j = 1; j <= n - i; j++) {
			if (arr[j] > arr[j + 1])
			{
				// ��������
				arr[0] = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = arr[0];
				flag = 1;
			}
		}
		if (flag == 0) break;
	}
}

/*
* �������� - ����: ����Ĭ��Ϊ��Ԫ��
*/
int Partition(ElemType arr[], int low, int high)
{
	arr[0] = arr[low];
	while (low < high)
	{
		while (low < high && arr[high] >= arr[0]) --high;
		arr[low] = arr[high];
		while (low < high && arr[low] <= arr[0]) ++low;
		arr[high] = arr[low];
	}
	arr[low] = arr[0];
	return low;
}
/*
* ��������
* @param arr {Array} Ŀ������
* @param low {int} ����������Ԫ������
* @param high {int} ��������ĩβԪ������ 
*/
void QuickSort(ElemType arr[], int low, int high)
{
	if (low < high) 
	{
		int pivotloc = Partition(arr, low, high);
		QuickSort(arr, low, pivotloc - 1);
		QuickSort(arr, pivotloc + 1, high);
	}
}

/*
* ѡ������
* @param arr {Array} Ŀ������
* @param n {int} Ԫ������
*/
void SelectSort(ElemType arr[], int n)
{
	int i, j, min;
	// ���ʣ��һԪ������Ƚ�
	for (i = 1; i < n; i++)
	{
		min = i;
		for (j = i + 1; j <= n; j++)
		{
			if (arr[j] < arr[min]) min = j;
		}
		if (min != i)
		{
			// ��������
			arr[0] = arr[i];
			arr[i] = arr[min];
			arr[min] = arr[0];
		}
	}
}

/*
* tool: ��ӡ����
* @param flag {int} 0: ��ӡԭʼ����; 1: ��ӡ���������
* @param arr {Array} Ŀ������
* @param n {int} Ԫ������
*/
void PrintArr(int flag, ElemType arr[], int n)
{
	int i;
	if (flag == 0) {
		printf("ԭʼ����:\n");
	}
	else if (flag == 1)
	{
		printf("���������:\n");
	}
	else {
		printf("���ݴ���\n");
	}
	for (i = 1; i <= n; i++)
	{
		printf("%d\t", arr[i]);
	}
	printf("\n");
}
int PrintCopyRight()
{
	printf("Auther: Au-c\n");
	printf("Date: 2021-5-24\n");
	printf("Blog: https://au-c.github.io/Blog/\n");
	printf("Github: https://github.com/Au-c\n");
	return 1024;
}

int main()
{
	PrintCopyRight();
	printf("\n******************** Straight Insertion Sort ********************\n");
	int arr1[] = { INF, 1, 45, 6, 2, 67, 90, 3, 13, 30, 5, 56 };
	PrintArr(0, arr1, 11);
	InsertSort(arr1, 11);
	PrintArr(1, arr1, 11);
	printf("\n******************** Binary Insertion Sort ********************\n");
	int arr2[] = { INF, 1, 45, 6, 2, 67, 90, 3, 13, 30, 5, 56 };
	PrintArr(0, arr2, 11);
	BInsertSort(arr2, 11);
	PrintArr(1, arr2, 11);
	printf("\n******************** Shell's Sort ********************\n");
	int arr3[] = { INF, 49, 38, 65, 97, 76, 13, 27, 49, 55, 4};
	int dk[] = {5, 3, 1};
	PrintArr(0, arr3, 10);
	ShellSort(arr3, dk, 10, 3);
	PrintArr(1, arr3, 10);
	printf("\n******************** Bubble Sort ********************\n");
	int arr4[] = { INF, 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
	PrintArr(0, arr4, 10);
	BubbleSort(arr4, 10);
	PrintArr(1, arr4, 10);
	printf("\n******************** Quick Sort ********************\n");
	int arr5[] = { INF, 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
	PrintArr(0, arr5, 10);
	QuickSort(arr5, 1, 10);
	PrintArr(1, arr5, 10);
	printf("\n******************** Simple Selection Sort ********************\n");
	int arr6[] = { INF, 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
	PrintArr(0, arr6, 10);
	SelectSort(arr6, 10);
	PrintArr(1, arr6, 10);
}