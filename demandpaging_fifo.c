#include <stdio.h>

void displayMemory(int *mem, int n) {
	int i;
	printf("Frames: |");
	for(i=0;i<n;i++) {
		printf("%d|", mem[i]);
	}
	printf("\n");
}

int pageExists(int page, int *mem, int n) {
	int i;
	for(i=0;i<n;i++) if(mem[i]==page) return 1;
	return 0;
}

int usePage(int page, int *mem, int n) {
	static int fifo_i = 0;
	if(pageExists(page, mem, n)) {
		return 0;
	}

	//fifo
	mem[fifo_i++]=page;
	if(fifo_i == n) fifo_i = 0;

	return 1;
}

int main() {
	int i;
	int ref[100], mem[100]={0}, refn, fn, pf=0;

	printf("How many frames? ");
	scanf("%d", &fn);
	printf("Size of reference string: ");
	scanf("%d", &refn);
	printf("Enter the reference string: ");
	for(i=0;i<refn;i++) {
		scanf("%d", &ref[i]);
	}
	
	for(i=0;i<refn;i++) {
		displayMemory(mem, fn);
		pf += usePage(ref[i], mem, fn);
	}
	displayMemory(mem, fn);
	printf("The number of page faults : %d\n", pf);
}
