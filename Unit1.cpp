//---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define mStr 128

#define PI (2.0 * asin(1.0))  /*value PI*/
#define RAD2DEG (90.0 / asin(1.0))    /*multiplier to convert radians to degrees*/
#define DEG2RAD (asin(1.0) / 90.0)    /*multiplier to convert degrees to radians*/
#define system_tolerance  0.000001

/***********************************************************************/
int  EQ_is_equal (double s, double t)
{
  if (fabs(s-t)<= system_tolerance)  { return(1); } else { return(0) ; }
}
/***********************************************************************/
int  EQ_is_ge (double s, double t)
{
  if (s > (t - system_tolerance)) { return(1); } else { return(0) ; }
}
/***********************************************************************/
int  EQ_is_zero (double s)
{
  if (fabs(s)<= system_tolerance)  { return(1); } else { return(0) ; }
}

//#=============================================================
double CheckConst ( double angle, double constvar  )
//#=============================================================
{
  /*while {$angle < 0.0} {set angle [expr $angle+360.0]}
   while {$angle >= 360.0} {set angle [expr $angle-360.0]}
   */
   while (angle < -constvar) { angle+=constvar ; }
   while (angle >= constvar) { angle-=constvar ; }
   return (angle) ;
}

/***********************************************************************/
/*
Methods:
0 - ABC->ijk
..- ijk->ABC
*/
// Перевод: Сферические координаты -> (Theta,Phi)<->(i,j,k)
int ABCijk_sphera(int Methods, double ang[12], double ijk[3])
{
  double ang_rad[12];
  double i,j,k ;
  double phi , theta , r ;
  double rad ;
  double A1 ;

  rad=3.1415926/180.;
  i=0.; j=0. ; k=1.;

 // проверка и установка значений.
  switch (Methods)
  {
   case 0 :  // A,B,C->i,j,k
       ang_rad[0]=ang[0]*rad; //A
       ang_rad[1]=ang[1]*rad; //B
       ang_rad[2]=ang[2]*rad; //C
       ang_rad[3]=0.*rad; //A2
       ang_rad[4]=0.*rad; //B2
       ang_rad[5]=0.*rad; //C2
       ang_rad[6]=0.*rad; //A3
       ang_rad[7]=0.*rad; //B3
       ang_rad[8]=0.*rad; //C3
       ang_rad[9]=0.*rad; //A4
       ang_rad[10]=0.*rad; //B4
       ang_rad[11]=0.*rad; //C4

       i=sin(ang_rad[0])*cos(ang_rad[1]);
       j=sin(ang_rad[0])*sin(ang_rad[1]);
       k=cos(ang_rad[0]);

   break ;
   default :
       i=ijk[0]; j=ijk[1]; k=ijk[2];
       r=sqrt(i*i+j*j+k*k);
       if (EQ_is_zero(r)) { i=0.; j=0.; k=1.;  }
       r=sqrt(i*i+j*j+k*k);
       if (!EQ_is_equal(r,1.000)) { i/= r; j/= r; k/= r; }
  }

  // перерасчет углов - исходя из i,j,k и ограничений
  phi=0.;
  theta=0.;
  r=sqrt(i*i+j*j+k*k);
  A1=sqrt(i*i+j*j);
  if (!EQ_is_zero(A1)) {
    A1=i/A1;
    if (EQ_is_ge(j,0.)) phi=acos(A1); else { phi=2.*PI-acos(A1); }
  }
  theta=acos(k);

  ang[0]=theta/rad; //theta
  ang[1]=phi/rad; //phi
  ang[2]=r; //r

  ang[0]=CheckConst(ang[0],180.);
  ang[1]=CheckConst(ang[1],360.);

  ijk[0]=i; ijk[1]=j; ijk[2]=k;

  return (0);
}


#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Cuts.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dxCalc"
#pragma link "dxCntner"
#pragma link "ElCaption"
#pragma link "ElACtrls"
#pragma link "dxEditor"
#pragma link "dxEdLib"
#pragma link "dxExEdtr"
#pragma link "ElTray"
#pragma link "ElTrayInfo"
#pragma link "ElBaseComp"
#pragma resource "*.dfm"
TfrmCalc *frmCalc;

AnsiString DeciText(AnsiString s)
{
  AnsiString pstr ;
  int index;
  char str[80];

  str[0]='\0';  strcpy(str,s.c_str());  strcat(str,"\0");
  index=0;
  while (str[index]!='\0')
  {
    if (str[index]==',') str[index]='.';
    index++;
  }
  pstr= AnsiString(str);
  return(pstr);
}

//---------------------------------------------------------------------------
__fastcall TfrmCalc::TfrmCalc(TComponent* Owner)
        : TForm(Owner)
{
  //TrayIcon1->Visible = True ;
  //TrayIcon1->Hide = True;
  AnsiString S=" (c) " ;
  //StatusBar1->SimpleText=S
  StatusBar1->Panels->Items[1]->Text =S;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalc::ElFormCaption1Buttons0Click(TObject *Sender)
{
 MessageBeep(0);
 Application->ProcessMessages();
 Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalc::ElFormCaption1Buttons1Click(TObject *Sender)
{
     frmCalc->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalc::ElFormCaption1Buttons2Click(TObject *Sender)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    // Start the child process.
    if( !CreateProcess( NULL, // No module name (use command line).
        "calc.exe", // Command line.
        NULL,             // Process handle not inheritable.
        NULL,             // Thread handle not inheritable.
        FALSE,            // Set handle inheritance to FALSE.
        0,                // No creation flags.
        NULL,             // Use parent's environment block.
        NULL,             // Use parent's starting directory.
        &si,              // Pointer to STARTUPINFO structure.
        &pi )             // Pointer to PROCESS_INFORMATION structure.
    )
    {
        //Application->MessageBox("CreateProcess failed; calc.exe  ","> ошибка ...", MB_OK);
    	ElTrayInfo1->Message=AnsiString("CreateProcess failed; calc.exe  ");
        ElTrayInfo1->Show();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalc::ElFormCaption1Buttons3Click(TObject *Sender)
{
  ShellAbout (NULL,"TechCalculator"," ____________________",NULL);

/*    LPCTSTR szApp,	// title bar and first line text
    LPCTSTR szOtherStuff,	// other dialog text
    HICON hIcon 	// icon to display
*/

}
//---------------------------------------------------------------------------

void __fastcall TfrmCalc::N1Click(TObject *Sender)
{
    //TrayIcon1->Restore();
    frmCalc->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalc::btEditTransClick(TObject *Sender)
{
  switch (tbSphera->TabIndex) {
   case 0:
   dxEd->Text=dxtheta->Text+ " " + dxf->Text + " " ;
   break;
   default :
   dxEd->Text=dxi->Text+ " " + dxj->Text + " " + dxk->Text;
   break;
  }
  dxEd->Update();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalc::dxEdChange(TObject *Sender)
{
  String estr , pstr ;
  int index;
  double i,j,k;
  double r ;
  char s[80];

  i=0.; j=0. ; k=1. ;
  estr=""; estr=dxEd->Text;
  s[0]='\0';  strcpy(s,estr.c_str());  strcat(s,"\0");
  index=0;
  while (s[index]!='\0')
  {
    if (s[index]==';' || s[index]=='(' || s[index]==')' || s[index]=='|') s[index]=' ';
    if (s[index]==',') s[index]='.';
    index++;
  }

  index=sscanf(s,"%lf %lf %lf",&i,&j,&k);

  switch (tbSphera->TabIndex)
  {
   case 0 :  // A,B,C->i,j,k

     s[0]='\0'; sprintf(s,"%.4lf",i); dxtheta->Text=s; dxtheta->Update();
     s[0]='\0'; sprintf(s,"%.4lf",j); dxf->Text=s; dxf->Update();
     s[0]='\0'; sprintf(s,"%.4lf",k); dxR->Text=s; dxR->Update();

   break ;
   default : // i,j,k->A,B,C

     r=sqrt(i*i+j*j+k*k);
     if (EQ_is_zero(r)) {
     	 i=0.; j=0.; k=1.;
      }
      r=sqrt(i*i+j*j+k*k);
      if (!EQ_is_equal(r,1.000)) {
           //s[0]='\0'; sprintf(s,"Проверка ввода: !! вектор={i,j,k} - не нормирован->нормируем... koef=%.3lf ",1./r);
           //ElTrayInfo1->Message=AnsiString(s);
           //ElTrayInfo1->Show();
           i/= r; j/= r; k/= r;
      }

     s[0]='\0'; sprintf(s,"%.6lf",i); dxi->Text=s; dxi->Update();
     s[0]='\0'; sprintf(s,"%.6lf",j); dxj->Text=s; dxj->Update();
     s[0]='\0'; sprintf(s,"%.6lf",k); dxk->Text=s; dxk->Update();

  }

  btCalcSfClick(NULL);
  return ;
}
//---------------------------------------------------------------------------


void __fastcall TfrmCalc::btCalcSfClick(TObject *Sender)
{

  AnsiString str;
  double ang[12], ijk[3], r ;
  long int i ;
  char mes[255] ;

  for(i=0;i<12;i++) ang[i]=0.;
  for(i=0;i<3;i++) ijk[i]=0.; ijk[2]=1.;

 // проверка и установка значений.
  switch (tbSphera->TabIndex)
  {
   case 0 :  // A,B,C->i,j,k

       dxtheta->Text=DeciText(dxtheta->Text);
       str=dxtheta->Text;  ang[0]=atof(str.c_str());
       dxf->Text=DeciText(dxf->Text);
       str=dxf->Text; ang[1]=atof(str.c_str());
       dxR->Text=DeciText(dxR->Text);
       str=dxR->Text; ang[2]=atof(str.c_str());

       mes[0]='\0'; sprintf(mes,"%.4lf",ang[0]);   dxtheta->Text=mes;
       mes[0]='\0'; sprintf(mes,"%.4lf",ang[1]);   dxf->Text=mes;
       mes[0]='\0'; sprintf(mes,"%.4lf",ang[2]);   dxR->Text=mes;

       if (ang[0]<0. || ang[0]>180.) { ; }
       if (ang[1]<0. || ang[1]>360.) { ; }

       ang[0]=CheckConst(ang[0],180.);
       ang[1]=CheckConst(ang[1],360.);

       i=ABCijk_sphera(0,ang,ijk);

   break ;
   default :

       dxi->Text=DeciText(dxi->Text);
       str=dxi->Text; ijk[0]=atof(str.c_str());
       dxj->Text=DeciText(dxj->Text);
       str=dxj->Text; ijk[1]=atof(str.c_str());
       dxk->Text=DeciText(dxk->Text);
       str=dxk->Text; ijk[2]=atof(str.c_str());

       r=sqrt(ijk[0]*ijk[0]+ijk[1]*ijk[1]+ijk[2]*ijk[2]);
       if (EQ_is_zero(r)) {
       	 ijk[0]=0.; ijk[1]=0.; ijk[2]=1.;
         r=1.;
       }
       if (!EQ_is_equal(r,1.000)) {
            ijk[0]/= r; ijk[1]/= r; ijk[2]/= r;
       }

       mes[0]='\0'; sprintf(mes,"%.6lf",ijk[0]);  dxi->Text=mes;
       mes[0]='\0'; sprintf(mes,"%.6lf",ijk[1]);  dxj->Text=mes;
       mes[0]='\0'; sprintf(mes,"%.6lf",ijk[2]);  dxk->Text=mes;

       i=ABCijk_sphera(1,ang,ijk);

       if (ang[0]<0. || ang[0]>180.) { ; }
       if (ang[1]<0. || ang[1]>360.) { ; }

  }

// вывод
  mes[0]='\0'; sprintf(mes,"%.4lf",ang[0]);   dxtheta->Text=mes;
  mes[0]='\0'; sprintf(mes,"%.4lf",ang[1]);   dxf->Text=mes;
  mes[0]='\0'; sprintf(mes,"%.4lf",ang[2]);   dxR->Text=mes;
  mes[0]='\0'; sprintf(mes,"%.6lf",ijk[0]);  dxi->Text=mes;
  mes[0]='\0'; sprintf(mes,"%.6lf",ijk[1]);  dxj->Text=mes;
  mes[0]='\0'; sprintf(mes,"%.6lf",ijk[2]);  dxk->Text=mes;

}
//---------------------------------------------------------------------------

void __fastcall TfrmCalc::ElTrayIcon1Click(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   N1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalc::ElTrayInfo1Click(TObject *Sender)
{
  ElTrayInfo1->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalc::BitBtn1Click(TObject *Sender)
{
  AnsiString s;
  s="В Unigraphics -не общепринятое- обозначение углов !\n";
  s+="      Угол Phi (UG) -> это угол Theta=0°..+180°\n";
  s+="      Угол Theta (UG) -> это угол Phi=0°..+360°";
  s+="\n\nПроверка ввода:\n";
  s+="      если вектор={i,j,k} - не нормирован->нормируем.\n";
  s+="      koef=1/|{i,j,k}|\n";
  ElTrayInfo1->Message=s;
  ElTrayInfo1->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalc::myButtonClick(int i, TObject *Sender)
{
  char *pathExec[5]={
  	"explorer.exe",
  	"winword.exe",
        "notepad.exe",
  	"C:\\Program Files\\UltraEdit\\uedit32.exe",
  	"mspaint.exe"
  };

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

 switch (i) {

  case 0: case 1: case 2: case 3: case 4:
    // Start the child process.
    if( !CreateProcess( NULL, // No module name (use command line).
        pathExec[i], // Command line.
        NULL,             // Process handle not inheritable.
        NULL,             // Thread handle not inheritable.
        FALSE,            // Set handle inheritance to FALSE.
        0,                // No creation flags.
        NULL,             // Use parent's environment block.
        NULL,             // Use parent's starting directory.
        &si,              // Pointer to STARTUPINFO structure.
        &pi )             // Pointer to PROCESS_INFORMATION structure.
    ) {
    	//Application->MessageBox("CreateProcess failed;","> ошибка ...", MB_OK);
    	ElTrayInfo1->Message=AnsiString("CreateProcess failed;");
        ElTrayInfo1->Show();
     }
  break;

  default : break ;
 }

}
//---------------------------------------------------------------------------


void __fastcall TfrmCalc::ToolButton1Click(TObject *Sender)
{
   myButtonClick(0,Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalc::ToolButton2Click(TObject *Sender)
{
 try
  {
   //myButtonClick(1,Sender);
   ShellExecute( NULL, "open" ,"winword",NULL,NULL,SW_SHOW );
  } catch (Exception &exception){ ;/*Application->ShowException(&exception);*/}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalc::ToolButton3Click(TObject *Sender)
{
 try
  {
    myButtonClick(2,Sender);
    //ShellExecute( NULL, "open" ,"notepad",NULL,NULL,SW_SHOW );
  } catch (Exception &exception){ ;/*Application->ShowException(&exception);*/}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalc::ToolButton4Click(TObject *Sender)
{
 try
  {
    //myButtonClick(3,Sender);
    ShellExecute( NULL, "open" ,"uedit32",NULL,NULL,SW_SHOW );
  } catch (Exception &exception){ ;/*Application->ShowException(&exception);*/}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalc::ToolButton5Click(TObject *Sender)
{
   myButtonClick(4,Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalc::ToolButton6Click(TObject *Sender)
{
  FormCuts->Show();
}
//---------------------------------------------------------------------------

