
int fifo_i=0;

int putPageFIFO(int page, int *mem, int n) {
	int old_page = mem[fifo_i];
	mem[fifo_i++]=page;
	fifo_i%=n;
	return old_page;
}
