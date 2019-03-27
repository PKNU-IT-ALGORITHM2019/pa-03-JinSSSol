#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(a,b){int tmp=a;a=b;b=tmp;}
#define MAX 1000000
#define BUFFER_LENGTH 100

void get_input_random(char filename[], int N); //테스트 파일명,크기 입력받아서 테스트 데이터파일 생성
void bubble_sort(int data[], int N);
void selection_sort(int data[], int N);
void insertion_sort(int data[], int N);
void merge_sort(int data[], int p, int r);
void merge(int data[], int p, int q, int r);
void quick_sort(int data[], int p, int r);
int partition(int data[], int p, int r);
int partition_middle(int data[], int p, int r);
int partition_random(int data[], int p, int r);
void printTable(); //파일로부터 데이터 받아 테이블 형식으로 출력

int main() {
	int N = 1000000;
	int*data = (int)malloc(MAX * sizeof(int));
	clock_t start, end;

	FILE *in_fp = fopen("input(1000000).txt", "r");
	FILE *out_fp = fopen("output.txt", "w");
	for (int i = 0; i < N; i++)
		fscanf(in_fp, "%d", &data[i]);

	start = clock(); //시작 시간
	quick_sort(data,0,N-1);
	end = clock();  //끝난 시간

	for (int i = 0; i < N; i++) {
		fprintf(out_fp, "%d\n", data[i]);
	}

	printf("시간: %lf초\n", (double)(end - start) / 1000);
	printTable();

	fclose(in_fp);
	fclose(out_fp);
	free(data);
	getchar();
	return 0;
}

void get_input_random(char filename[], int N)
{
	printf("데이터파일 이름 입력하시오: \n");
	scanf("%s", filename);
	printf("테스트 데이터의 크기를 입력하시오: \n");
	scanf("%d", &N);

	FILE *fp = fopen(filename, "w");
	srand((unsigned int)time(NULL));
	for (int i = 0; i < N; i++) {
		fprintf(fp, "%d\n", rand() % N + 1);
	}
	fclose(fp);

}

void bubble_sort(int data[], int N)
{
	for (int i = N - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (data[j] > data[j + 1])
				SWAP(data[j], data[j + 1]);
		}
	}
}

void selection_sort(int data[], int N)
{
	int max = data[0], maxI = 0;
	for (int i = N - 1; i > 0; i--) {
		for (int j = 0; j <= i; j++) {
			if (data[j] > max) {
				max = data[j];
				maxI = j;
			}
			SWAP(data[maxI], data[i]);
		}
	}
}

void insertion_sort(int data[], int N)
{
	for (int i = 1; i < N; i++) {
		int tmp = data[i];
		int j = i - 1;
		for (; j >= 0 && data[j]>tmp; j--) {
			data[j + 1] = data[j];
		}
		data[j + 1] = tmp;
	}
}

void merge_sort(int data[], int p, int r)
{
	if (p < r) {
		int q = (p + r) / 2;
		merge_sort(data, p, q);
		merge_sort(data, q + 1, r);
		merge(data, p, q, r);
	}

	return;
}

int tmp[MAX];
void merge(int data[], int p, int q, int r) // 정렬된 data[p~q],[q+1~r] 을 하나의 정렬 데이터로 병합
{
	int i = p, j = q + 1, k = p;
	while (i <= q && j <= r) {
		if (data[i] < data[j]) {
			tmp[k++] = data[i++];
		}
		else
			tmp[k++] = data[j++];
	}

	if (i <= q)
		tmp[k++] = data[i++];
	else if (j <= r)
		tmp[k++] = data[j++];

	for (int i = p; i <= r; i++)
		data[i] = tmp[i];

}

void quick_sort(int data[], int p, int r)
{
	if (p < r) {
		int q = partition_middle(data, p, r);
		quick_sort(data, p, q - 1);
		quick_sort(data, q + 1, r);
	}
	return;
}



int partition(int data[], int p, int r) //pivot(마지막 값)기준 작,큰 으로 나누고 pivot 인덱스 반환
{
	int pivot = data[r];
	int i = p - 1;        //i까지는 pivot보다 작은 수
	for (int j = p; j < r; j++) {
		if (data[j] < pivot) {
			i++;
			SWAP(data[i], data[j]);
		}
	}
	SWAP(data[i + 1], data[r]);
	return i + 1;
}

int partition_middle(int data[], int p, int r) //pivot(중간값)기준 작,큰 으로 나누고 pivot 인덱스 반환
{
	int mid = (p + r) / 2;
	int pivot, pivotIndex;
	if ((data[p] >= data[mid] && data[p] <= data[r]) || (data[p] <= data[mid] && data[p] >= data[r])) {
		pivot = data[p];
		pivotIndex = p;
	}
	else if ((data[mid] >= data[p] && data[mid] <= data[r]) || (data[mid] <= data[p] && data[p] >= data[r])) {
		pivot = data[mid];
		pivotIndex = mid;
	}
	else {
		pivot = data[r];
		pivotIndex = r;
	}

	int i = p - 1;
	for (int j = p; j <= r; j++) {
		if (data[j] < pivot) {
			i++;
			SWAP(data[i], data[j]);
			if (data[j] == pivot) pivotIndex = j;
		}
	}
	SWAP(data[i + 1], data[pivotIndex]);
	return i + 1;
}

int partition_random(int data[], int p, int r) //pivot(랜덤 값)기준 작,큰 으로 나누고 pivot 인덱스 반환
{
	int pivotIndex = (rand() % (r - p + 1) + p); //pivot은 data[p~r] 사이의 랜덤 값
	int pivot = data[pivotIndex];
	int i = p - 1;
	for (int j = p; j <= r; j++) {
		if (data[j] < pivot) {
			i++;
			SWAP(data[i], data[j]);
			if (data[i] == pivot) pivotIndex = i;
			else if (data[j] == pivot) pivotIndex = j;
		}
	}
	SWAP(data[i + 1], data[pivotIndex]);
	return i + 1;
}

void printTable() {
	typedef struct sort {
		char name[10];       //정렬 이름
		double time[6];      //걸린 시간

	}Sort;
	Sort sort[10];
	FILE *in_fp = fopen("timedata.txt", "r");
	for (int i = 0; i < 7; i++) {
		fscanf(in_fp, "%s", sort[i].name);
		for (int j = 0; j < 6; j++) {
			fscanf(in_fp, "%lf", &sort[i].time[j]);
		}
	}
	FILE*fp = fopen("time.txt", "w");
	fprintf(fp, "%15s %15s %15s %15s %15s %15s %15s\n", " ", "Random1000", "Reverse1000", "Random10000", "Reverse100000", "Random1000000", "Reverse1000000");
	for (int i = 0; i < 7; i++) {
		fprintf(fp, "%-15s ", sort[i].name);
		for (int j = 0; j < 6; j++) fprintf(fp, "%15.4f ", sort[i].time[j]);
		fprintf(fp, "\n");
	}
	fclose(in_fp);
	fclose(fp);
}
