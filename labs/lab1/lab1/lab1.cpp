#include <iostream>
#include <bitset>
#include <mmintrin.h>

using namespace std;

pair<__m64, __m64> from__int8_to__int16(__m64 A);
pair<__m64, __m64> sub__int16(__m64 A_first, __m64 A_second, __m64 B_first, __m64 B_second);
pair<__m64, __m64> add__int16(__m64 A_first, __m64 A_second, __m64 B_first, __m64 B_second);
void print__m64_i16(__m64 a);
__m64 from__int8_to__m64(char* A);
pair<__m64, __m64> from__int16_to__m64(short* A);


int main()
{
	setlocale(LC_ALL, "Russian");
	__int8 A[8] = { -127, 127, 1, 1, 2, 1, 1, 1 };
	__int8 B[8] = { 127, 0, 1, 1, 1, 1, 1, 1 };
	__int8 C[8] = { 1, 127, 127, 2, 1, 1, 1, 1 };
	__int16 D[8] = { 0, 0, 0, 0, 1, 1, 1, 1 };
	__int8 zero[8] = { 0 };

	cout << "Ожидаемый результат:\n";
	for (int i = 0; i < 8; ++i) {
		printf("%d ", (A[i] - B[i] + C[i] - D[i]));
	}
	cout << endl;

	__m64 A_mmx = from__int8_to__m64(A);
	__m64 B_mmx = from__int8_to__m64(B);
	__m64 C_mmx = from__int8_to__m64(C);

	auto d = from__int16_to__m64(D);
	auto a = from__int8_to__int16(A_mmx);
	auto b = from__int8_to__int16(B_mmx);
	auto c = from__int8_to__int16(C_mmx);


	a = sub__int16(a.first, a.second, b.first, b.second); // A = A-B
	c = sub__int16(c.first, c.second, d.first, d.second); // C = C-D
	d = add__int16(a.first, a.second, c.first, c.second); // D = A+D

	cout << "Фактический результат: \n";
	print__m64_i16(d.first);
	print__m64_i16(d.second);
	
	//Ниже - код на ассемблере, который я вам сдавал
	// F = (A-B)+(C-D)
	
	//__asm {
	//	; __int8 A to __int16 A
	//	pxor mm0, mm0
	//	movq mm1, A
	//	movq mm2, A
	//	pcmpgtb mm0, mm1
	//	punpcklbw mm1, mm0
	//	punpckhbw mm2, mm0

	//	; __int8 B to __int16 B
	//	movq mm0, zero
	//	movq mm3, B
	//	movq mm4, B
	//	pcmpgtb mm0, mm3
	//	punpcklbw mm3, mm0
	//	punpckhbw mm4, mm0

	//	psubsw mm1, mm3
	//	psubsw mm2, mm3

	//	lea eax, F
	//	movq[eax], mm1
	//	movq[eax + 8], mm2


	//	; __int8 C to __int16 C
	//	movq mm0, zero
	//	movq mm1, C
	//	movq mm2, C
	//	pcmpgtb mm0, mm1
	//	punpcklbw mm1, mm0
	//	punpckhbw mm2, mm0

	//	; D = C - D
	//	lea eax, D
	//	movq mm3, [eax]
	//	movq mm4, [eax + 8]
	//	psubsw mm1, mm3
	//	psubsw mm2, mm4
	//	movq[eax], mm1
	//	movq[eax + 8], mm2
	//	emms


	//	lea eax, F
	//	lea ebx, D
	//	movq mm1, [eax]
	//	movq mm2, [eax + 8]
	//	movq mm3, [ebx]
	//	movq mm4, [ebx + 8]

	//	paddsw mm1, mm3
	//	paddsw mm2, mm4
	//	movq[eax], mm1
	//	movq[eax + 8], mm2
	//	emms
	//}
}

pair<__m64, __m64> from__int8_to__int16(__m64 A) {
	__m64 mm0 = _mm_xor_si64(A, A);
	__m64 mask = _m_pcmpgtb(mm0, A);
	__m64 left = _m_punpcklbw(A, mask);
	__m64 right = _m_punpckhbw(A, mask);
	return make_pair(left, right);
}

pair<__m64, __m64> sub__int16(__m64 A_first, __m64 A_second, __m64 B_first, __m64 B_second) {
	A_first = _m_psubsw(A_first, B_first);
	A_second = _m_psubsw(A_second, B_second);
	return make_pair(A_first, A_second);
}

pair<__m64, __m64> add__int16(__m64 A_first, __m64 A_second, __m64 B_first, __m64 B_second) {
	A_first = _m_paddsw(A_first, B_first);
	A_second = _m_paddsw(A_second, B_second);
	return make_pair(A_first, A_second);
}

void print__m64_i16(__m64 a) {
	for (int i = 0; i < 4; i++) {
		printf_s("%d ", a.m64_i16[i]);
	}
}

__m64 from__int8_to__m64(char* A) {
	__m64 result;
	__asm {
		mov eax, A
		movq mm1, [eax]
		movq result, mm1
	}
	return result;
}

pair<__m64, __m64> from__int16_to__m64(short* A) {
	__m64 result_l, result_h;
	__asm {
		mov eax, A
		movq mm1, [eax]
		movq mm2, [eax + 8]
		movq result_l, mm1
		movq result_h, mm2
	}
	return make_pair(result_l, result_h);
}
















