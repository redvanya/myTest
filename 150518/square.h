#ifndef __SQUARE_H__
#define __SQUARE_H__

// extern "C" : name mangling을 하지 마라
#ifdef __cplusplus	// 산업 표준: c++ 컴파일러라면 모두 가지고 있다
extern "C" {
#endif

	int square(int);

#ifdef __cplusplus
}
#endif

#endif