#include <iostream>
#include <time.h>
#include <fstream>

int ARR_SIZE = 0;
int HALF;
std::string FILENAME = "10m.txt";

float median (int* p, int l, int r){
    int L, R, i, j;
    int x;

    L = l;
    R = r;
    int k = ((int)(R - L)) / 3; //random
    x = *(p + L + k);
    i = L;
    j = R - 1;

    while(i <= j){
        for(;x > *(p + i)  && i < R; i++){}

        for(;x < *(p + j) && j >= L; j--){}

        if(i <= j){
          int w = *(p + i);
          *(p + i) = *(p + j);
          *(p + j) = w;
          i++;
          j--;
        }
      }
    //turn right part
    if (i <= HALF) {return median (p, i, R);}
    //turn left part
    if (j >= HALF){return median (p, L, j + 1);}

    //middle part sorted
    if (j < i){
      if((ARR_SIZE % 2) != 1){
          return ((float)(*(p + HALF) + *(p + HALF - 1))) / 2;
      };

      return *(p + HALF);
    }

    return 0;
}

int main(){
    std::ios::sync_with_stdio(false);
    clock_t start = clock();

    int max = 0;
    int min = 0;
    float med = 0;
    long sum = 0;
    int i = 0;
    std::string line;

    std::ifstream myfile;
    myfile.open (FILENAME);

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
             ARR_SIZE++;
        }
    }

    myfile.close();
    myfile.open (FILENAME);

    int* arr = new int[ARR_SIZE];
    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
             int x = std::stoi(line);
             *(arr + i++) = x;
             sum = sum + x;
             max = std::max(x, max);
             min = std::min(x, min);
        }
    }
    myfile.close();
    HALF = (int) (ARR_SIZE / 2);
    med = median(arr, 0, ARR_SIZE);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The max: %i \n", max);
    printf("The min: %i \n", min);
    printf("The med: %f \n", med);
    printf("The avg: %f \n", ((float) sum) / ARR_SIZE);
    printf("The time: %f seconds\n", seconds);

    return 0;
}
