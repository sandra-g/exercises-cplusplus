#include <iostream>//cout
#include <string>//string
#include <cctype>//tolower
#include <map>//map
using namespace std;

void decryptMessage(string, string);

int main(int argc, char* args[]) {
	string message = "Bgc-bfufb tegaedppqna ql aggv zge xof tegaedppfe'l lgjb.\nXof adpf vflqanfe logjbvn'x hf pdwqna d cgebv qn coqro xof tbdkfe ql mjlx d lpdbb tdex. Xof tbdkfe QL XOF HGLL; qx'l kgje vjxk xg fnxfexdqn oqp ge ofe.\nZgrjl ql d pdxxfe gz vfrqvqna codx xoqnal kgj def ngx agqna xg vg.\nXof rglx gz dvvqna d zfdxjef qln'x mjlx xof xqpf qx xdwfl xg rgvf qx. Xof rglx dblg qnrbjvfl xof dvvqxqgn gz dn ghlxdrbf xg zjxjef fstdnlqgn. Xof xeqrw ql xg tqrw xof zfdxjefl xodx vgn'x zqaox fdro gxofe. - Mgon Rdepdrw.\n(ccc.adpdljxed.rgp/uqfc/nfcl/234346?utkjpvbjr) \n(ccc.hedqnkijgxf.rgp/ijgxfl/djxogel/m/mgon_rdepdrw.oxpb)";
	string freqLang = "TEOAISRHNUCMDLGWFPYKJBVQX";
    decryptMessage(message,freqLang);
	return 0;
}

void decryptMessage(string message, string freqLang) {

    map<char, int> mapa;

    cout << "Mensaje leido:" << endl;
    for (char c : message) {
        cout << c;
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            c = tolower(c);
            mapa[c]++;
        }
    }
    cout << endl;

    map<int, char> cantidades;
    for (map<char, int>::iterator it = mapa.begin(); it != mapa.end(); it++) {
        cantidades[it->second] = it->first;
    }

    map<char, char> corresponde;
    int ind = 0;
    for (map<int, char>::iterator it = cantidades.begin(); it != cantidades.end(); it++) {
        corresponde[it->second] = freqLang[24 - ind];
        ind++;
    }

    cout << endl;
    cout << "Mensaje descifrado:" << endl;
    for (char c : message) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            if (islower(c)) {
                char letraMin = tolower(corresponde[c]);
                cout << letraMin;
            }
            else {
                char letraMin = tolower(c);
                cout << corresponde[letraMin];
            }
        }
        else
            cout << c;
    }
}