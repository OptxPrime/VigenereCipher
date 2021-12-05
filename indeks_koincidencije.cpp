#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<cmath>


using namespace std;

/// frekvencije slova u hrvatskom jeziku
vector<double>p{ 0.115, 0.015, 0.028, 0.037, 0.084, 0.003, 0.016, 0.008, 0.098, 0.051, 0.036,
            0.033, 0.031, 0.066,0.090, 0.029, 0, 0.054, 0.056, 0.048, 0.043, 0.035, 0, 0, 0,0.023};

    vector<double> nadjiFrekvenciju( string blok ){ /// funkcija koja nalazi niz apsolutnih frekvencija stringa
        vector<double> frekvencija(26,0);
        for( int i=0;i<blok.size();i++ ){
            frekvencija[ blok[i] - 'A' ]++;
        }
        return frekvencija;
    }

    const double hrvatskiIndeksKoincidencije = 0.064; /// prosjecni indeks koincidencije hrvatskog jezika

int main()
{
    cout<<"Unesite poruku sifriranu preko Vigenerovog chipera!"<<endl<<endl;
    string s;
    cin>>s;
    for( int i=0;i<s.size();i++ ) s[i] = toupper(s[i]); /// unosi se string sa standardnog ulaza i pretvara u velika slova


    vector<string> blokovi;
    vector<double>frekvencija;
    double indeksKoincidencije = 0, najblizi = 100;
    int duzina;


    for( int m = 2; m<=10; m++ ){ /// probavamo duzine kljuca od 2 do 10. naravno, ove granice se mogu promjeniti po potrebi

        blokovi.resize(m);
        for( int i = 0;i<s.size();i++ ){
            blokovi[i%m].push_back(s[i]); /// slova grupisemo po ostatku pozicije tog slova po modulu m
        }                                 /// slova u istoj grupi su sifrirana istim slovom kljuca, ako je m zaista prava duzina

        double sumaIndeksaKoincidencije = 0;

        for( int i=0;i<blokovi.size();i++ ){
            frekvencija = nadjiFrekvenciju( blokovi[i] ); ///  za svaki blok/grupu nalazimo niz frekvencija slova

            for( int i=0;i<26;i++ ){
                indeksKoincidencije += frekvencija[i]*(frekvencija[i]-1); /// pronalazimo indeks koincidencije
            }
            int n = blokovi[i].size();
            indeksKoincidencije /= (double)(n*(n-1));
            sumaIndeksaKoincidencije += indeksKoincidencije; /// suma indeksa koincidencije nam treba da bi nasli prosjecni
            }
            double prosjecniIndeksKoincidencije = sumaIndeksaKoincidencije/m; /// zanima nas prosjecni indeks koincidencije od svih blokova
            if( abs(prosjecniIndeksKoincidencije - hrvatskiIndeksKoincidencije) < najblizi ){ /// ako je ova duzina m proizvela blokove koji su u prosjeku najblizi hrvatskom indeksu koincidencije
                najblizi = abs(prosjecniIndeksKoincidencije-hrvatskiIndeksKoincidencije); /// onda to sacuvamo
                duzina = m; /// spasimo tu duzinu jer je ona dosad najvjerovatnija
            }
        blokovi.clear(); /// ocistimo blokove, jer za druge duzine potpuno se mjenjaju velicine blokova, i sami blokovi

    }
    /// sve dovde je bilo za pronalazak duzine sifrata

    cout<<endl<<"Duzina kljuca je"<<endl;
    cout<<duzina<<endl;

    blokovi.resize(duzina);

    for( int i=0;i<s.size();i++ ){
        blokovi[i%duzina] += s[i]; /// sad opet formiramo blokove, sa duzinom koju smo nasli
    }

    string sifrat = ""; /// ovo je ustvari kljuc
    double najveci;
    int pomak;

    for( int i = 0;i<blokovi.size();i++ ){
        najveci = 0;
        pomak = 0;
        frekvencija = nadjiFrekvenciju(blokovi[i]); /// opet nam trebaju frekvencije

        double M = 0;
        for(int g=0;g<26;g++){ /// probavamo svako slovo abecede
            for( int j = 0;j<26;j++ ){
                M += p[j]*frekvencija[ ((j-g)+26)%26 ]; /// racunamo indeks koincidencije teksta ovog bloka pomjerenog za odgovarajuce slovo i prosjecnog otvorenog teksta na hrvatskom jeziku
            }
            int n = blokovi[i].size();
            M/=n; /// podjelimo sa velicinom bloka da dobimemo indeks koincidencije
            if(M>najveci){ /// trazimo najveci, jer ce pravo slovo proizvesti indeks koincidencije najblizi 0.064, dok ce ostali puno manje(tako je ocekivano)
                najveci=M;
                pomak=g;
            }
        }
        sifrat += char(( -pomak+26 )%26+'A'); /// kad smo skontali koje je slovo koristeno za ovaj blok(najvjerovatnije), dodamo ga u kljuc
    }

    cout<<endl<<"Kljuc koji je koristen je:"<<endl;
    cout<<sifrat<<endl;
    string rezultat = "";

    for( int i=0;i<s.size();i++ ){
        rezultat += char((s[i]-sifrat[i%duzina]+26)%26 + 'A');
    }
    cout<<endl<<"Izvorna poruka glasi:"<<endl;
    cout<<rezultat<<endl;

return 0;
}






