#include <iomanip> 
#include <cstring> 
#include <stdlib.h>
#include <conio.h>
#include <stdio.h> 
#include <fstream>                  
#include <iostream>
#include <cstdio>

using namespace std;
struct Musteri_bilgi {
	string ad;
	string soyad;
	char tc[80];
	string telefon;
	string arac_marka;
	string seri_no;
	int fiyat;
};
void Musteri_ekleme();
void Musteri_listeleme();
void Musteri_arama();
void Musteri_silme();
void Musteri_duzenle();


int main() {
	char anamenu;
	do {

		system("cls");

		cout << "|-------Hosgeldiniz------|" << endl;
		cout << "|      Secim Yapiniz     |" << endl;
		cout << "|   1- Musteri ekleme    |" << endl;
		cout << "|   2- Musteri listeleme |" << endl;
		cout << "|     3- Musteri arama   |" << endl;
		cout << "|    4- Musteri silme    |" << endl;
		cout << "|    5- Musteri duzenle  |" << endl;
		cout << "|------------------------|" << endl;

		char secim;
		cout << "\n seciminiz: ";
		cin >> secim;
		switch (secim) {
		case '1':
			Musteri_ekleme();
			break;
		case '2':
			Musteri_listeleme();
			break;
		case '3':
			Musteri_arama();
			break;
		case '4':
			Musteri_silme();
			break;
		case '5':
			Musteri_duzenle();
			break;
		}

		cout << "Ana menuye donmek icin a" << endl << "cikmak icin c" << endl;
		cin >> anamenu;
	} while (anamenu == 'a' || anamenu == 'A');

	return 0;
}

Musteri_bilgi musteri; //******

void Musteri_ekleme() {
	ofstream yaz("musteri.dat", ios::binary | ios::app);
	char secim;
	int adet = 0;
	do {
		cout << "isim: ";
		cin >> musteri.ad;

		cout << "soyisim: ";
		cin >> musteri.soyad;

		cout << "Tc kimlik numarasi: ";
		cin >> musteri.tc;

		cout << "telefon: ";
		cin >> musteri.telefon;

		cout << "arac marka: ";
		cin >> musteri.arac_marka;

		cout << "arac seri no: ";
		cin >> musteri.seri_no;

		cout << "fiyat: ";
		cin >> musteri.fiyat;
		yaz.write((char*)&musteri, sizeof(musteri));

		adet++;
		cout << "Baska Kayit Eklemek Istermisin (E/H)" << endl;
		cin >> secim;
		cout << endl << endl;

	} while (secim == 'e' || secim == 'E');

	cout << adet << " Adet musteri eklendi..." << endl;

	yaz.close();
}
void Musteri_listeleme() {
	ifstream oku("musteri.dat", ios::binary | ios::app);
	oku.seekg(0, ios::end);
	int adet = oku.tellg() / sizeof(musteri);
	if (adet > 0) {
		for (int i = 0;i < adet;i++) {
			oku.seekg(i * sizeof(musteri)); // bu bölümü eklmeyi unuttuðum için hata aldým full
			oku.read((char*)&musteri, sizeof(musteri));
			cout << i + 1 << " . Musteri bilgileri" << endl << endl;
			cout << "musteri ad: " << musteri.ad << endl;
			cout << "musteri soyad: " << musteri.soyad << endl;
			cout << "musteri Tc kimlik numarasi: " << musteri.tc << endl;
			cout << "musteri telefon: " << musteri.telefon << endl;
			cout << "musteri arac marka: " << musteri.arac_marka << endl;
			cout << "arac seri numarasi: " << musteri.seri_no << endl;
			cout << "fiyat: " << musteri.fiyat << endl << endl << endl;

		}
		oku.close();

	}
	else {
		cout << "Kayit BULUNAMADÝ" << endl;
	}
}

void Musteri_arama() {
	ifstream oku("musteri.dat", ios::binary | ios::app);
	oku.seekg(0, ios::end);
	int kayitlar = oku.tellg() / sizeof(musteri);
	char aranan_musteri_tc[80];
	cout << "Aranacak musterinin tc si: ";
	cin >> aranan_musteri_tc;
	if (kayitlar > 0) {
		for (int i = 0;i < kayitlar;i++) {
			oku.seekg(i * sizeof(musteri));
			oku.read((char*)&musteri, sizeof(musteri));
			if(strcmp(musteri.tc,aranan_musteri_tc)==0){
			
				cout << "Bulunan musteri bilgileri" << endl << endl;


				cout << "musteri ad: " << musteri.ad << endl;
				cout << "musteri soyad: " << musteri.soyad << endl;
				cout << "musteri Tc kimlik numarasi: " << musteri.tc << endl;
				cout << "musteri telefon: " << musteri.telefon << endl;
				cout << "musteri arac marka: " << musteri.arac_marka << endl;
				cout << "arac seri numarasi: " << musteri.seri_no << endl;
				cout << "fiyat: " << musteri.fiyat << endl << endl << endl;			
			}
		}
	}
	else {
		cout << "Herhangi bir kayit bulunamadi...";

	}
	oku.close();
}
void Musteri_silme() {
		ifstream oku("musteri.dat", ios::binary | ios::in);
		ofstream yedek_yaz("Yedek.dat", ios::binary | ios::out);

		char aranan_musteri_tc[80];
		char secim;
		bool var = false;

		cout << "Aranacak musterinin tc si: ";
		cin >> aranan_musteri_tc;

		if (oku.is_open() && yedek_yaz.is_open()) {
			while (oku.read((char*)&musteri, sizeof(musteri))) {
				if (strcmp(musteri.tc, aranan_musteri_tc) == 0) {
					cout << "Bulunan musteri bilgileri" << endl << endl;
					cout << "musteri ad: " << musteri.ad << endl;
					cout << "musteri soyad: " << musteri.soyad << endl;
					cout << "musteri Tc kimlik numarasi: " << musteri.tc << endl;
					cout << "musteri telefon: " << musteri.telefon << endl;
					cout << "musteri arac marka: " << musteri.arac_marka << endl;
					cout << "arac seri numarasi: " << musteri.seri_no << endl;
					cout << "fiyat: " << musteri.fiyat << endl << endl;

					cout << "Silmek istediginiz musteri bu mu? (E/h): ";
					cin >> secim;

					if (secim == 'E' || secim == 'e') {
					
						cout << "Musteri silindi!" << endl;
						var = true;
						continue;
					}
				}
				yedek_yaz.write((char*)&musteri, sizeof(musteri));
			}
			oku.close();
			yedek_yaz.close();

			
			remove("musteri.dat");
			rename("Yedek.dat", "musteri.dat");
		}
		else {
			cout << "Dosya açýlmadý!" << endl;
		}
	}

void Musteri_duzenle() {
		ifstream oku("musteri.dat", ios::binary | ios::in);
		ofstream yedek_yaz("Yedek.dat", ios::binary | ios::out);

		char aranan_musteri_tc[80];
		char secim;
		bool var = false;

		cout << "Duzeltmek istediginiz musterinin tc si: ";
		cin >> aranan_musteri_tc;

		if (oku.is_open() && yedek_yaz.is_open()) {
			while (oku.read((char*)&musteri, sizeof(musteri))) {
				if (strcmp(musteri.tc, aranan_musteri_tc) == 0) {
					cout << "Bulunan musteri bilgileri:" << endl;
					cout << "Musteri ad: " << musteri.ad << endl;
					cout << "Musteri soyad: " << musteri.soyad << endl;
					cout << "Musteri Tc kimlik numarasi: " << musteri.tc << endl;
					cout << "Musteri telefon: " << musteri.telefon << endl;
					cout << "Musteri arac marka: " << musteri.arac_marka << endl;
					cout << "Arac seri numarasi: " << musteri.seri_no << endl;
					cout << "Fiyat: " << musteri.fiyat << endl << endl;

					cout << "Bu bilgileri duzenlemek istiyor musunuz? (E/H): ";
					cin >> secim;

					if (secim == 'E' || secim == 'e') {
						
						cout << "Yeni ad: ";
						cin >> musteri.ad;
						cout << "Yeni soyad: ";
						cin >> musteri.soyad;
						cout << "Yeni telefon: ";
						cin >> musteri.telefon;
						cout << "Yeni arac marka: ";
						cin >> musteri.arac_marka;
						cout << "Yeni arac seri no: ";
						cin >> musteri.seri_no;
						cout << "Yeni fiyat: ";
						cin >> musteri.fiyat;

						cout << "Musteri bilgileri basariyla duzenlendi!" << endl;
						var = true;
					}

				}
				yedek_yaz.write((char*)&musteri, sizeof(musteri));
			}

			oku.close();
			yedek_yaz.close();

			if (var) {
				remove("musteri.dat");
				rename("Yedek.dat", "musteri.dat");
			}
			else {
				cout << "Aradiginiz TC kimlik numarasina sahip musteri bulunamadi!" << endl;
			}
		}
		else {
			cout << "Dosya acilamadi!" << endl;
		}
	}
