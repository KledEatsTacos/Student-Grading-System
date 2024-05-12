#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

struct Ogrenci {
    string ad;
    string soyad;
    double vize;
    double kisaSinav1;
    double kisaSinav2;
    double odev1;
    double odev2;
    double finalNotu;
};

int rastgeleIndis(int arraySize) {
    return rand() % arraySize;
}

const string adlar[] = { "Emre", "Aylin", "Can", "Ela", "Ozan", "Leyla", "Burak", "Melis", "Arda", "Zara", "Deniz", "Ceren", "Alp", "Irem", "Kaan" };
const string soyAdlar[] = { "Yıldırım", "Kara", "Aydın", "Demir", "Öztürk", "Tekin", "Güzel", "Kaya", "Sönmez", "Yılmaz", "Erdoğan", "Koç", "Kılıç", "Yavuz", "Acar" };

double finalNotuHesapla(Ogrenci& ogrenci, double vizeAgirligi, double kisaSinav1Agirligi, double kisaSinav2Agirligi, double odev1Agirligi, double odev2Agirligi) {
    return (ogrenci.vize * vizeAgirligi / 100) +
        (ogrenci.kisaSinav1 * kisaSinav1Agirligi / 100) +
        (ogrenci.kisaSinav2 * kisaSinav2Agirligi / 100) +
        (ogrenci.odev1 * odev1Agirligi / 100) +
        (ogrenci.odev2 * odev2Agirligi / 100) +
        ((100 - (vizeAgirligi + kisaSinav1Agirligi + kisaSinav2Agirligi + odev1Agirligi + odev2Agirligi)) * ogrenci.finalNotu / 100);
}

string harfNotuHesapla(double notu) {
    if (notu >= 90.0) return "AA";
    else if (notu >= 85.0) return "BA";
    else if (notu >= 80.0) return "BB";
    else if (notu >= 75.0) return "CB";
    else if (notu >= 65.0) return "CC";
    else if (notu >= 58.0) return "DC";
    else if (notu >= 50.0) return "DD";
    else if (notu >= 40.0) return "FD";
    else return "FF";
}

int main() {
    setlocale(LC_ALL, "Turkish");
    srand(time(0));

    int ogrenciSayisi;
    cout << "Öğrenci sayısını girin: ";
    cin >> ogrenciSayisi;

    double vizeAgirligi, kisaSinav1Agirligi, kisaSinav2Agirligi, odev1Agirligi, odev2Agirligi;

    cout << "Vize sınavının ağırlığını girin: ";
    cin >> vizeAgirligi;
    cout << "kisaSinav 1'in ağırlığını girin: ";
    cin >> kisaSinav1Agirligi;
    cout << "kisaSinav 2'nin ağırlığını girin: ";
    cin >> kisaSinav2Agirligi;
    cout << "Ödev 1'in ağırlığını girin: ";
    cin >> odev1Agirligi;
    cout << "Ödev 2'nin ağırlığını girin: ";
    cin >> odev2Agirligi;

    if (vizeAgirligi + kisaSinav1Agirligi + kisaSinav2Agirligi + odev1Agirligi + odev2Agirligi != 100) {
        cerr << "Hata: Toplam ağırlık 100 olmalıdır.\n";
        return 1;
    }

    vector<Ogrenci> ogrenciler;

    for (int i = 0; i < ogrenciSayisi; ++i) {
        Ogrenci ogrenci;

        ogrenci.ad = adlar[rastgeleIndis(sizeof(adlar) / sizeof(adlar[0]))];
        ogrenci.soyad = soyAdlar[rastgeleIndis(sizeof(soyAdlar) / sizeof(soyAdlar[0]))];

        int dagilim = rand() % 100;

        if (dagilim < 20) {
            ogrenci.vize = min(static_cast<double>(rand() % 21) + 80.0, 100.0);
            ogrenci.kisaSinav1 = min(static_cast<double>(rand() % 31) + 80.0, 100.0);
            ogrenci.kisaSinav2 = min(static_cast<double>(rand() % 31) + 80.0, 100.0);
            ogrenci.odev1 = min(static_cast<double>(rand() % 21) + 80.0, 100.0);
            ogrenci.odev2 = min(static_cast<double>(rand() % 21) + 80.0, 100.0);
        }
        else if (dagilim < 70) {
            ogrenci.vize = min(static_cast<double>(rand() % 31) + 50.0, 100.0);
            ogrenci.kisaSinav1 = min(static_cast<double>(rand() % 31) + 50.0, 100.0);
            ogrenci.kisaSinav2 = min(static_cast<double>(rand() % 31) + 50.0, 100.0);
            ogrenci.odev1 = min(static_cast<double>(rand() % 31) + 50.0, 100.0);
            ogrenci.odev2 = min(static_cast<double>(rand() % 31) + 50.0, 100.0);
        }
        else {
            ogrenci.vize = min(static_cast<double>(rand() % 51), 100.0);
            ogrenci.kisaSinav1 = min(static_cast<double>(rand() % 51), 100.0);
            ogrenci.kisaSinav2 = min(static_cast<double>(rand() % 51), 100.0);
            ogrenci.odev1 = min(static_cast<double>(rand() % 51), 100.0);
            ogrenci.odev2 = min(static_cast<double>(rand() % 51), 100.0);
        }

        ogrenciler.push_back(ogrenci);
    }

    double toplamNotlar = 0;
    double karelerinToplami = 0;
    double enYuksekNot = 0;
    double enDusukNot = 100;
    int notAraligi[3] = { 0 };
    int harfNotuAraligi[9] = { 0 };

    for (auto& ogrenci : ogrenciler) {
        ogrenci.finalNotu = finalNotuHesapla(ogrenci, vizeAgirligi, kisaSinav1Agirligi, kisaSinav2Agirligi, odev1Agirligi, odev2Agirligi);
        toplamNotlar += ogrenci.finalNotu;
        karelerinToplami += pow(ogrenci.finalNotu, 2);

        enYuksekNot = max(enYuksekNot, ogrenci.finalNotu);
        enDusukNot = min(enDusukNot, ogrenci.finalNotu);

        string harfNotu = harfNotuHesapla(ogrenci.finalNotu);

        switch (harfNotu[0]) {
        case 'A':
            harfNotuAraligi[0]++;
            break;
        case 'B':
            harfNotuAraligi[1]++;
            break;
        case 'C':
            harfNotuAraligi[2]++;
            break;
        case 'D':
            harfNotuAraligi[3]++;
            break;
        case 'F':
            harfNotuAraligi[4]++;
            break;
        }

        cout << "Ad: " << setw(8) << left << ogrenci.ad << " " << setw(10) << left << ogrenci.soyad << "\t"
            << "Final Notu: " << fixed << setprecision(2) << setw(6) << ogrenci.finalNotu << "\t"
            << "Harf Notu: " << harfNotu << "\n";
    }

    double ortalamaNot = toplamNotlar / ogrenciSayisi;
    double varyans = (karelerinToplami / ogrenciSayisi) - pow(ortalamaNot, 2);
    double standartSapma = sqrt(varyans);

    cout << "\nSınıf İstatistikleri:\n";
    cout << "Sınıfın ortalama notu: " << ortalamaNot << "\n";
    cout << "Standart Sapma: " << standartSapma << "\n";
    cout << "En Yüksek Not: " << enYuksekNot << "\n";
    cout << "En Düşük Not: " << enDusukNot << "\n";
    cout << "Harf Notu Aralığındaki Öğrenci Sayısı:\n";
    cout << "AA: " << harfNotuAraligi[0] << "\n";
    cout << "BA: " << harfNotuAraligi[1] << "\n";
    cout << "BB: " << harfNotuAraligi[2] << "\n";
    cout << "CB: " << harfNotuAraligi[3] << "\n";
    cout << "FF: " << harfNotuAraligi[4] << "\n";

    return 0;
}