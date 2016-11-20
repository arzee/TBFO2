#include <stdio.h>
#include <math.h>
#include "mesinkata.h"
#include "stacklist.h"

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

boolean checkKatax(Kata kata){
    char cc;
    int ci,countl=0,countr=0,i=0;;
    Stack S;
    infotype X;
    CreateEmpty(&S);
    boolean cek;

    cek=true;
    while (i<=kata.Length){
        if ( kata.TabKata[i] == '(' || kata.TabKata[i] == ')'){
            if (kata.TabKata[i] == '('){
                cek=false;
                printf("cek = false\n");
            }else{
                cek=true;
                printf("cek = true\n");
            }
            X.val=0;
            X.op =kata.TabKata[i];
            Push(&S,X);
        }
        i++;
    }
    while (!(IsEmpty(S))) {
        Pop(&S,&X);
        if (X.op == ')'){
            countr++;
            printf(")\n");
        }else if (X.op == '('){
            countl++;
            printf("(\n");
        }else{

        }
    }
    if (countl == countr){
        if (cek == false){
            printf("salah\n");
            return false;
        }else{
            printf("bener\n");
            return true;
        }
    }else{
        printf("di sini");
        return false;
    }
}

int main() {
    float sum;
    infotype X;
    int i=1;
    CreateEmpty(&S);
    boolean check;

    input = InputKata();
    check = checkKatax(input);

    printf("sampai sini");      //ga sampai sini
    if (check==true){
        printf("masih bisa");
        input.Length++;
        input.TabKata[input.Length] = ')';
        X.op = '(';
        X.val = 0;
        Push(&S,X);
        sum = proses();
        if (sum<=0 || sum>0){
            printf("%f\n",sum);
        }else{
            printf("syntax error\n");
        }
        return 0;
    }else{
      printf("syntax error\n");
    }
}

