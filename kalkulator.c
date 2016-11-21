#include <stdio.h>
#include <math.h>
#include "mesinkata.h"
#include "stacklist.h"
#include "check.h"

#define Karakter(i) input.TabKata[(i)]

int i;
Kata input;
Stack S;

double TakeAngka() {
    double angka = 0;
    int j;
    do {
        angka = angka*10 + (double) ((int) Karakter(i) - (int) '0');
        i++;
    } while ((i <= input.Length) && ((int) Karakter(i) >= (int) '0') && ((int) Karakter(i) <= (int) '9'));
    if (Karakter(i) == '.') {
        i++;
        j = 0;
        while ((i <= input.Length) && ((int) Karakter(i) >= (int) '0') && ((int) Karakter(i) <= (int) '9')) {
            j++;
            angka = angka + (double) ((int) Karakter(i) - (int) '0') / pow(10,j);
            i++;
        }
    }
    return angka;
}

double proses() {
    double angka,sum,temp;
    boolean minus,kali,bagi;
    infotype X;
    minus = false;
    kali = false;
    bagi = false;
    while ((i <= input.Length) && (Karakter(i) != ')')) {
        if ((Karakter(i) >= '0') && (Karakter(i) <= '9')) {
            angka = TakeAngka();
            //printf("%f ",angka);
            if (minus) {
                angka *= -1;
                minus = false;
            }
            else if (kali) {
                Pop(&S,&X);
                angka *= X.val;
                kali = false;
            }
            else if (bagi) {
                Pop(&S,&X);
                angka = X.val / angka;
                bagi = false;
            }
            //printf("%f\n",angka);
            X.op = 'b';
            X.val = angka;
            Push(&S,X);
        }
        else if (Karakter(i) == '+') {
            i++;
        }
        else if (Karakter(i) == '-') {
            i++;
            minus = true;
        }
        else if (Karakter(i) == '*') {
            i++;
            kali = true;
        }
        else if (Karakter(i) == '/') {
            i++;
            bagi = true;
        }
        else if (Karakter(i) == '(') {
            X.op = '(';
            X.val = 0;
            Push(&S,X);
            i++;
            angka = proses();
            //printf("%f ",angka);
            if (minus) {
                angka *= -1;
                minus = false;
            }
            else if (kali) {
                Pop(&S,&X);
                angka *= X.val;
                kali = false;
            }
            else if (bagi) {
                Pop(&S,&X);
                angka = X.val / angka;
                bagi = false;
            }
            //printf("%f\n",angka);
            X.op = 'b';
            X.val = angka;
            Push(&S,X);
        }
        if (Karakter(i) == ')') {
            angka = 0;
            Pop(&S,&X);
            //printf("%f %c\n",X.val,X.op);
            while (X.op != '(') {
                angka += X.val;
                Pop(&S,&X);
            //printf("%f %c\n",X.val,X.op);
            }
        }
    }
    i++;
    return angka;
}

int main() {
    float sum;
    infotype X;
    i = 1;
    CreateEmpty(&S);

    input = InputKata();
    if (checkSemua(input)){
        input.Length++;
        input.TabKata[input.Length] = ')';
        X.op = '(';
        X.val = 0;
        Push(&S,X);
        sum = proses();
        printf("%.2f\n",sum);
    }else{
        printf("syntax error\n");
    }

    return 0;
}
