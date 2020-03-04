//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include "dxCalc.hpp"
#include "dxCntner.hpp"
#include <ExtCtrls.hpp>
#include "ElCaption.hpp"
#include "ElACtrls.hpp"
#include <ImgList.hpp>
#include "dxEditor.hpp"
#include "dxEdLib.hpp"
#include "dxExEdtr.hpp"
#include <Buttons.hpp>
#include <Graphics.hpp>
#include "ElBaseComp.hpp"
#include "ElTray.hpp"
#include <Menus.hpp>
#include "ElTrayInfo.hpp"
//---------------------------------------------------------------------------
class TfrmCalc : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar1;
        TElFormCaption *ElFormCaption1;
        TImageList *ImageListAngle;
        TPanel *Panel1;
        TPanel *Panel3;
        TTabControl *tbSphera;
        TImage *Image1;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TBevel *Bevel2;
        TImage *Image3;
        TImage *Image4;
        TdxCalcEdit *dxtheta;
        TdxCalcEdit *dxf;
        TElFlatEdit *dxR;
        TdxCalcEdit *dxi;
        TdxCalcEdit *dxj;
        TdxCalcEdit *dxk;
        TBitBtn *btCalcSf;
        TElFlatEdit *dxEd;
        TBitBtn *btEditTrans;
        TPanel *Panel4;
        TBevel *Bevel1;
        TdxCalculator *dxCalculator1;
        TdxCalcDisplay *dxResX;
        TElFlatEdit *dxResY;
        TPopupMenu *PopupMenuCalc;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TElTrayIcon *ElTrayIcon1;
        TImageList *ImageTool1;
        TElTrayInfo *ElTrayInfo1;
        TBitBtn *BitBtn1;
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TToolButton *ToolButton5;
        TToolButton *ToolButton6;
        TToolButton *ToolButton7;
        TToolButton *ToolButton8;
        TToolButton *ToolButton9;
        TToolButton *ToolButton10;
        void __fastcall ElFormCaption1Buttons0Click(TObject *Sender);
        void __fastcall ElFormCaption1Buttons1Click(TObject *Sender);
        void __fastcall btEditTransClick(TObject *Sender);
        void __fastcall dxEdChange(TObject *Sender);
        void __fastcall btCalcSfClick(TObject *Sender);
        void __fastcall N1Click(TObject *Sender);
        void __fastcall ElFormCaption1Buttons2Click(TObject *Sender);
        void __fastcall ElTrayIcon1Click(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ElTrayInfo1Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall ElFormCaption1Buttons3Click(TObject *Sender);
        void __fastcall ToolButton1Click(TObject *Sender);
        void __fastcall ToolButton2Click(TObject *Sender);
        void __fastcall ToolButton3Click(TObject *Sender);
        void __fastcall ToolButton4Click(TObject *Sender);
        void __fastcall ToolButton5Click(TObject *Sender);
        void __fastcall ToolButton6Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmCalc(TComponent* Owner);
        void __fastcall myButtonClick(int i, TObject *Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCalc *frmCalc;
//---------------------------------------------------------------------------
#endif
