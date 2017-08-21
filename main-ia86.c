#include <stdio.h>
#include <time.h>

double test();

int main(int argc, char *agrv[]){
	double sum, now, average, max = 0.0, min = 1e9;
	int i  = 1000;
	sum = 0;
	average = 0;

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
	return 0;
}


double test(){
	volatile int count = 0;
	clock_t start, end;
	start = clock();

#ifdef VOLATILE
	__asm__ __volatile__(
	"\n.LOOP1: \n\t"
	"movl %0, %%eax \n\t"
	"addl $1, %%eax \n\t"
	"movl %%eax, %0 \n\t"
	"cmpl $999999, %%eax \n\t"
	"jle .LOOP1"
	:"=m"(count)
	:"m"(count):"eax"
	);
#else

	__asm__ __volatile__(
		"movl %0, %%eax \n\t"
		:"=m"(count)
		:
		:"eax"
	);
	__asm__ __volatile__(
	"\n.LOOP2: \n\t"
	"addl $1, %%eax \n\t"
	"cmpl $999999, %%eax \n\t"
	"jle .LOOP2 \n\t"
	"movl %%eax, %0"
	:"=m"(count)::"eax"
	);
#endif
	
	end = clock();
	return (double)(end - start) /  (double)CLOCKS_PER_SEC * 1000;
}
