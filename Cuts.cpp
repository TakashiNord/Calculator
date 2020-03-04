//---------------------------------------------------------------------------
#include <stdio.h>
#include <math.h>

#define PI  3.1415926

#include <vcl.h>
#pragma hdrstop

#include "Cuts.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ElTrayInfo"
#pragma resource "*.dfm"
TFormCuts *FormCuts;
//---------------------------------------------------------------------------
__fastcall TFormCuts::TFormCuts(TComponent* Owner)
        : TForm(Owner)
{
  /*EditStn->Text="0.0";
  EditStVc->Text="0.0";
  EditStP->Text="0.0";
  EditStPn->Text="0.0";
  EditStM->Text="0.0";
  EditSthm2->Text="0.0";
  EditStQ->Text="0.0";
  EditStVf->Text="0.0";
  EditStfz->Text="0.0"; */

  AnsiString s;
  BaseD->ItemIndex=14;
  BaseZ->ItemIndex=1;
  s=BaseD->Text;
  BaseB->Text=FloatToStr(atof(s.c_str())/2.);
  BaseT->Text=FloatToStr(atof(s.c_str())/2.);
  BaseVc->Text="560.";
  Basefz->Text="0.3";
  ComboBoxStkpd->ItemIndex=0;

}
//---------------------------------------------------------------------------

void TFormCuts::OutputMessage(AnsiString s)
{
    //FormMessage->ElFlatMemoMes->Lines->Append(s);
    ElTrayInfo1->Message=s;
    ElTrayInfo1->Show();
}
//---------------------------------------------------------------------------

int TFormCuts::CalcStnV(TObject *Sender)
{
  char s[80]; String str;
  int mach; // станок
  double D; //исходные данные
  double tn,tvc; // рассчитываемые параметры : ..., мощность

 /* Проверка на правильность ввода числовых значений*/
  /*диаметр*/
  str=BaseD->Text;
  D=atof(str.c_str());
  if (D<=0.) {
    D=0.;
    s[0]='\0'; sprintf(s,"%.2lf",D); BaseD->Text=s;
    BaseD->SetFocus(); BaseD->SelectAll();
    OutputMessage("Ошибка задания 'диаметра инструмента' - D");
    Application->MessageBox("Ошибка задания 'диаметра инструмента' - D","Предупреждение...",MB_OK);
    return (-1);
  }

  /*обороты */
  str=EditStn->Text;
  tn=atof(str.c_str());
  if (tn<=0.) {
    tn=0;
    s[0]='\0'; sprintf(s,"%.3lf",tn); EditStn->Text=s;
    EditStn->SetFocus(); EditStn->SelectAll();
    OutputMessage("Ошибка задания оборотов шпинделя...<=0");
  }

  // Расчет скорости резания
  tvc=(D*PI*tn)/1000.;
  s[0]='\0'; sprintf(s,"%.3lf",tvc);  EditStVc->Text=s;
  EditStVc->SetFocus(); EditStVc->SelectAll();

  return (0);
}
//---------------------------------------------------------------------------

int TFormCuts::CalcStQ(TObject *Sender)
{
  char s[80]; String str;
  int mach; // станок
  double ap,ae; //исходные данные
  double tvf,Q; // рассчитываемые параметры : ..., мощность

  /*Ширина резания*/
  str=BaseB->Text;
  ap=atof(str.c_str());
  if (ap<=0.) {
    ap=0.;
    s[0]='\0'; sprintf(s,"%.3lf",ap); BaseB->Text=s;
    BaseB->SetFocus(); BaseB->SelectAll();
    OutputMessage("Ошибка задания ширины реза...<=0");
  }

  /*Глубина реза*/
  str=BaseT->Text;
  ae=atof(str.c_str());
  if (ae<=0.) {
    ae=0;
    s[0]='\0'; sprintf(s,"%.3lf",ae); BaseT->Text=s;
    BaseT->SetFocus(); BaseT->SelectAll();
    OutputMessage("Ошибка задания глубины реза...<=0");
  }

  /*подачи резания*/
  str=EditStVf->Text;
  tvf=atof(str.c_str());
  if (tvf<=0.) {
    tvf=0;
    s[0]='\0'; sprintf(s,"%.3lf",tvf); EditStVf->Text=s;
    EditStVf->SetFocus(); EditStVf->SelectAll();
    OutputMessage("Ошибка задания подачи реза...<=0");
  }

  // Скорость сьема материала
  Q=(ae*ap*tvf)/1000.;
  s[0]='\0'; sprintf(s,"%.5lf",Q); EditStQ->Text=s;

  return (0);
}
//---------------------------------------------------------------------------


int TFormCuts::CalcSthm(TObject *Sender)
{
  double vd; int vi=0 ; char s[80];  String str;
  int mach; // станок
  double D,z,ap,ae,fz; //исходные данные
  double ak,fsi ; // Стружка
  double thm; // рассчитываемые параметры : ..., мощность

  /*диаметр*/
  str=BaseD->Text;
  D=atof(str.c_str());
  if (D<=0.) {
    D=0.;
    s[0]='\0'; sprintf(s,"%.3lf",D); BaseD->Text=s; BaseD->SetFocus(); BaseD->SelectAll();
    Application->MessageBox("Ошибка задания 'диаметра инструмента' - D","Предупреждение...",MB_OK);
    return(-1);
  }

  /*Глубина реза*/
  str=BaseT->Text;
  ae=atof(str.c_str());
  if (ae<=0.) {
    ae=0;
    s[0]='\0'; sprintf(s,"%.3lf",ae); BaseT->Text=s;
    BaseT->SetFocus(); BaseT->SelectAll();
    Application->MessageBox("Ошибка задания 'Глубина реза' - ae","Предупреждение...",MB_OK);
    return (-1);
  }

  /*Подача на зуб*/
  str=EditStfz->Text;
  fz=atof(str.c_str());
  if (fz<=0.) {
    fz=0;
    s[0]='\0'; sprintf(s,"%.5lf",fz); EditStfz->Text=s;
    EditStfz->SetFocus(); EditStfz->SelectAll();
    Application->MessageBox("Ошибка задания 'Подача на зуб' - fz","Предупреждение...",MB_OK);
  }

  // Средняя толщина стружки
  if (D<=0.) {
  	Application->MessageBox("Средняя толщина стружки \n D=0. \n Расчет прерван.","Предупреждение...",MB_OK);
  	return(-1) ;
  }

  vi=0;
  fsi=0.1;
  if (vi==0) { fsi=180./PI*2.*asin(ae/D); } else { fsi=90.+180./PI*asin((ae-D/2.)/(D/2.)); }
  vd=ae/D;

  thm=fz*sqrt(ae/D);

  s[0]='\0'; sprintf(s,"%.8lf",thm); EditSthm2->Text=s;

  EditSthm2->SetFocus(); EditSthm2->SelectAll(); EditSthm2->SelStart=0;
  //Расчет завершен

   return (0);
}
//---------------------------------------------------------------------------

int TFormCuts::CalcStFSz(TObject *Sender)
{
  int vi=0 ; char s[80]; String str;
  int mach; // станок
  double z,fz,vf; //исходные данные
  double tn,tvf,tfz; // рассчитываемые параметры : ..., мощность

  /*Подача на зуб*/
  str=EditStVf->Text;
  vf=atof(str.c_str());
  if (vf<=0.) {
    vf=0;
    s[0]='\0'; sprintf(s,"%.3lf",vf); EditStVf->Text=s;
    EditStVf->SetFocus(); EditStVf->SelectAll();
  }

  /*Подача на зуб*/
  str=Basefz->Text;
  fz=atof(str.c_str());
  if (fz<=0.) {
    fz=0;
    s[0]='\0'; sprintf(s,"%.5lf",fz);  Basefz->Text=s;
    Basefz->SetFocus(); Basefz->SelectAll();
  }

  /*Число зубьев*/
  str=BaseZ->Text;
  vi=atoi(str.c_str());
  if (vi<=0) {
    vi=0;
    s[0]='\0'; sprintf(s,"%d",vi); BaseZ->Text=s;
    BaseZ->SetFocus(); BaseZ->SelectAll();
    Application->MessageBox("Ошибка задания 'Числа зубьев' - z","Предупреждение...",MB_OK);
    return (-1);
  }
  z=(double)vi;

  /*Число оборотов*/
  str=EditStn->Text;
  tn=atof(str.c_str());
  if (tn<=0.) {
    tn=0.;
    s[0]='\0'; sprintf(s,"%.3lf",tn); EditStn->Text=s;
    EditStn->SetFocus(); EditStn->SelectAll();
  }

  // Расчет подачи на зуб
  if (tn<=0.) { Application->MessageBox("Расчет подачи на зуб \n n=0. \n Расчет прерван.","Предупреждение...",MB_OK); return (-1); }
  if (z<=0.) { Application->MessageBox("Расчет подачи на зуб \n z=0. \n Расчет прерван.","Предупреждение...",MB_OK); return (-1); }
  tfz=vf/(z*tn);
  s[0]='\0'; sprintf(s,"%.5lf",tfz);  EditStfz->Text=s;
  EditStfz->SetFocus(); EditStfz->SelectAll();

   return (0);
}
//---------------------------------------------------------------------------

int TFormCuts::CalcStP(TObject *Sender)
{
  char s[80];  String str;
  double D,B,t,K; //исходные данные
  double tSz,tn,tPz; // .....мощность
  double k4,x4,y4,z4,m2;
  double t1,t2,t3,t4,t5;

  /* Проверка на правильность ввода числовых значений
    StrToFloat(str) FloatToStr(vd) FloatToText(s,vd,fvExtended, ffFixed,8,8);*/
  /*диаметр*/
  str=BaseD->Text;
  D=atof(str.c_str());
  if (D<=0.) {
    D=30.;
    s[0]='\0'; sprintf(s,"%.3lf",D);BaseD->Text=s;
    BaseD->SetFocus();   BaseD->SelectAll();
    str="Ошибка задания 'диаметра инструмента' - D -> исправлено....";
    OutputMessage(str);
    Application->MessageBox(str.c_str(),"Предупреждение...",MB_OK);
  }

  /*Глубина реза*/
  str=BaseT->Text;
  t=atof(str.c_str());
  if (t<=0.) {
    t=D/4;
    s[0]='\0'; sprintf(s,"%.3lf",t);BaseT->Text=s;
    BaseT->SetFocus();  BaseT->SelectAll();
    str="Ошибка задания 'Глубина реза' - ae -> исправлено....";
    OutputMessage(str);
    Application->MessageBox(str.c_str(),"Предупреждение...",MB_OK);
  }

  /*fz*/
  str=Basefz->Text;
  tSz=atof(str.c_str());
  if (tSz<=0.) {
    Basefz->SetFocus();  Basefz->SelectAll();
    str="Ошибка задания 'Подача на зуб' - fz....";
    OutputMessage(str);
    Application->MessageBox(str.c_str(),"Предупреждение...",MB_OK);
    return(-1);
  }

  /*Число оборотов*/
  str=EditStn->Text;
  tn=atof(str.c_str());
  if (tn<=0.) {
    tn=0.;
    s[0]='\0'; sprintf(s,"%.3lf",tn); EditStn->Text=s;
    EditStn->SetFocus(); EditStn->SelectAll();
    str="Ошибка задания n<=0 (Расчет Pz)....";
    OutputMessage(str);
    Application->MessageBox(str.c_str(),"Предупреждение...",MB_OK);
    return (-1);
  }

  /**************************************************************************/
  /* Расчет */
  /*Sz*/
  if (tSz<=0.0001) {
    str="Ошибка вычисления-> Sz=fz=0.";
    OutputMessage(str);
    Application->MessageBox(str.c_str(),"Предупреждение..(Расчет Pz).",MB_OK);
    return (-1);
  }

  switch (RadioGroupPower->ItemIndex)
  {
  	case 0: k4=246.; x4=0.846; y4=0.546; z4=0.168; m2=0.118;
  	break;
  	default: k4=224.; x4=0.506; y4=0.344; z4=0.123; m2=0.112;
  	break;
  }

  /*Pz*/ t1=pow(t,x4);  t2=pow(tSz,y4);  t3=pow(D,z4);  t4=pow(tn,m2); tPz=k4*t1*t2*t3/t4;
  //установка значений
  s[0]='\0'; sprintf(s,"%.2lf",tPz); EditStP->Text=s;

  //Расчет завершен

   return (0);
}
//---------------------------------------------------------------------------

int TFormCuts::CalcStNctMz(TObject *Sender)
{
  char s[80]; String str;
  double D,ap,ae,tn,vc ; //исходные данные
  double kpd, kc; // материал
  double tvf,tP,tNp,tM; // рассчитываемые параметры : ..., мощность

  /*диаметр*/
  str=BaseD->Text;
  D=atof(str.c_str());
  if (D<=0.) {
    D=0.;
    s[0]='\0'; sprintf(s,"%.3lf",D); BaseD->Text=s;
    BaseD->SetFocus(); BaseD->SelectAll();
    OutputMessage("Ошибка задания 'диаметра инструмента' - D");
  }

  /*Ширина резания*/
  str=BaseB->Text;
  ap=atof(str.c_str());
  if (ap<=0.) {
    ap=0.;
    s[0]='\0'; sprintf(s,"%.5lf",ap); BaseB->Text=s;
    BaseB->SetFocus(); BaseB->SelectAll();
    OutputMessage("Ошибка задания 'Ширины реза' - ap     ");
  }

  /*Глубина реза*/
  str=BaseT->Text;
  ae=atof(str.c_str());
  if (ae<=0.) {
    ae=0;
    s[0]='\0'; sprintf(s,"%.5lf",ae); BaseT->Text=s;
    BaseT->SetFocus(); BaseT->SelectAll();
    OutputMessage("Ошибка задания 'Глубина реза' - ae<=0.   ");
  }

  /*скорость реза*/
  str=BaseVc->Text;
  vc=atof(str.c_str());
  if (vc<=0.) {
    vc=0;
    s[0]='\0'; sprintf(s,"%.5lf",vc); BaseVc->Text=s;
    BaseVc->SetFocus(); BaseVc->SelectAll();
    OutputMessage("Ошибка задания 'Скорость реза' - Vc<=0.    ");
  }

  /*Число оборотов*/
  str=EditStn->Text;
  tn=atof(str.c_str());
  if (tn<=0.) {
    tn=0.;
    s[0]='\0'; sprintf(s,"%.3lf",tn); EditStn->Text=s;
    EditStn->SetFocus(); EditStn->SelectAll();
    OutputMessage("Число оборотов шпинделя - n<=0.    ");
  }

  /*подачи резания*/
  str=EditStVf->Text;
  tvf=atof(str.c_str());
  if (tvf<=0.) {
    tvf=0;
    s[0]='\0'; sprintf(s,"%.5lf",tvf);  EditStVf->Text=s;
    EditStVf->SetFocus(); EditStVf->SelectAll();
    OutputMessage("Подача резания - vf<=0.    ");
  }

  /*силы реза*/
  str=EditStP->Text;
  tP=atof(str.c_str());
  if (tP<=0.) {
    tP=0;
    s[0]='\0'; sprintf(s,"%.5lf",tP);  EditStP->Text=s;
    EditStP->SetFocus(); EditStP->SelectAll();
    OutputMessage("Сила резания - P <=0.    ");
  }

  str=ComboBoxStkpd->Text; kpd=atof(str.c_str());

  tNp=0.;
  // Расчет мощности резания
  // 1.
  tNp=ae*ap*tvf*tP/(6.*10000000.*kpd);
  s[0]='\0'; sprintf(s,"%.5lf",tNp); EditStPn1->Text=s;

  // 2.
  tNp=tP*vc/(1020.*60.);
  s[0]='\0'; sprintf(s,"%.5lf",tNp); EditStPn2->Text=s;

  // Расчет момента резания
  tM=tP*D/(2.*100.);
  s[0]='\0'; sprintf(s,"%.5lf",tM); EditStM->Text=s;

  // 3.
  tNp=tM*(2.*3.1415926)*tn/60.;
  tNp/=1000.; // перевод из вт в квт
  s[0]='\0'; sprintf(s,"%.5lf",tNp); EditStPn3->Text=s;

  //Расчет завершен

   return (0);
}
//---------------------------------------------------------------------------

void TFormCuts::CalcStandart(TObject *Sender)
{
  int i;
  /**************************************************************************/
  /* Расчет */

  /*n V*/ /*i=CalcStnV(Sender); if (i<0) return ;*/
  /*************************************************************************/
  int vi=0 ; char s[80]; String str;
  int mach; // станок
  double D,z,vc,fz; //исходные данные
  double tn,tvf; //исходные данные

 /* Проверка на правильность ввода числовых значений
    StrToFloat(str) FloatToStr(vd) FloatToText(s,vd,fvExtended, ffFixed,8,8);*/
  /*диаметр*/
  str=BaseD->Text;
  D=atof(str.c_str());
  if (D<=0.) {
    D=0.;
    s[0]='\0'; sprintf(s,"%.3lf",D); BaseD->Text=s; BaseD->SetFocus(); BaseD->SelectAll();
    Application->MessageBox("Ошибка задания 'диаметра инструмента' - D","Предупреждение...",MB_OK);
    return ;
  }

  /*Число зубьев*/
  str=BaseZ->Text;
  vi=atoi(str.c_str());
  if (vi<=0) {
    vi=0;
    s[0]='\0'; sprintf(s,"%d",vi); BaseZ->Text=s; BaseZ->SetFocus(); BaseZ->SelectAll();
    Application->MessageBox("Ошибка задания 'Числа зубьев' - z","Предупреждение...",MB_OK);
    return ;
  }
  z=(double)vi;

  /*Скорость резания*/
  str=BaseVc->Text;
  vc=atof(str.c_str());
  if (vc<=0.) {
    vc=0;
    s[0]='\0'; sprintf(s,"%.3lf",vc); BaseVc->Text=s; BaseVc->SetFocus(); BaseVc->SelectAll();
    Application->MessageBox("Ошибка задания 'Скорости резания' - vc","Предупреждение...",MB_OK);
    return ;
  }

  /*Подача на зуб*/
  str=Basefz->Text;
  fz=atof(str.c_str());
  if (fz<=0.) {
    fz=0;
    s[0]='\0'; sprintf(s,"%.5lf",fz);
    Basefz->Text=s; Basefz->SetFocus(); Basefz->SelectAll();
    Application->MessageBox("Ошибка задания 'Подача на зуб' - fz","Предупреждение...",MB_OK);
    return ;
  }

  // Расчет оборотов
  if (D<=0.) { Application->MessageBox("Расчет оборотов \n D=0. \n Расчет прерван.","Предупреждение...",MB_OK); return ; }
  tn=vc*1000./(D*PI);
  s[0]='\0'; sprintf(s,"%.3lf",tn);  EditStn->Text=s;

  // Расчет скорости резания
  vc=(D*PI*tn)/1000.;
  s[0]='\0'; sprintf(s,"%.3lf",vc);  EditStVc->Text=s;
  /*************************************************************************/

  /*************************************************************************/
  /*Sz F*/ /* i=CalcStFSz(Sender);  if (i<0) return ; */
  /*************************************************************************/
  // Расчет подачи резания
  tvf=fz*z*tn;
  s[0]='\0'; sprintf(s,"%.2lf",tvf);  EditStVf->Text=s;

  // Расчет подачи на зуб
  if (tn<=0.) { Application->MessageBox("Расчет подачи на зуб \n n=0. \n Расчет прерван.","Предупреждение...",MB_OK); return ; }
  if (z<=0.) { Application->MessageBox("Расчет подачи на зуб \n z=0. \n Расчет прерван.","Предупреждение...",MB_OK); return ; }
  fz=tvf/(z*tn);
  s[0]='\0'; sprintf(s,"%.5lf",fz);  EditStfz->Text=s;
  /*************************************************************************/

  /*Q*/ i=CalcStQ(Sender);  if (i<0) return ;
  /*hm*/ i=CalcSthm(Sender);  if (i<0) return ;

  /*P*/ i=CalcStP(Sender);  if (i<0) return ;

  /*Nct Mz*/  i=CalcStNctMz(Sender);  if (i<0) return ;
  /**************************************************************************/
  //Расчет завершен
  return ;
}
//---------------------------------------------------------------------------

void __fastcall TFormCuts::BitBtn1Click(TObject *Sender)
{
    CalcStandart(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormCuts::BitBtnSt1Click(TObject *Sender)
{
   CalcStnV(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormCuts::BitBtnSt2Click(TObject *Sender)
{
   CalcStQ(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormCuts::BitBtnSt3Click(TObject *Sender)
{
     CalcSthm(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormCuts::BitBtnSt4Click(TObject *Sender)
{
   CalcStFSz(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormCuts::BitBtnSt5Click(TObject *Sender)
{
     CalcStNctMz(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormCuts::BitBtnSt6Click(TObject *Sender)
{
    CalcStP(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormCuts::Image9Click(TObject *Sender)
{
    BaseVc->Text=EditStVc->Text;
}
//---------------------------------------------------------------------------

void __fastcall TFormCuts::Image10Click(TObject *Sender)
{
   Basefz->Text=EditStfz->Text;
}
//---------------------------------------------------------------------------



