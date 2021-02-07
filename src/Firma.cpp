/*
Öğrenci Adı.........: Berat
Öğrenci Soyadı......: Öner
Grup................: 1B
Öğrenci Numarası....: B191210066
*/
#include<iostream>
#include"Firma.h"

int Firma::yukseklik(Firma* N)
{
    if (N == NULL)
        return 0;
    return N->derinlik;
}

Firma* Firma:: yeniDugumEkle(string firmaAd)
{
    Firma* kok = new Firma();
    kok->calisanSayisi = 1;
    kok->firmaAd = firmaAd;
    kok->sol = NULL;
    kok->sag = NULL;
    kok->derinlik = 1;
    return(kok);
}

Firma* Firma::sagDondurme(Firma* y)
{
    Firma* x = y->sol;
    Firma* T2 = x->sag;

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

Firma* Firma::solDondurme(Firma* x)
{
    Firma* y = x->sag;
    Firma* T2 = y->sol;

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

int Firma::dengeKatSayisi(Firma* N)
{
    if (N == NULL)
        return 0;
    return yukseklik(N->sol) - yukseklik(N->sag);
} 

Firma* Firma::Ekle(Firma* kok, string firmaAd, int derinlik)
{
    /* 1. Normal BST yerleştirmeyi gerçekleştirin */
    if (kok == NULL)
        return yeniDugumEkle(firmaAd);

    if (derinlik <= kok->derinlik)
        kok->sol = Ekle(kok->sol, firmaAd, derinlik);
    else if (derinlik > kok->derinlik)
        kok->sag = Ekle(kok->sag, firmaAd, derinlik);
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
    if (denge > 1 && derinlik <= kok->sol->derinlik)
        return sagDondurme(kok);

    // sag sag Durumu   
    if (denge < -1 && derinlik > kok->sag->derinlik)
        return solDondurme(kok);

    // sol sag Durumu  
    if (denge > 1 && derinlik > kok->sol->derinlik)
    {
        kok->sol = solDondurme(kok->sol);
        return sagDondurme(kok);
    }

    // sag sol Durumu   
    if (denge < -1 && derinlik <= kok->sag->derinlik)
    {
        kok->sag = sagDondurme(kok->sag);
        return solDondurme(kok);
    }

    /* (değişmemiş) düğüm işaretçisini döndür */
    return kok;
}

void Firma::postorderSiralama(Firma* root)
{
    if (root == NULL)
        return;

    postorderSiralama(root->sol);
    postorderSiralama(root->sag);
    cout << root->firmaAd << endl;
}

// Ağacı dengeleme fonksiyonu
Firma* Firma::FirmaDengele(Firma* kok)
{
    if (kok == NULL)
        return kok;
    
    kok->sol = FirmaDengele(kok->sol);
    kok->sag = FirmaDengele(kok->sag);

    if (kok->sag == NULL && kok->sol == NULL)
        return kok;

   if (kok->sag != NULL && kok->sol != NULL)
    {
        if (kok->sol->calisanSayisi > kok->sag->calisanSayisi)
        {
            Firma* _kok;
            Firma* _kokSolSol = kok->sol->sol;
            Firma* _kokSolSag = kok->sol->sag;
            Firma* _kokSagSol = kok->sag->sol;
            Firma* _kokSagSag = kok->sag->sag;

            _kok = kok->sag;

            kok->sag = kok->sol;
            kok->sol = _kok;

            kok->sol->sol = _kokSolSol;
            kok->sol->sag = _kokSolSag;
            kok->sag->sol = _kokSagSol;
            kok->sag->sag = _kokSagSag;

        }

    }
    
    if (kok->sol != NULL)
    {
        if (kok->sol->calisanSayisi > kok->calisanSayisi)
        {
            Firma* _kok;
            Firma* _kokSolSol = kok->sol->sol;
            Firma* _kokSolSag = kok->sol->sag;
            Firma* _kokSag = kok->sag;

            _kok = kok;

            kok = kok->sol;
            kok->sol = _kok;

            kok->sol->sol = _kokSolSol;
            kok->sol->sag = _kokSolSag;
            kok->sag = _kokSag;

        }
    }

    if (kok->sag != NULL)
    {
        if (kok->calisanSayisi > kok->sag->calisanSayisi)
        {
            Firma* _kok;
            Firma* _kokSagSol = kok->sag->sol;
            Firma* _kokSagSag = kok->sag->sag;
            Firma* _kokSol = kok->sol;

            _kok = kok;

            kok = kok->sag;
            kok->sag = _kok;

            kok->sag->sol = _kokSagSol;
            kok->sag->sag = _kokSagSag;
            kok->sol = _kokSol;
        }
    }
    return kok;
}
