#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void itoa(char *buf, int base, long long value){
    static const char digits[] = "0123456789abcdef";
    if (base < 2 || base > 16){
        *buf = '\0';
        return;
    }

    // Handle value 0
    if(value == 0){
        *buf++ = '0';
        *buf = '\0';
        return;
    }

    // Handle negative values
    int sign = 1;
    if(value < 0){
        sign = -1;
        value = -value;
    }

    // Convert value to string
    char temp[32] = {0};
    int i = 0;
    
    while (value > 0){
        temp[i++] = digits[value % base];
        value /= base;
    }
    if(sign < 0){
        *buf++ = '-';
    }
    // Reverse the string
    for(int j = 0; j < i; j++){
        *buf++ = temp[i - j - 1];
    }
    *buf = '\0';
  }


int my_printf(const char * restrict format, ...){
    va_list args;
    va_start(args, format);
    int result = 0;
    for(int i = 0; format[i]; i++){
        if (format[i] == '%'){
          // Temporary buffer for formatted value
            char temp[32] = {0};   
            switch (format[i + 1]){
                case 'd':
                    itoa(temp, 10, va_arg(args, int));
                    result += write(1, temp, strlen(temp)); 
                    break;
                case 'o':
                    itoa(temp, 8, va_arg(args, int));
                    result += write(1, temp, strlen(temp));
                    break;
                case 'u':
                    itoa(temp, 10, va_arg(args, int));
                    result += write(1, temp, strlen(temp));
                    break;
                case 'x':
                    itoa(temp, 16, va_arg(args, int));
                    result += write(1, temp, strlen(temp));
                    break;
                case 'c':
                    result += write(1, &(char){(char)va_arg(args, int)}, 1);
                    break;
                case 's':{
                    char *str = va_arg(args, char*);
                    if(str != NULL){
                        strcpy(temp, str);
                        result += write(1, temp, strlen(temp));
                    }else{
                        strcpy(temp, "(null)");
                        result += write(1, temp, strlen(temp));
                        
                    }
                    break;
                }
                case 'p':
                    result += write(1, "0x", 2);
                    itoa(temp, 16, (unsigned long long)(long long)va_arg(args, void *));
                    result += write(1, temp, strlen(temp));
                    break;
              
              }
            
            i++;
        }else {      
            // Print character as it is
            result += write(1, &format[i], 1);
        }
    }
    va_end(args);
    return result;
}
        
    
int main(){
    //int variable;
    
    return 0;
}
