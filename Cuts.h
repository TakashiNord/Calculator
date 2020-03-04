//---------------------------------------------------------------------------

#ifndef CutsH
#define CutsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
#include "ElTrayInfo.hpp"
//---------------------------------------------------------------------------
class TFormCuts : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControlParam;
        TTabSheet *TabSheet1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *LabelB;
        TLabel *LabelT;
        TLabel *Label23;
        TLabel *LabelVc;
        TLabel *Labelfz;
        TComboBox *BaseD;
        TComboBox *BaseZ;
        TEdit *BaseB;
        TEdit *BaseT;
        TComboBox *ComboBoxStkpd;
        TEdit *BaseVc;
        TEdit *Basefz;
        TPageControl *PageControlMethods;
        TTabSheet *TabSheetStandard;
        TGroupBox *GroupBox3;
        TImage *Image6;
        TLabel *Label21;
        TEdit *EditStQ;
        TBitBtn *BitBtnSt2;
        TGroupBox *GroupBox4;
        TImage *Image7;
        TLabel *Label18;
        TImage *Image3;
        TLabel *Label19;
        TImage *Image10;
        TEdit *EditStVf;
        TEdit *EditStfz;
        TBitBtn *BitBtnSt4;
        TGroupBox *GroupBox5;
        TLabel *Label17;
        TLabel *Label85;
        TLabel *Label87;
        TBitBtn *BitBtnSt5;
        TEdit *EditStPn1;
        TEdit *EditStM;
        TGroupBox *GroupBox7;
        TImage *Image1;
        TLabel *Label4;
        TImage *Image2;
        TLabel *Label5;
        TImage *Image9;
        TEdit *EditStn;
        TEdit *EditStVc;
        TBitBtn *BitBtnSt1;
        TGroupBox *GroupBox6;
        TLabel *Label20;
        TImage *Imagehm;
        TBitBtn *BitBtnSt3;
        TEdit *EditSthm2;
        TBitBtn *BitBtn1;
        TLabel *Label3;
        TElTrayInfo *ElTrayInfo1;
        TImage *Image4;
        TImage *Image5;
        TImage *Image8;
        TBevel *Bevel2;
        TEdit *EditStPn3;
        TGroupBox *GroupBox1;
        TEdit *EditStP;
        TLabel *Label7;
        TImage *Image11;
        TEdit *EditStPn2;
        TLabel *Label6;
        TLabel *Label8;
        TBitBtn *BitBtnSt6;
        TImage *Image12;
        TRadioGroup *RadioGroupPower;
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtnSt1Click(TObject *Sender);
        void __fastcall BitBtnSt2Click(TObject *Sender);
        void __fastcall BitBtnSt3Click(TObject *Sender);
        void __fastcall BitBtnSt4Click(TObject *Sender);
        void __fastcall BitBtnSt5Click(TObject *Sender);
        void __fastcall Image9Click(TObject *Sender);
        void __fastcall Image10Click(TObject *Sender);
        void __fastcall BitBtnSt6Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormCuts(TComponent* Owner);
        
        void CalcStandart(TObject *Sender);
        int CalcStnV(TObject *Sender);
        int CalcStQ(TObject *Sender);
        int CalcSthm(TObject *Sender);
        int CalcStFSz(TObject *Sender);
        int CalcStP(TObject *Sender);
        int CalcStNctMz(TObject *Sender);
        void OutputMessage(AnsiString s);        
};
//---------------------------------------------------------------------------
extern PACKAGE TFormCuts *FormCuts;
//---------------------------------------------------------------------------
#endif
