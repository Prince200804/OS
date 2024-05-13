#include <stdio.h>
#include <limits.h>


int isMissOrHit(int page, int frames[], int num_frames);

void optimal(int pages[], int frames[], int num_pages, int num_frames);

int maxDist_Optimal(int pages[], int frames[], int num_frames, int start, int end);

void main(){
    int num_frames = 4;
    int frames[num_frames];
    int i;
    for(i=0; i<num_frames; i++){
        frames[i] = -1;
    }
    int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int num_pages = sizeof(pages)/sizeof(pages[0]);

    optimal(pages, frames, num_pages, num_frames);
    
}



int isMissOrHit(int page, int frames[], int num_frames){
    int i,f=0;
    for(i=0; i<num_frames; i++){
        if(page == frames[i]){
            f=1;
            break;
        }
    }
    return f;
}

void optimal(int pages[], int frames[], int num_pages, int num_frames){
    int i,j,f,index;
    double miss=0,hit=0;
    for(i=0; i<num_pages; i++){
        f=0;
        for(j=0; j<num_frames; j++){
            if(frames[j] == -1){
                frames[j] = pages[i];
                f=1;
                miss++;
                break;
            }
        }

        if(f==0){
            if(isMissOrHit(pages[i], frames, num_frames) == 0){
                index = maxDist_Optimal(pages, frames, num_frames, i, num_pages);
                frames[index] = pages[i];
                miss++;
            }else{
                hit++;
            }
        }

        printf("Input %d: ", pages[i]);
        for(j=0; j<num_frames; j++){
            printf("%d\t", frames[j]);
        }
        printf("\n");
    }
    printf("Miss: %.0f\t Hit: %.0f\t Hit ratio: %.2f\n", miss, hit, hit/miss);
}

int maxDist_Optimal(int pages[], int frames[], int num_frames, int start, int end){
    int i,j,f, max_index = INT_MIN, frame_index, index;
    for(i=0; i<num_frames; i++){
        f=0;
        for(j=start; j<end; j++){
            if(frames[i] == pages[j]){
                index = j;
                f=1;
                break;
            }
        }

        if(f==0){
            max_index = INT_MAX;
            frame_index = i;
            break;
        }

        if(max_index < index){
            max_index = index;
            frame_index = i;
        }
    }
    return frame_index;
}