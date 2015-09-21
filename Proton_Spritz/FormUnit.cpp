//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>

#pragma hdrstop

#include "FormUnit.h"
#include "spritz.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OpenButtonClick(TObject *Sender)
{
	if (OpenDialog1->Execute())
	{
		Label1->Caption=OpenDialog1->FileName;
	}
	else
	{
		return;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TestButtonClick(TObject *Sender)
{
	int keyLength = KeyEdit->Text.Length();
	char *Key = new char[keyLength];
	unsigned char *masterKey = new unsigned char[keyLength];
	strcpy(Key,UnicodeToChar(KeyEdit->Text));
    for (int i = 0; i < keyLength; i++)
		masterKey[i]=Key[i];

	LARGE_INTEGER start, finish, freq;
	QueryPerformanceFrequency( &freq );
	QueryPerformanceCounter( &start );

	struct stat buf;
	stat(UnicodeToChar(OpenDialog1->FileName),&buf);
	int filesize=buf.st_size;

	FILE *f=fopen(UnicodeToChar(OpenDialog1->FileName), "rb");
	if (f==NULL)
	{
		LogMemo->Lines->Add("ERR: Can not open file "+OpenDialog1->FileName+" !");
		return;
	}
	unsigned char *plainByte =new unsigned char[filesize];
	fread(plainByte,sizeof(unsigned char),filesize,f);
	fclose(f);


	FILE *f_enc=fopen(UnicodeToChar(OpenDialog1->FileName+".enc"), "wb");
	unsigned char *encryptByte =new unsigned char[filesize];
	spritz_encrypt(encryptByte, plainByte, filesize,
								(unsigned char *)"Some session code",17,
								masterKey, keyLength);
	fwrite(encryptByte,sizeof(unsigned char),filesize,f_enc);
	fclose(f_enc);

	QueryPerformanceCounter( &finish );
	// time - время в секундах
	double time = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
	LogMemo->Lines->Add("!\tCrypting done in-> "+FloatToStr(time)+" sec.");
	LogMemo->Lines->Add("\tsize of file-> "+IntToStr(filesize)+" byte");
	LogMemo->Lines->Add("\tspeed-> "+FloatToStr(filesize*8/time/1024/1024)+" Mbit per sec.");



	QueryPerformanceFrequency( &freq );
	QueryPerformanceCounter( &start );

	FILE *f_dec=fopen(UnicodeToChar(OpenDialog1->FileName+".dec"), "wb");
	unsigned char *decryptByte =new unsigned char[filesize];
	spritz_decrypt(decryptByte, encryptByte, filesize,
								(unsigned char *)"Some session code",17,
								masterKey, keyLength);
	fwrite(decryptByte,sizeof(unsigned char),filesize,f_dec);
	fclose(f_dec);

	QueryPerformanceCounter( &finish );
	// time - время в секундах
	time = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
	LogMemo->Lines->Add("!\tDecrypting done in-> "+FloatToStr(time)+" sec.");
	LogMemo->Lines->Add("\tsize of file-> "+IntToStr(filesize)+" byte");
	LogMemo->Lines->Add("\tspeed-> "+FloatToStr(filesize*8/time/1024/1024)+" Mbit per sec.");

	for (long long i = 0; i < filesize; i++)
	{
		if (plainByte[i]!=decryptByte[i])
		{
			LogMemo->Lines->Add("ERR: not compare at "+IntToStr(i)+" byte!!!");
		}
	}

	delete masterKey;
	delete plainByte;
	delete encryptByte;
	delete decryptByte;
}
//---------------------------------------------------------------------------


char* TForm1::UnicodeToChar(UnicodeString input)
{
	AnsiString a = input.c_str();
	char *b = a.c_str();
	return b;
}



void __fastcall TForm1::FormCreate(TObject *Sender)
{
	LogMemo->Clear();
}
//---------------------------------------------------------------------------


