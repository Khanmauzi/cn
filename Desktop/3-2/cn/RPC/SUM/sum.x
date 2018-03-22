struct arr {
	long arr[10];
};

struct arrs{
	long arr1[10];
	long arr2[10];	
};

program SUM_PROG {
		version SUM_VERS {
			struct arr add(struct arrs) =1;
		} = 1;
	} = 0x31423456;
