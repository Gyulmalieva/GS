//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tf_main *f_main;
//---------------------------------------------------------------------------
__fastcall Tf_main::Tf_main(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tf_main::b_sendClick(TObject *Sender)
{
	struct TinputData t;
	t.value = 1.5;
	t.measure = tacc;


	TDateTime* myTime =  new TDateTime(Now());
	String text =  myTime -> FormatString("dd.mm.yyyy") +
		" " + myTime -> FormatString ("hh:mm:ss") + " Я: " +
		e_messege -> Text;
	chat -> Lines -> Add(text);

	String mes = e_messege ->Text;
	if (mes.Pos("Привет")){
		chat->Lines->Add(myTime->FormatString("dd.mm.yyyy") +
		" " + myTime -> FormatString ("hh:mm:ss") + " Бот: " +
		"Привеет");
	}
	if (mes.Pos("дела")&& (mes.Pos("?")== mes.Length())){
		chat->Lines->Add(myTime->FormatString("dd.mm.yyyy") +
		" " + myTime -> FormatString ("hh:mm:ss") + " Бот: " +
		"Норм");
	}
	if (mes.Pos("Пока")){
		chat->Lines->Add(myTime->FormatString("dd.mm.yyyy") +
		" " + myTime -> FormatString ("hh:mm:ss") + " Бот: " +
		"Пока");
	}

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall Tf_main::e_messegeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == '\r') {
		 b_sendClick( Sender);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tf_main::B_analysisClick(TObject *Sender)
{
	int p;
	String text = chat->Lines->GetText();
	String word;

	bool numFound = false;
	char *measureText[] = {"","км/ч","км/ч2","час", "км"};
	int number;
	do{
			p = text.Pos(" ");
				if (p==0){
					word = text;
				}
				else{
					word = text.SubString(1,p-1);
					text = text.SubString(p+1,text.Length());
				}
				if (numFound == true ){
					if (word.Pos("км/ч")>0) {
						inputData[i-1].measure = tvelocity;

					}
					else if (word.Pos("час")>0 || word.Pos("часа")>0 || word.Pos("часов")>0 ) {
						inputData[i-1].measure =ttime;
					}
					else if (word.Pos("км")>0 ) {
						inputData[i-1].measure =tdistance;
					}
					else if (word == "км/ч2" ) {
						inputData[i-1].measure =tacc;
					}
					numFound = false;
				}


			mem->Lines->Add(word);

				try{
					inputData[i].value = word.ToDouble();
					if (word != ",") {
						numFound = true;
						i++;
						mem->Lines->Add("Число");
					}


				}
				catch(const Exception& e){
				   number=0;
				   if (word.Pos("один")) {
						number = 1;

				   }
				   else if (word.Pos("два")) {
						number = 2;

				   }
				   else if (word.Pos("три")) {
						number = 3;
						//	chat->Lines->Add(number);
				   }
				   else if (word.Pos("четыре")) {
						number = 4;
					   //	chat->Lines->Add(number);
				   }
				   else if (word.Pos("пять")) {
						number = 5;
						//chat->Lines->Add(number);
				   }
				   else if (word.Pos("шесть")) {
						number = 6;
					   //	chat->Lines->Add(number);
				   }
				   else if (word.Pos("семь")) {
						number = 7;
					   //	chat->Lines->Add(number);
				   }
				   else if (word.Pos("восемь")) {
						number = 8;
					   //	chat->Lines->Add(number);
				   }
				   else if (word.Pos("девять")) {
						number = 9;
					   //	chat->Lines->Add(number);
				   }
				   else if (word.Pos("десять")) {
						number = 10;
						//	chat->Lines->Add(number);
				   }
				   if (number !=0 ){
						inputData[i].value = number;
						i++;
						numFound = true;

				   }
				   if (word == "час" && numFound == false) {
					   inputData[i].value = 1;
					   inputData[i].measure = ttime;
					   i++;

				   }

				}

		} while (p);
	for (int j = 0; j < i; j++) {
		mem->Lines->Add(FloatToStr(inputData[j].value) + " " + measureText[inputData[j].measure] );

	}
}
//---------------------------------------------------------------------------

void __fastcall Tf_main::SoldClick(TObject *Sender)
{
	char *measureText[] = {"","км/ч","км/ч2","час", "км"};
	int p;
   String text = chat->Lines->GetText();
   p=text.Pos("Найдите среднюю скорость");
	if (p==0) {
		chat->Lines->Add("Нет решения");
		return;
	}
	double T, V , S, S1;
	double v[10];
	double t[10];
	double s[10];
	int j;
	int jv=0;
	int jt=0;
	int js=0;
	for (j = 0; j < i; j++) {
			if (inputData[j].measure == tvelocity) {
				v[jv]= inputData[j].value;
				jv++;

			}
			if (inputData[j].measure == ttime) {
				t[jt]= inputData[j].value;

				//chat->Lines->Add(T);
				jt++;

			}
			if (inputData[j].measure == tdistance) {
				s[js]= inputData[j].value;
			   //	S1 = S1+ inputData[j].value;
				js++;
				//chat->Lines->Add(S);

			}

	}
	if (jv>0 && jt>0 ) {


		for (int k=0; k < jv; k++) {

			 S = S+ v[k]*t[k];
			 T = T+ t[k];
		 }

	}
	if (jv>0 && js>0) {


	  for (int l=0; l < js; l++) {

			 S = S+ s[l];
			 mem->Lines->Add(S);
			 T=T+ s[l]/v[l];
	  }


	}
	if (T == 0 ) {
		chat->Lines->Add("Проведите анализ");
	}
	else {
		V = S/T;
		//Ans->Lines->Add(V);
		inputData[i].value = V;
		inputData[i].measure = tvelocity;
		Ans->Lines->Add(FloatToStr(inputData[i].value) + " " + measureText[inputData[i].measure]);
	}

   //	V=S/T;
   //	chat->Lines->Add("Ответ");
	//chat->Lines->Add("Ответ:" + FloatToStr(V));

}
//---------------------------------------------------------------------------


void __fastcall Tf_main::Button1Click(TObject *Sender)
{

ADOQuery1->Close();
ADOQuery1->SQL->Clear();
ADOQuery1->SQL->Add("select * from word where word=:param1");
ADOQuery1->Parameters->ParamByName("param1")->Value = Edit1->Text;
ADOQuery1->Open();
AnsiString str = ADOQuery1->FieldByName("number")->AsString;
Label1->Caption = str;

}
//---------------------------------------------------------------------------





void __fastcall Tf_main::AddClick(TObject *Sender)
{
	int p;
	String text = chat->Lines->GetText();
	String word;
	String punkts;
	//bool punkts;
	bool numFound = false;
	char *measureText[] = {"","км/ч","км/ч2","час", "км"};
	int number;
	//words = (**char)0;
	words = NULL;
	char *pc=NULL;
	words_number=0;
		do{
			p = text.Pos(" ");
				if (p==0){
					//word = word.SubString(1, word.Length()-1 );
					word = text;
				}
				else{
					word = text.SubString(1,p-1);
					text = text.SubString(p+1,text.Length());
					int l = word.Length();
					int c = word.Pos(",");
					int d = word.Pos(".");
						if (l==d || l==c) {
							punkts =  word.SubString(word.Length(), word.Length());
							word = word.SubString(1, word.Length()-1 );
							//punkt = true;
						}
				}
			pc = (char *)malloc(word.Length()+1);
				if (pc == NULL) {
					  return;
				}
			words_number++;
				//words = malloc(words_number*sizeof(char *));
				// words = realloc(words,words_number*sizeof(char *)) ;
				if(words_number==NULL){
					words = (char **)malloc(words_number*sizeof(char *));
				}
				else{
					words = (char **)realloc(words,words_number*sizeof(char *)) ;
				}

				for (int j = 0; j <= word.Length(); j++) {
					pc[j] = (char)word.c_str()[j];
				}
				//strcpy(pc, (char *)word.c_str());

			WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, word.c_str(), -1, pc, word.Length()+1, NULL, NULL);
			words[words_number-1]= pc;


			 if(punkts !=NULL){
				 pc = (char *)malloc(punkts.Length()+1);
					if (pc == NULL) {
						  return;
					}
				words_number++;
					//words = malloc(words_number*sizeof(char *));
					// words = realloc(words,words_number*sizeof(char *)) ;
					if(words_number==NULL){
						words = (char **)malloc(words_number*sizeof(char *));
					}
					else{
						words = (char **)realloc(words,words_number*sizeof(char *)) ;
					}

					/*for (int j = 0; j <= punkts.Length(); j++) {
						pc[j] = (char)punkts.c_str()[j];
					}  */
					//strcpy(pc, (char *)word.c_str());

			   WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, punkts.c_str(), -1, pc, punkts.Length()+1, NULL, NULL);
			   words[words_number-1]= pc;
			   punkts = 0;
			}





		} while (p);
		for (i=0; i < words_number; i++) {
			Memo_mass->Lines->Add(words[i]);
		}

}
//---------------------------------------------------------------------------


void __fastcall Tf_main::NewClick(TObject *Sender)
{
 bool numFound = false;
  float result;

  randomize();
  M_new->Text=" ";
	for (i=0; i < words_number; i++) {
		sscanf (words[i], "%f", &result);
			if (sscanf (words[i], "%f", &result)>0) {
				numFound = true;
				M_new->Text=M_new->Text+" "+rand() %100;

			}
			else{
				//M_new->Text=M_new->Text+" "+words[i];
				String query="SELECT `sinonim` FROM `sinonimi` WHERE `groupid`=(SELECT `groupid` FROM `sinonimi` WHERE `sinonim`=\"" ;
				 query= query+words[i]+"\")";
				ADOQuery1->Close();
				ADOQuery1->SQL->Clear();
				ADOQuery1->SQL->Add(query);
				//ADOQuery1->Parameters->ParamByName("param1")->Value = words[i];
				ADOQuery1->Open();
				AnsiString str = ADOQuery1->FieldByName("sinonim")->AsString;
				//Label1->Caption = str;
				if (str== "") {
					M_new->Text=M_new->Text+" "+words[i];
				}
				else {
				M_new->Text=M_new->Text+" "+str;
				}
			}

	}



}
//---------------------------------------------------------------------------

