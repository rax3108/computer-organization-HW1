#include <stdio.h>
int main ()
{
	int a[10] = {0}, b[10]= {0}, c[10] = {0};
	int i, arr_size = 10;
	FILE *input = fopen("../input/2.txt","r");
	for(i = 0; i<arr_size; i++) fscanf(input, "%d", &a[i]);
	for(i = 0; i<arr_size; i++) fscanf(input, "%d", &b[i]);
	for(i = 0; i<arr_size; i++) fscanf(input, "%d", &c[i]);
	
	fclose(input);
	int *p_a = &a[0];
	int *p_b = &b[0];
	int *p_c = &c[0];

/* Original C code segment
 for (int i = 0; i < arr_size; i++){
 *p_c++ = *p_a++ * *p_b++;
 }
 */
	for (int i = 0; i < arr_size; i++)
		asm volatile(
				"lw x5,(%[A])\n\t"
				"lw x6,(%[B])\n\t"
				"lw x7,(%[C])\n\t"
				"mul x7, x5, x6\n\t"
				"sw x7,(%[C])\n\t"
				"addi %[A], %[A], 4\n\t"
				"addi %[B], %[B], 4\n\t"
				"addi %[C], %[C], 4\n\t"
				:[C] "+r"(p_c),[A] "+r"(p_a),[B] "+r"(p_b)
				);
	
	
	p_c = &c[0];
	for (int i = 0; i < arr_size; i++)
		printf("%d ", *p_c++);


	return 0;
}
