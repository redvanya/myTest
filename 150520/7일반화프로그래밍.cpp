#include <iostream>
using namespace std;

// 일반화 프로그래밍 (generic programming)
#if 0
int main() {

	// 검색 구간
	// 1. 시작 위치, 변위
	// 2. 시작 위치, 마지막의 다음 위치 (PTE: post-the-end)
	char* s = "abcdefg";
	char* p = strchr(s, 'c');
	if (p == 0) {
		cout << "not found" << endl;
	} else {
		cout << "found" << endl;
	}
}
#endif

#if 0	//검색 범위를 일반화 합니다
char* xstrchr(char* first, char* last, char ch) {
	while (first != last && *first != ch)	// last는 마지막의 다음 위치. 여기까지 갔다면 못찾은 것
		++first;
	return first;	// 찾았다면 (*first == ch) 그 위치를 반환, 못찾았을 경우 (first == last) 마지막의 다음 위치 반환
}

// 문제점: 검색 구간에는 일반화 되었지만 타입에 대해서는 일반화 되지 않음
int main() {
	char* str = "abcdefg";
	char* p = xstrchr(str, str + 4, 'c');	// 부분 검색 시, 마지막 위치를 넘겨주었을 경우 찾은건지 아닌지 알 수 없다
											// 마지막 위치도 검색 구간이고 null이 아니기 때문
											// 그래서 마지막의 다음을 넘김으로써 마지막의 다음인 경우 못찾은 것으로 간주
	if (p == str + 4)	cout << "not found" << endl;
	else cout << "found" << endl;
}
#endif

// 모든 타입에 대해 처리가 가능하도록 변경하기
// 문제점: 호환되는 타입에 대해 동작하지 않는다
// -> 템플릿의 인자를 하나 더 추가하기
// 문제점: array만 되고, list와 같은 것은 되지 않는다. ++ 연산이 되지 않기 때문
template <typename T1, typename T2>
T1* xfind(T1* first, T1* last, T2 ch) {
	while (first != last && *first != ch)
		++first;
	return first;
}

int main() {
		double arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };	// 5를 검색
		//double* ip = xfind(arr, arr + 5, 5);	// 5가 int형이라서 type checking에 의해 에러가 발생
												// 그러나 builtin 타입은 5와 5.0이 같다. 즉 호환됨
		double* ip = xfind(arr, arr + 5, 5);	// 그래서 타입을 두개로 지정
		if (ip == arr + 5)	cout << "not found" << endl;
		else	cout << "found" << endl;
}

//int main() {
//	char* str = "abcdefg";
//	char* p = xfind(str, str + 4, 'c');
//	if (p == str + 4)	cout << "not found" << endl;
//	else cout << "found" << endl;
//
//	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };	// 5를 검색
//	int* ip = xfind(arr, arr + 5, 5);
//	if (ip == arr + 5)	cout << "not found" << endl;
//	else	cout << "found" << endl;
//}