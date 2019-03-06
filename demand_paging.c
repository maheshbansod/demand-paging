#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dp_algorithms.h"

int processString(char *str, int *arr) {
	char *s;
	int i=0;
	s = strtok(str,",");
	while(s!=NULL) {
		arr[i++]=atoi(s);
		s =strtok(NULL, ",");
	}
	return i;
}

int isPageInMemory(int page, int *mem, int n) {
	int i;
	for(i=0;i<n;i++) {
		if(mem[i]==page) return 1;
	}
	return 0;
}

int addToMemory(int page, int *mem, int n) {
	/*
	* returns the swapped page if swapped,
	*	0 if added to free memory,
	* -1 if page already exists
	* */

	if(isPageInMemory(page, mem, n)) {
		return -1;
	}

	return putPageFIFO(page, mem, n);
}

void showReferenceString(int x, int *ref, int n) {
	int i;
	printf(" Reference string: {");
	for(i=0;i<n;i++) {
		if(i==x) printf("<");
		printf("%d", ref[i]);
		if(i==x) printf(">");
		printf(" ");
	}
	printf("}\n");
}

void showMemory(int *mem, int n) {
	int i;
	printf(" Memory: |");
	for(i=0;i<n;i++) {
		printf("%d|", mem[i]);
	}
	printf("\n");
}

void main() {
	int mem[100]={0}, n, i, r;
	int ref[200], refn;
	int pf = 0; //page fault
	char str[300];

	printf("Enter memory size: ");
	scanf("%d", &n);
	getchar();

	printf("Enter reference string: ");
	fgets(str, 300, stdin);
	refn = processString(str, ref);
	
	printf("Initially:\n");
	showReferenceString(-1, ref, refn);
	showMemory(mem, n);

	printf("\n\n");
	for(i=0;i<refn;i++) {
		showReferenceString(i, ref, refn);
		if((r=addToMemory(ref[i], mem, n))!=-1) {
			pf++;
			if(r!=0)
				printf("Page %d swapped out\n", r);
		}
		printf("No. of page faults: %d\n",pf);
		showMemory(mem, n);
		printf("-------\n");
	}
}
