#include<stdio.h>
int main()
{
int i=0;
int h[9]={0}, x[3]={0}, y[3]={0};
FILE *input = fopen("../input/4.txt","r");
for(i = 0; i<9; i++) fscanf(input, "%d", &h[i]);
for(i = 0; i<3; i++) fscanf(input, "%d", &x[i]);
for(i = 0; i<3; i++) fscanf(input, "%d", &y[i]);
fclose(input);
int *p_x = &x[0] ;
int *p_h = &h[0] ;
int *p_y = &y[0] ;
asm volatile(
		"addi t1, x0, 3\n\t"
		"Loop1:\n\t"
			"addi t0, x0, 3\n\t"
			"Loop2:\n\t"
				"beq t0, x0, Exit2\n\t"
				"lw t2, (%[X])\n\t"
				"lw t3, (%[Y])\n\t"
				"lw t4, (%[H])\n\t"
				"mul t5, t4, t2\n\t"
				"add t3, t3, t5\n\t"
				"addi %[X], %[X], 4\n\t"
				"addi %[H], %[H], 4\n\t"
				"sw t3, (%[Y])\n\t"
				"addi t0, t0, -1\n\t"
				"beq x0,x0,Loop2\n\t"
			"Exit2:\n\t"
			"addi %[X], %[X], -12\n\t"
			"addi %[Y], %[Y], 4\n\t"
			"addi t1, t1, -1\n\t"
			"bne t1, x0,Loop1\n\t"
		"Exit1:\n\t"
		:[Y] "+r"(p_y), [H] "+r"(p_h), [X] "+r"(p_x)
		);
p_y = &y[0];
for(i = 0; i<3; i++)
	printf("%d \n", *p_y++);
return(0) ;

}

