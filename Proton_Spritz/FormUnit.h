//---------------------------------------------------------------------------

#ifndef FormUnitH
#define FormUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TOpenDialog *OpenDialog1;
	TButton *OpenButton;
	TLabel *Label1;
	TEdit *KeyEdit;
	TButton *TestButton;
	TMemo *LogMemo;
	TLabel *Label2;
	void __fastcall OpenButtonClick(TObject *Sender);
	void __fastcall TestButtonClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations

	__fastcall TForm1(TComponent* Owner);
	char * UnicodeToChar(UnicodeString input);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
