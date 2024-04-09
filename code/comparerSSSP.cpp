#include <stdio.h>
#include <stdlib.h>

void readFromFiles(const char *f1, const char *f2) {
    FILE *file1 = fopen(f1, "rb");
    if (file1 == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
		FILE *file2 = fopen(f2, "rb");
    if (file2 == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
		int weight1,weight2,numnodes1,numnodes2;
		int *path1;
		int *path2;
		int i = 1;
		
		while(i <= 1957027) {
		
			fread(&weight1,sizeof(int),1,file1);
			fread(&numnodes1,sizeof(int),1,file1);
			path1 = (int *)malloc(numnodes1 * sizeof(int));
			fread(path1,sizeof(int),numnodes1,file1);
			
			fread(&weight2,sizeof(int),1,file2);
			fread(&numnodes2,sizeof(int),1,file2);
			path2 = (int *)malloc(numnodes2 * sizeof(int));
			fread(path2,sizeof(int),numnodes2,file2);
			
			if(weight1 != weight2) {
				printf("Weight mismatch %d %d at i %d\n",weight1,weight2,i);
				break;
			}
			if(numnodes1 != numnodes2) {
				printf("Alternate path but same weight numnodes %d numnodes %d at i %d\n",numnodes1,numnodes2,i);
				//break;
			}
			free(path1);
			free(path2);
			i++;
		}

    fclose(file1);
		fclose(file2);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *f1 = argv[1];
		char *f2 = argv[2];

    // Read matrices from files
    readFromFiles(f1, f2);

    return 0;
}
