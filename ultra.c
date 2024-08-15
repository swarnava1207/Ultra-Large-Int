#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ultra.h"
ultra str_to_ultra(char * str){
    long int length = (long int) strlen(str);
    ultra value = (ultra) malloc(sizeof(char)*(length+1));
    for (long int i = length-1 ; i >= 0 ; i--){
        value[length - 1 - i] = str[i];
    }
    value[length] = '\0';
    if (str[0] != '-'){
        value = (ultra) realloc(value,sizeof(char)*(length+2));
        value[length] = '+';
        value[length + 1] ='\0';
    }
    return value;
}
int compare(ultra a,ultra b){
    for (int i = length(a)-2; i>=0; i--){
        if (a[i] > b[i]){
            return 1;
        }
        else if (b[i] > a[i]){
            return -1;
        }
    }
    return 0;
}
long int length(ultra a){
    return (long int) strlen(a);
}
char * ultra_to_str(ultra a){
    long int len = length(a);
    ultra value = (ultra) malloc(sizeof(char)*(len+1));
    if (a[len -1] == '+'){
        for (long int i = len-1 ; i >= 1 ; i--){
            value[len - 1 - i] = a[i-1];
    }

    }
    else {
        for (long int i = len-1 ; i >= 0 ; i--){
        value[len - 1 - i] = a[i];
        }
    }
    value[len] = '\0';
    return value;
}
ultra extend(ultra a, ultra b){
    b = (ultra) realloc(b,sizeof(char)*(length(a)+1));
    char sign_b = b[length(b)-1];
    for(long int i = length(b) -1; i < length(a)- 1; i++){
        b[i] = '0';
    }
    b[length(a) - 1] = sign_b;
    b[length(a)] = '\0';
    return b;

}
int is_zero(ultra a){
    for (long int i = 0; i < length(a) - 1;i++){
        if (a[i] != '0'){
            return 0;
        }
    }
    return 1;
}
ultra initialise(long int length){
    ultra result = (ultra) malloc((length+1)*sizeof(char));
    for (long int i = 0; i < length -1; i++){
        result[i] = '0';
    }
    result[length-1] = '+';
    result[length] = '\0';
    return result;
}
ultra subtract(ultra m,ultra n){
    int carry = 0;
    if (length(m) > length(n)){
        n = extend(m,n);
    }
    if (length(n) > length(m)){
        m = extend(n,m);
    }
    ultra result = initialise(length(m));
    ultra a,b;
    char value_a, value_b;
    int comparison = compare(m,n);
    long int len = length(m);
    if (m[len -1] == '-' && n[len -1] == '-'){
        if (comparison == 1){
            result[len - 1] = '-';
            a = m;
            b = n;
        }
        else if (comparison == -1){
            result[len - 1] = '+';
            a = n;
            b = m;
        }
        else {
            return result;
        }
        for (long int i = 0; i < length(a) - 1;i++){
            value_a = (a[i] - ('0'));
            value_b = (b[i] - ('0'));
            if (a[i] < b[i]){
                if (carry){
                    result[i] = (10 + value_a - value_b - 1 + '0');
                    }
                else {
                    result[i] = (10 + value_a - value_b  + '0');
                }
                carry = 1;
            }
            else if (b[i] < a[i]) {
                if (carry){
                    result[i] = (value_a - value_b - 1 + '0');
                }
                else {
                    result[i] = (value_a - value_b + '0');
                }

            }
            else {
                if (carry){
                    result[i] = '9';
                }
                else {
                    result[i] = '0';
                }
            }
        }
        result[len] = '\0';
    }
    else if (m[len -1] == '+' && n[len -1] == '+'){
        if (comparison == 1){
            result[len - 1] = '+';
            a = m;
            b = n;
        }
        else if (comparison == -1){
            result[len - 1] = '-';
            a = n;
            b = m;
        }
        else {
            return result;
        }
        for (long int i = 0; i < len - 1;i++){
            value_a = (a[i] - ('0'));
            value_b = (b[i] - ('0'));
            if (a[i] < b[i]){
                if (carry){
                    result[i] = (10 + value_a - value_b - 1 + '0');
                    }
                else {
                    result[i] = (10 + value_a - value_b  + '0');
                }
                carry = 1;
            }
            else if (b[i] < a[i]) {
                if (carry){
                    result[i] = (value_a - value_b - 1 + '0');
                }
                else {
                    result[i] = (value_a - value_b + '0');
                }

            }
            else {
                if (carry){
                    result[i] = '9';
                }
                else {
                    result[i] = '0';
                }
            }
        }
        result[len] = '\0';
    }
    else if (m[len -1] == '+' && n[len -1] == '-'){
        a = m;
        b = n;
        result[len -1] = '+';
        for (long int i = 0; i < len - 2;i++){
            value_a = (a[i] - ('0'));
            value_b = (b[i] - ('0'));
            if ((value_a + value_b) >= 10){
                if (carry){
                    result[i] = (-10 + value_a + value_b + 1 + '0');
                    }
                else {
                    result[i] = (-10 + value_a + value_b  + '0');
                }
                carry = 1;
            }
            else {
                if (carry){
                    result[i] = (value_a + value_b + 1 + '0');
                }
                else {
                    result[i] = (value_a + value_b + '0');
                }

            }
            //printf("result = %s at i = %li\n",result,i);
        }
        value_a = a[len-2] - '0';
        value_b = b[len-2] - '0';
        if (value_a + value_b + 1 >= 10){
            result = (ultra) realloc(result, len + 2 * sizeof(char));
            if (carry){
                result[len - 2] = (value_a + value_b + 1 - 10 + '0');
            }
            else {
                result[len - 2] = (value_a + value_b  - 10 + '0');
            }
            result[len - 1] = '1';
            result[len] ='+';
            result[len + 1] = '\0';
        }
        else {
            if (carry){
                result[len - 2] = (value_a + value_b + 1 + '0');
            }
            else {
                result[len - 2] = (value_a + value_b + '0');
            }
            result[len - 1] = '+';
            result[len] ='\0';
            }
            //printf("result at i=2 is %s\n",result);

        }
     else if (m[len -1] == '-' && n[len -1] == '+'){
        a = m;
        b = n;
        result[len -1] = '-';
        for (long int i = 0; i < len - 2;i++){
            value_a = (a[i] - ('0'));
            value_b = (b[i] - ('0'));
            if ((value_a + value_b) >= 10){
                if (carry){
                    result[i] = (-10 + value_a + value_b + 1 + '0');
                    }
                else {
                    result[i] = (-10 + value_a + value_b  + '0');
                }
                carry = 1;
            }
            else {
                if (carry){
                    result[i] = (value_a + value_b + 1 + '0');
                }
                else {
                    result[i] = (value_a + value_b + '0');
                }

            }
        }
        value_a = a[len-2] - '0';
        value_b = b[len-2] - '0';
        if (value_a + value_b + 1 >= 10){
            result = (ultra) realloc(result, len + 2);
            if (carry){
                result[len - 2] = (value_a + value_b + 1 - 10 + '0');
            }
            else {
                result[len - 2] = (value_a + value_b  - 10 + '0');
            }
            result[len - 1] = '1';
            result[len] ='-';
            result[len + 1] = '\0';
        }
        else {
            if (carry){
                result[len - 2] = (value_a + value_b + 1 + '0');
            }
            else {
                result[len - 2] = (value_a + value_b + '0');
            }
            result[len - 1] = '-';
            result[len] ='\0';
        }

    }
    return result;
}


void increment(ultra a,long int index){
    if (a[index] == '+'){
        return;
    }
    if (a[index] != '9'){
        a[index] += '1' - '0';
        return;
    }
    else {
        a[index] = '0';
        return increment(a,index+1);
    }

}
// int main(int argc, char ** argv){
//     printf("%s\n",str_to_ultra(argv[1]));
//     printf("%li\n",length(argv[1]));
//     printf("%d\n",is_zero(argv[1]));
//     printf("%s\n",initialise(3));
//     ultra a = str_to_ultra(argv[1]);
//     ultra b = str_to_ultra(argv[2]);
//     printf("%s\n",subtract(a,b));
//     increment(a,0);
//     printf("%s\n",a);
//     printf("%s",ultra_to_str(a));
// }
