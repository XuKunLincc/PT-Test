#include <stdio.h>
#include <time.h>

double test();

int main(int argc, char *agrv[]){
	double sum, now, average, max = 0.0, min = 0Xffff;
	int i  = 1000, count = 0;

	for( ; count < 10; count++){
		i = 1000;
		sum = 0;
		average = 0;
		max = 0.0;
		min = 0Xffff;

		while(i){
			i--;
			now = test();

			if (now < min)
				min = now;
			if (now > max)
				max = now;

			sum += now;	// get the all value sum
		}

		average = sum / 1000;
		printf("the average value was: %lfms max:%lfms min:%lfms\n", average, max, min);
	}
	return 0;
}


double test(){
	volatile int count = 0;
	clock_t start, end;
	start = clock();
	count++;

#ifdef VOLATILE

	__asm__ __volatile__ (
		"ldr r2, =999999 \n\t"
		:::"r2"
	);	// ARM中立即数不能大于8位

	__asm__ __volatile__(
	"\n.LOOP1: \n\t"
	"add r1, %1, #1 \n\t"
	"str r1, %0 \n \t"
	"cmp r1, r2 \n\t"
	"bne .LOOP1"
	:"=m"(count)
	:"r"(count)
	:"r0","r1"
	);

#else

	__asm__ __volatile__(
		"mov r1, %0 \n\t"
		"ldr r2, =999999 \n\t"
		:
		:"r"(count)
		:"r1","r2"
	);
	__asm__ __volatile__(
		"\n.LOOP2: \n\t"
		"add r1, r1, #1 \n\t"
		"cmp r1, r2 \n\t"
		"bne .LOOP2 \n\t"
		"str r1, %0 \n\t"
		:"=m"(count)
		:
		:
	);
#endif
	end = clock();
	return (double)(end - start) /  (double)CLOCKS_PER_SEC * 1000;
}
