//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <stdio.h>
//---------------------------------------------------------------------------
class Tf_main : public TForm
{
__published:	// IDE-managed Components
	TButton *b_send;
	TEdit *e_messege;
	TMemo *chat;
	TButton *B_analysis;
	TButton *Sold;
	TMemo *mem;
	TMemo *Ans;
	TADOTable *ADOTable1;
	TDataSource *DataSource1;
	TDBGrid *DBGrid1;
	TADOQuery *ADOQuery1;
	TLabel *Label1;
	TEdit *Edit1;
	TButton *Button1;
	TButton *Devide;
	TButton *Add;
	TMemo *Memo_mass;
	TButton *New;
	TMemo *M_new;



	void __fastcall b_sendClick(TObject *Sender);

	void __fastcall e_messegeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall B_analysisClick(TObject *Sender);
	void __fastcall SoldClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall AddClick(TObject *Sender);
	void __fastcall NewClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall Tf_main(TComponent* Owner);
};
		enum Tmeasure { tvelocity =1, tacc=2, ttime=3, tdistance=4} Emeasure;

		struct TinputData {
			double value;
			Tmeasure measure;
		} inputData[10];
		int i=0;

		char **words;
		int words_number;


//---------------------------------------------------------------------------
extern PACKAGE Tf_main *f_main;
//---------------------------------------------------------------------------
#endif
