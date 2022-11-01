#include <iostream>
#include <string>
#include <cstring>
#include <list>
using namespace std;

const int ERROR_STATE = 100;
typedef int state; // kieu trang thai
typedef char *attri; // kieu thuoc tinh
typedef unsigned char *token; // kieu tu to
unsigned char *x; // xau vao x
unsigned int i=0; // vtri cua ky tu doc vao xau x

// return ky tu tiep theo
unsigned char readchar(unsigned char *x, unsigned int i) {
    if (i < sizeof(x)) return *(x+i);
    else return '\0';
}

// return thuoc tinh tuong ung voi trang thai ket thuc
// attri attribute(state s){
//     char *ch = "";
//     switch(s) {
//         case 2: strcpy(ch, "so sanh lon hon bang"); break;
//         case 3: strcpy(ch, "dich phai"); break;
//         case 4: strcpy(ch, "so sanh lon hon"); break;
//         case 6: strcpy(ch, "so sanh nho hon bang"); break;
//         case 7: strcpy(ch, "dich trai"); break;
//         case 8: strcpy(ch, "so sanh nho hon"); break;
//         case 10: strcpy(ch, "so sanh khong bang"); break;
//         case 11: strcpy(ch, "phu dinh"); break;
//         case 13: strcpy(ch, "so sanh bang"); break;
//         case 14: strcpy(ch, "gan"); break;
//         case 17: strcpy(ch, "cong bang"); break;
//         case 18: strcpy(ch, "tang 1"); break;
//         case 19: strcpy(ch, "cong"); break;
//         case 21: strcpy(ch, "tru bang"); break;
//         case 22: strcpy(ch, "giam 1"); break;
//         case 23: strcpy(ch, "tru"); break;
//         case 25: strcpy(ch, "nhan bang"); break;
//         case 26: strcpy(ch, "nhan"); break;
//         case 28: strcpy(ch, "chia bang"); break;
//         case 29: strcpy(ch, "chia"); break;
//         case 30: strcpy(ch, "chia lay du"); break;
//         default: strcpy(ch, "token khong duoc doan nhan (tt khong dung)");
//     }
//     return ch;
// }

attri attribute(state s){
    char *ch = "";
    switch(s) {
        case 2: strcpy(ch, ">="); break;
        case 3: strcpy(ch, ">>"); break;
        case 4: strcpy(ch, ">"); break;
        case 6: strcpy(ch, "<="); break;
        case 7: strcpy(ch, "<<"); break;
        case 8: strcpy(ch, "<"); break;
        case 10: strcpy(ch, "!="); break;
        case 11: strcpy(ch, "!"); break;
        case 13: strcpy(ch, "=="); break;
        case 14: strcpy(ch, "="); break;
        case 17: strcpy(ch, "+="); break;
        case 18: strcpy(ch, "++"); break;
        case 19: strcpy(ch, "+"); break;
        case 21: strcpy(ch, "-="); break;
        case 22: strcpy(ch, "--"); break;
        case 23: strcpy(ch, "-"); break;
        case 25: strcpy(ch, "*="); break;
        case 26: strcpy(ch, "*"); break;
        case 28: strcpy(ch, "/="); break;
        case 29: strcpy(ch, "/"); break;
        case 30: strcpy(ch, "%"); break;
        default: strcpy(ch, "token khong duoc doan nhan (tt khong dung)");
    }
    return ch;
}

// ktra s co phai trang thai ket thuc khong sao
int nostar_end_state(state s){
    switch(s) {
        case 2: case 3: case 6: case 7: case 10: case 13: case 17: case 18: 
        case 21: case 22: case 25: case 28: case 30: return 1;
        default: return 0;
    }
}

// ktra s co phai trang thai ket thuc co sao
int star_end_state(state s) {
    switch(s){
        case 4: case 8: case 11: case 14: case 19: case 23: case 26: case 29: return 1;
        default: return 0;
    }
}

state start_state_otherbranch(state s){
    state start;
    switch(s){
        case 0: start = 15; break;
        case 15: start = ERROR_STATE;
    }
    return start;
}

int start_state(state s){
    if ((s == 0) || (s == 15)) return 1;
    return 0;
}

// ghep them ky tu c vao token tk
void catchar_in_token(unsigned char c, token tk){
    *(tk+sizeof(tk)+1)='\0';
    *(tk+sizeof(tk))=c;
}

// return tri tu vung bat dau tu vtri i va thuoc tinh tra ve cho tt
token search_token(unsigned int *i, attri tt) {
    token tk;
    state s=0;
    int stop = 0;
    unsigned char c;
    do {
        c = readchar(x, *i);
        *i = *i + 1;
    } while((c == ' ' && (*i<sizeof(x))));

    while (*i<sizeof(x) && (!stop)) {
        switch(s) {
            case 0: 
                if (c == '>') s = 1;
                else if (c == '<') s = 5;
                else if (c == '!') s = 9;
                else if (c == '=') s = 12;
                else s = start_state_otherbranch(s);
                break;
            case 1:
                if (c == '=') s = 2;
                else if (c == '>') s = 3;
                else s = 4;
                break; 
            case 5:
                if (c == '=') s = 6;
                else if (c == '<') s = 7;
                else s = 8;
                break; 
            case 9:
                if (c == '=') s = 10;
                else s = 11;
                break;
            case 12:
                if (c == '=') s = 13;
                else s = 14;
                break;
            case 15:
                if (c == '+') s = 16;
                else if (c == '-') s = 20;
                else if (c == '*') s = 24;
                else if (c == '/') s = 27;
                else if (c == '%') s = 30;
                else s = start_state_otherbranch(s);
                break;
            case 16:
                if (c == '=') s = 17;
                else if (c == '+') s = 18;
                else s = 19;
                break;
            case 20:
                if (c == '=') s = 21;
                else if (c == '+') s = 22;
                else s = 23;
                break;
            case 24:
                if (c == '=') s = 25;
                else s = 26;
                break;
            case 27:
                if (c == '=') s = 28;
                else s = 29;
                break;
            default: stop = 1;
        }
        if (s == ERROR_STATE) {
            stop = 1;
            cout << "loi tai vi tri thu " << *i;
            *tk = '\0';
        }
        else if (start_state(s)) ;
        else if (nostar_end_state(s)) {
            catchar_in_token(c, tk);
            *i = *i + 1; 
            stop = 1;
            strcpy(tt, attribute(s));
        }
        else if (star_end_state(s)) {
            strcpy(tt, attribute(s));
            stop = 1;
        }
        else {
            catchar_in_token(c, tk);
            *i = *i + 1;
            c = readchar(x, *i);
        }
    }
    return tk;
}

// luu tru tk, a vao danh sach l
list<pair<token, attri>> l;
void save_token_and_attribute(token tk, attri a) {
    attri b;
    strcpy((char *)b, (char *)a);
    l.push_back(pair<token, attri>(tk, b));
}

void lexical_analysis() {
    token tk; attri a;
    do {
        tk=search_token(&i,a);
        save_token_and_attribute(tk,a);
    } while ((*tk!='\0')&&(i<sizeof(x)));
}

int main() {
    cout << "nhap xau vao x: ";
    string input;
    getline(cin, input);
    x = new unsigned char[100]();
    for (int j = 0; j < input.size(); j++)
    {
        *(x + j) = input[j];
    }
    cout << "length(x) = " << strlen((char *)x) << endl;
    for (int j = 0; j < strlen((char *)x); j++)
    {
        cout << "j = " << j << " : " << *(x + j) << endl;
    }
    cout << endl;
    lexical_analysis();
    // in danh sach tu to va thuoc tinh
    cout << "Danh sach tu to: " << endl;
    for (pair<token, attri> p : l)
    {
        for (int j = 0; j < strlen((char *)p.first); j++)
        {
            cout << *(p.first + j);
        }
        cout << " | ";
        for (int j = 0; j < strlen((char *)p.second); j++)
        {
            cout << *(p.second + j);
        }
        cout << endl;
    }
}