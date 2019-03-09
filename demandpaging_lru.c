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

int used[100]={0};
int cnt=0;

int usePage(int page, int *mem, int n) {
	
	int i, mini, min = 1000;

	used[page] = cnt;
	cnt++;

	if(pageExists(page, mem, n)) {
		return 0;
	}

	//lru
	for(i=0;i<n;i++) {
		if(mem[i]==0) {
			mem[i]=page;
			return 1;
		}
	}

	for(i=0;i<n;i++) {
		if(used[mem[i]] < min) {
			min = used[mem[i]];
			mini = i;
		}
	}
	mem[mini] = page;

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
