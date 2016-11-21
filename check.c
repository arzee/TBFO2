#include <stdio.h>
#include <stdlib.h>
#include "mesinkata.h"
#include "check.h"

boolean checkKurung(Kata kata){
    char cc;
    int ci=0,n=1;
    boolean valid=true;

    while (n<=kata.Length && valid){
        if ( kata.TabKata[n] == '(' || kata.TabKata[n] == ')'){
            if (kata.TabKata[n] == '('){
                ci++;
            }else{
                ci--;
            }
            if (ci<0){
                valid=false;
            }
        }
        n++;
    }
    if (ci==0){
        return valid;
    }else{
        return false;
    }

}

boolean isOperator(char cc){
    return (cc=='+' || cc=='-' || cc=='*' || cc=='/');
}

boolean checkOperator(Kata kata){
    char cc;
    int ci=0,n=1;
    boolean valid=true;

    while (n<=kata.Length && valid){
        if (isOperator(kata.TabKata[n])){
            if (kata.TabKata[n]=='-'){
                if (n == 1) {
                    if (!(kata.TabKata[n+1]=='(' || (kata.TabKata[n+1]>='0' && kata.TabKata[n+1] <= '9'))) {
                        valid = false;
                    }
                }
                else {
                    if (!(kata.TabKata[n-1]=='(' || kata.TabKata[n-1]==')' || (kata.TabKata[n-1]>='0' && kata.TabKata[n-1] <= '9'))) {
                        valid = false;
                    }
                    if (!(kata.TabKata[n+1]=='(' || (kata.TabKata[n+1]>='0' && kata.TabKata[n+1] <= '9'))) {
                        valid = false;
                    }
                }
            }
            else {
                if (n == 1) {
                    valid = false;
                }
                else {
                    if (!(kata.TabKata[n-1]==')' || (kata.TabKata[n-1]>='0' && kata.TabKata[n-1] <= '9'))) {
                        valid = false;
                    }
                    if (!(kata.TabKata[n+1]=='(' || (kata.TabKata[n+1]>='0' && kata.TabKata[n+1] <= '9'))) {
                        valid = false;
                    }
                }
            }  
        }
        else if (kata.TabKata[n] == '(') {
            if (n == 1) {
                if (!(kata.TabKata[n+1]=='(' || kata.TabKata[n+1]=='-' || (kata.TabKata[n+1]>='0' && kata.TabKata[n+1] <= '9'))) {
                    valid = false;
                }
            }
            else {
                if (!(kata.TabKata[n-1]=='(' || isOperator(kata.TabKata[n-1]))) {
                    valid = false;
                }
                if (!(kata.TabKata[n+1]=='(' || kata.TabKata[n+1]=='-' || (kata.TabKata[n+1]>='0' && kata.TabKata[n+1] <= '9'))) {
                    valid = false;
                }
            }
        }
        else if (kata.TabKata[n] == ')') {
            if (n == 1) {
                valid = false;
            }
            else if (n == kata.Length) {
                if (!(kata.TabKata[n-1]==')' || (kata.TabKata[n-1]>='0' && kata.TabKata[n-1] <= '9'))) {
                    valid = false;
                }
            }
            else {
                if (!(kata.TabKata[n-1]==')' || (kata.TabKata[n-1]>='0' && kata.TabKata[n-1] <= '9'))) {
                    valid = false;
                }
                if (!(kata.TabKata[n+1]==')' || isOperator(kata.TabKata[n+1]))) {
                    valid = false;
                }
            }
        }
        n++;
    }
    return valid;
}

boolean checkAngka(Kata kata){
    char cc;
    int ci=0,n=1;
    boolean valid=true;

    while (n<=kata.Length && valid){
        if ((kata.TabKata[n]>= '0') && (kata.TabKata[n]<= '9')){
            while ((kata.TabKata[n]>= '0') && (kata.TabKata[n]<= '9')) {
                n++;
            }
            if (kata.TabKata[n] == '.') {
                n++;
                if ((kata.TabKata[n]>= '0') && (kata.TabKata[n]<= '9')) {
                    while ((kata.TabKata[n]>= '0') && (kata.TabKata[n]<= '9')) {
                        n++;
                    }
                    if (kata.TabKata[n] == '.') {
                        valid = false;
                    }
                }
                else {
                    valid = false;
                }
            }
        }
        else if (kata.TabKata[n] == '.') {
            valid = false;
        }
        n++;
    }
    return valid;
}

boolean checkSemua(Kata kata) {
    return (checkKurung(kata) && checkOperator(kata) && checkAngka(kata));
}