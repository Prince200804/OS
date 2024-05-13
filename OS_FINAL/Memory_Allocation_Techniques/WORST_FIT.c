#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

double totalBlockSize = 0;

void worstFit(int blocks[], int processes[], int num_blocks, int num_processes);

void main(){
    int blocks[] = {100, 500, 200, 300, 600};
    int processes[] = {200, 400, 110, 420, 80};
    int num_blocks = sizeof(blocks)/sizeof(blocks[0]);
    int num_processes = sizeof(processes)/sizeof(processes[0]);
    int input, i, j;
    int a[num_blocks], b[num_processes];

    for(i=0; i<num_blocks; i++){
        totalBlockSize += blocks[i];
    }

    // printf("Enter 1 for First Fit \nEnter 2 for Next Fit \nEnter 3 for Best Fit \nEnter 4 for Worst Fit \nEnter 0 to quit\n");
    
    
        // printf("\nEnter: ");
        // scanf("%d", &input);
        for(i=0; i<num_blocks; i++){
            a[i] = blocks[i];
        }
        for(i=0; i<num_blocks; i++){
            b[i] = processes[i];
        }

        
        worstFit(a, b, num_blocks, num_processes);
        // if(input == 0){
        //     break;
        // }else if(input == 1){
        //     printf("First Fit: \n");
        //     printf("Process No.\t Process Size\t Block No.\n");
        //     firstFit(a, b, num_blocks, num_processes);
        // }else if(input == 2){
        //     printf("Next Fit: \n");
        //     printf("Process No.\t Process Size\t Block No.\n");
        //     nextFit(a, b, num_blocks, num_processes);
        // }else if(input == 3){
        //     printf("Best Fit: \n");
        //     printf("Process No.\t Process Size\t Block No.\n");
        //     bestFit(a, b, num_blocks, num_processes);
        // }else if(input == 4){
        //     printf("Worst Fit: \n");
        //     printf("Process No.\t Process Size\t Block No.\n");
        //     worstFit(a, b, num_blocks, num_processes);
        // }
    
}

void worstFit(int blocks[], int processes[], int num_blocks, int num_processes){
    int i,j,a,max, max_index;
    double totalProcessesSize = 0;
    for(i=0; i<num_processes; i++){
        max = INT_MIN;
        max_index = -1;
        for(j=0; j<num_blocks; j++){
            if(blocks[j] >= processes[i]){
                a = blocks[j] - processes[i];
                if(max < a){
                    max = a;
                    max_index = j;
                }
            }
        }

        if(max_index == -1){
            printf("%d\t\t %d\t\t Not Allocated\n", i+1, processes[i]);
        }else{
            printf("%d\t\t %d\t\t %d\n", i+1, processes[i], max_index+1);
            blocks[max_index] -= processes[i];\
            totalProcessesSize += processes[i];
        }
        
    }
    printf("\nRemaining Space: ");
    for(i=0; i<num_blocks; i++){
        printf("%d ", blocks[i]);
    }
    printf("\n");
    printf("Memory Utilisation: %.2f\n", ((totalProcessesSize/totalBlockSize) * 100));
}