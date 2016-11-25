#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <bitset>

using namespace std;


struct kolor
{
	unsigned char B;
	unsigned char G;
	unsigned char R;
};
#pragma pack(push,1)
struct Headerinfo
{
	char  signature1;			// Sygnatura obraza BM bitmapa 
	char  signature2;
	int   fileSize;				// Oznacza rozmiar calego pliku w bajtach
	int   reserved;				// Zarezerwowany
	int   dataOffset;			// Poczatkowy adres bitow w tab pikseli(OFFSET)
};
#pragma pack(pop)

#pragma pack(push,1)
struct BitmapInfoHeader
{
	int   headerSize;			// Dlugoœæ w bitach info nag³owka
	int   width;			    // Szerokoœæ obrazka w PIX
	int   height;				// Wysokoœæ obrazka w PIX
	short planes;				// Liczba warstw kolorów
	short bitPerPixel;			// Liczba bitów na piksel
	int   compression;			// Kompresja 0 Brak kompresji | 1 RLE 8bit | 2 RLE 4bit
	int   imageSize;			// Rozmiar samego obrazka
	int   xResolution;			// Rozdzielczoœæ pozioma
	int   yResolution;			// Rozdzielczoœæ pionowa
	int   colorUsed;			// Liczba kolorów w palecie
	int   colorImportant;		// Liczba wa¿nych kolorów gdy 0 -  Wszystkie s¹ równie wa¿ne


								//te dwa ostatnie nie wiaodmo czy trzeba bo struktura wtedy zajmuje wiêcej ni¿ 40
	int   colorRotation;		// Flaga sygnalizuj¹ca rotacje palety 0 - Brak rotacji
	short reservedByte;			// Bit zarezerwowany (buffor chyba)
};
#pragma pack(pop)

/*
------------OTWIERANIE DO ODCZYTU--------------
Otwarcie binarne
Arg: Strumien pliku | Nazwa pliku
*/
void openRead(ifstream &fin, string name)
{
	size_t pos = name.rfind(".bmp");

	if (pos = string::npos)
	{
		fin.open(name + ".bmp", ios::binary);
		if (!fin)
			exit(0);
	}
	else
	{
		fin.open(name, ios::binary);
		if (!fin)
			exit(0);
	}
}
/*
----------TWORZENIE TABLICY DYNAMICZNEJ------------
Funkcja przyjmuje jeden argument jakim jest rozmiar
*/
kolor *createArray(long long size)
{
	kolor *tab = nullptr;
	try
	{
		tab = new kolor[size];
	}
	catch (bad_alloc)
	{
		cout << "Brak pamiêci";
		system("pause");
		exit(0);
	}
	return tab;
}

int main()
{
	ifstream file;
	openRead(file, "szop");

	Headerinfo info;
	BitmapInfoHeader dataInfo;

	file.read((char*)&info, sizeof(info));
	file.seekg(14, ios_base::beg);
	file.read((char*)&dataInfo, sizeof(dataInfo));

	int pixValue = dataInfo.bitPerPixel * dataInfo.height * dataInfo.width;

	//kolor *BGR = createArray(pixValue);
	//long long size_of_struct = 3 * pixValue;

	uint8_t *pixele = new uint8_t[pixValue];

	file.seekg(info.dataOffset, ios_base::beg);

	file.read((char*)pixele, pixValue);

	if (file.fail())
	{
		cout << "Poza bitmapa";
		system("pause");
		exit(0);
	}
	//file.read((char*)BGR, size_of_struct);



	file.close();

	system("pause");
	return 0;
}
