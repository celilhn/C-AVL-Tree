/*
Öğrenci Adı.........: Berat
Öğrenci Soyadı......: Öner
Grup................: 1B
Öğrenci Numarası....: B191210066
*/
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include"Firma.h"


using namespace std;

string firmaAd[1000], calisanAdSoyad[1000], _firmaAd, _calisanAdSoyad;
int baslangicYil[1000], _baslangicYil;
bool isExistFirma = false;
int satirSayisi = 0;

// String sayıyı integer'e donusturme fonksiyonu
int donusturmeFonksiyonu(string sayi)
{
    int carpim = 1, sonuc = 0, temp;
    for (int i = sayi.length() - 1; i >= 0; i--)
    {
        temp = sayi[i] - 48;
        sonuc += temp * carpim;
        carpim = carpim * 10;
    }
    return sonuc;
}

// Dosya okuma ve dosyadaki isim, firma ve yıl bilgilerini değişkenlere atama
void dosyaOku()  
{
    ifstream dosyaoku("Veri.txt");
    string satir = "";
    int index, temp_dogum, temp_baslangicYil, sayac = 0;
    string _dogumYili, _baslangicYil;

    if (dosyaoku.is_open()) {
        while (getline(dosyaoku, satir))
        {
            index = satir.find("#", 0);
            firmaAd[satirSayisi] = satir.substr(0, index);
            temp_dogum = index + 1;
            index = satir.find("#", index + 1);
            calisanAdSoyad[satirSayisi] = satir.substr(temp_dogum, index - temp_dogum);

            temp_baslangicYil = index + 1;
            index = satir.find("#", index + 1);
            _baslangicYil = satir.substr(temp_baslangicYil, index - temp_baslangicYil);
            baslangicYil[satirSayisi] = donusturmeFonksiyonu(_baslangicYil);
            
            satirSayisi++;
        }
        dosyaoku.close();
    }
}

void yukseltveElemanEkle(Firma* kok, string firmaAd, bool calisan)
{
    if (kok == NULL)
        return;

    yukseltveElemanEkle(kok->sol, firmaAd, calisan);
    yukseltveElemanEkle(kok->sag, firmaAd, calisan);

    if (kok->firmaAd == firmaAd)
    {
        if (calisan)
            kok->calisanSayisi++;

        kok->eleman = kok->eleman->Ekle(kok->eleman, _calisanAdSoyad, _baslangicYil);

    }
}

string _firmalar[100]; int _firmaSayisi = 0; bool _isExistFirma = false;
void yazdir(Firma* root)
{
    if (root == NULL)
        return;

    yazdir(root->sol);
    yazdir(root->sag);

    cout << root->firmaAd << endl;
    root->eleman->postorderSiralama(root->eleman);
    cout << endl;
}


int main() {
    SetConsoleOutputCP(65001);
    int firmaSayisi = 0;
    string firmalar[100];
    bool isExistFirma = false;
    Firma* kok = NULL;

    dosyaOku();

    for (int i = 0; i < satirSayisi; i++)
    {
        _firmaAd = firmaAd[i];
        _calisanAdSoyad = calisanAdSoyad[i];
        _baslangicYil = baslangicYil[i];

        for (int j = 0; j < firmaSayisi; j++)
        {
            if (_firmaAd == firmalar[j])
                isExistFirma = true;
        }
        if (i == 10)
            int a = 2;
        if (isExistFirma)
        {
            isExistFirma = false;
            yukseltveElemanEkle(kok, _firmaAd,true);
            kok = kok->FirmaDengele(kok);
        }
        else
        {
            kok = kok->Ekle(kok, _firmaAd, 0);
            yukseltveElemanEkle(kok, _firmaAd,false);
            kok = kok->FirmaDengele(kok);
            firmalar[firmaSayisi] = _firmaAd;
            firmaSayisi++;
        }
    }
    yazdir(kok);
    system("pause");
    return 0;
}