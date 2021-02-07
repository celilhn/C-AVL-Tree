/*
Öğrenci Adı.........: Berat
Öğrenci Soyadı......: Öner
Grup................: 1B
Öğrenci Numarası....: B191210066
*/
#include<iostream>
#include"Eleman.h"


int Eleman::yukseklik(Eleman* N)
{
    if (N == NULL)
        return 0;
    return N->derinlik;
}

Eleman* Eleman::yeniDugumEkle(string adSoyad, int yil)
{
    Eleman* kok = new Eleman();
    kok->adSoyad = adSoyad;
    kok->yil = yil;
    kok->sol = NULL;
    kok->sag = NULL;
    kok->derinlik = 1;
    return(kok);
}
 
Eleman* Eleman::sagDondurme(Eleman* y)
{
    Eleman* x = y->sol;
    Eleman* T2 = x->sag;

    // Rotasyon gerçekleştirme  
    x->sag = y;
    y->sol = T2;

    // Yükseklik güncellemesi 
    if (yukseklik(y->sol) > yukseklik(y->sag))
        y->derinlik = yukseklik(y->sol) + 1;
    else
        y->derinlik = yukseklik(y->sag) + 1;

    if (yukseklik(x->sol) > yukseklik(x->sag))
        x->derinlik = yukseklik(x->sol) + 1;
    else
        x->derinlik = yukseklik(x->sag) + 1;

    // Yeni kök döndürür  
    return x;
}
 
Eleman* Eleman::solDondurme(Eleman* x)
{
    Eleman* y = x->sag;
    Eleman* T2 = y->sol;

    // Rotasyon gerçekleştirme  
    y->sol = x;
    x->sag = T2;

    // Yükseklik güncellemesi 
    if (yukseklik(y->sol) > yukseklik(y->sag))
        y->derinlik = yukseklik(y->sol) + 1;
    else
        y->derinlik = yukseklik(y->sag) + 1;

    if (yukseklik(x->sol) > yukseklik(x->sag))
        x->derinlik = yukseklik(x->sol) + 1;
    else
        x->derinlik = yukseklik(x->sag) + 1;

    // Yeni kök döndürür 
    return y;
}

int Eleman::dengeKatSayisi(Eleman* N)
{
    if (N == NULL)
        return 0;
    return yukseklik(N->sol) - yukseklik(N->sag);
} 

Eleman* Eleman::Ekle(Eleman* kok, string adSoyad, int yil)
{
    /* 1. Normal AVL yerleştirmeyi gerçekleştirin */
    if (kok == NULL)
        return yeniDugumEkle(adSoyad,yil);

    if (yil >= kok->yil)
        kok->sol = Ekle(kok->sol, adSoyad, yil);
    else if (yil < kok->yil)
        kok->sag = Ekle(kok->sag, adSoyad, yil);
    else // AVL'de eşit köklere izin verilmez  
        return kok;

    /* 2. Bu düğümün yüksekliğini güncelle */
    if (yukseklik(kok->sol) > yukseklik(kok->sag))
        kok->derinlik = yukseklik(kok->sol) + 1;
    else
        kok->derinlik = yukseklik(kok->sag) + 1;




    /* 3. Bu düğümün dengesiz olup olmadığını kontrol etmek için bu üst düğümün denge faktörünü alıyoruz */
    int denge = dengeKatSayisi(kok);

    // Bu düğüm dengesiz hale gelirse, o zaman 4 durum vardır

    // sol sol Durumu  
    if (denge > 1 && yil >= kok->sol->yil)
        return sagDondurme(kok);

    // sag sag Durumu   
    if (denge < -1 && yil < kok->sag->yil)
        return solDondurme(kok);

    // sol sag Durumu   
    if (denge > 1 && yil < kok->sol->yil)
    {
        kok->sol = solDondurme(kok->sol);
        return sagDondurme(kok);
    }

    // sag sol Durumu   
    if (denge < -1 && yil >= kok->sag->yil)
    {
        kok->sag = sagDondurme(kok->sag);
        return solDondurme(kok);
    }

    /* (değişmemiş) düğüm işaretçisini döndür */
    return kok;
}

void Eleman::postorderSiralama(Eleman* root)
{
    if (root == NULL)
        return;

    postorderSiralama(root->sol);
    postorderSiralama(root->sag);
    cout << root->adSoyad << " - " << root->yil << " |";
}