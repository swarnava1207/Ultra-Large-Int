#include "ultra.h"
#include <stdlib.h>
#include <stdio.h>
/*def count_pairs(data: list[int], target: int) -> int:
    """Count the number of pairs of
    list indices i < j such that
    data[i] - data[j] = target.
    Time complexity: Naive O(n^2).
    """
    result = 0
    n = len(data)
    for i in range(n - 1):
        for j in range(i + 1, n):
            if data[i] - data[j] == target:
                result += 1
    return result
*/
long int digits(long int a){
    long int result =0;
    long int n = a;
    while (n != 0){
        n=n/10;
        result++;
        //printf("%li",result);
    }
    return result;
}

int count_pairs_c(int length_data, ultra data[length_data],ultra target){
    // ultra value = initialise(digits((long int) length_data) + 1);
    int value = 0;
    printf("%d\n",length_data);
    // printf("%li\n",digits((long int) length_data));
    // printf("%s66\n",value);
    for (int i = 0; i < length_data-1;i++){
        for (int j = i+1; j<length_data; j++){
            //printf("%s %s\n",data[i],data[j]);
            ultra sub_data = subtract(data[i],data[j]);
            ultra equate = subtract(sub_data,target);
            //printf("%s %s\n",sub_data,equate);
            //printf("%d %d\n",i,j);
            if (is_zero(equate)){
                value++;
            }
        }
    }
    return value;
}
int main(int argc, char ** argv){
   // char ** argv_c = (char **) argv;
    printf("%d\n",argc-1);
    ultra * Numbers = (ultra *) malloc(sizeof(ultra)*(argc-1));
    for (int i = 0; i < argc-1; i++){
        Numbers[i] = str_to_ultra(argv[i]);
       // printf("%s\n",Numbers[i]);
    }
    ultra target = str_to_ultra(argv[argc-1]);
   // printf("%d\n",count_pairs_c(argc - 1,Numbers, target));

   printf("%s\n",target);
    //printf("%d\n",argc-1);
   // printf("%d\n",count_pairs_c(argc - 1,Numbers, target));
   // return count_pairs_c(argc - 1,Numbers, target);
   //return 0;
}

