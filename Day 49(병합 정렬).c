#include <stdio.h>

// 오늘의 문법 설명: "끝까지 쪼개고, 합칠 때 정렬한다"
// 어제 배운 퀵 정렬이 '피벗'이라는 대장을 기준으로 대략 나누고 정렬했다면, 병합 정렬(Merge Sort)은 아주 계획적입니다.
// 일단 배열을 원소가 1개가 될 때까지 무조건 반으로 쪼개버린 뒤, 다시 합치는 과정에서 순서를 맞추는 방식입니다.

// 분할(Divide): 배열을 더 이상 나눌 수 없을 때까지 절반으로 계속 나눕니다.
// 정복/합병(Merge): 쪼개진 두 그룹을 비교하며 **작은 순서대로 새 바구니(임시 배열)**에 옮겨 담습니다.
// 특징: 데이터가 어떻게 생겼든 상관없이 항상 똑같은 시간($O(N \log N)$)이 걸리는 아주 '정직한' 정렬입니다.

int sorted[8]; // 전역 변수 선언

void merge(int arr[], int L, int mid, int R) {
	int i = L;
	int j = mid + 1;
	int k = L;

	while (i <= mid && j <= R) {
		if (arr[i] < arr[j]) {
			sorted[k] = arr[i]; // 더 키가 작은 선수(if문에서 arr[i]가 더 작았으니)를 sorted[k] 자리에 세우기.
			i++; // 왼쪽이 작았으니 왼쪽은 다음 선수로 넘어감.
		}
		else { // arr[i]와 arr[j]가 똑같으면 뭐가 들어가도 상관 없으니 여기서 처리.
			sorted[k] = arr[j]; // 더 작은 선수 (arr[j]) 투입.
			j++; // 오른쪽이 작았으니 오른쪽 다음 선수로.
		}
		k++; // 빈 자리를 채웠으니 다음 칸으로.
	}

	// [2라운드: 잔당 소탕] 💡 수정 2: 통째로 추가된 로직입니다!
	// 만약 왼쪽 팀(i)이 아직 mid 이하로 남아있다면? 다 털어 넣기!
	while (i <= mid) {
		sorted[k] = arr[i];
		i++;
		k++;
	}
	// 만약 오른쪽 팀(j)이 아직 R 이하로 남아있다면? 다 털어 넣기!
	while (j <= R) {
		sorted[k] = arr[j];
		j++;
		k++;
	}

	for (int x = L; x <= R; x++) {
		arr[x] = sorted[x]; // arr 배열에 sorted 배열을 그대로 복사.
	}
}

void mergeSort(int arr[], int L, int R) {
	if (L < R) {
		int mid = (L + R) / 2;
		mergeSort(arr, L, mid);
		mergeSort(arr, mid + 1, R); // mid까지는 왼쪽에서 처리. mid 다음칸부터 오른쪽에서 처리하기에 mid + 1
		merge(arr, L, mid, R);
	}
}

int main() {
	int arr[8] = { 38, 27, 43, 3, 9, 82, 10, 19 };
	printf("[정렬 전 배열]\n");
	for (int i = 0; i < 8; i++) {
		printf("%d ", arr[i]);
	}

	mergeSort(arr, 0, 7);

	printf("\n[정렬 후 배열]\n");
	for (int i = 0; i < 8; i++) {
		printf("%d ", arr[i]);
	}
	return 0;
}