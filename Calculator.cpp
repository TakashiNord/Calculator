//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Calculator.res");
USEFORM("Unit1.cpp", frmCalc);
USEFORM("Cuts.cpp", FormCuts);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TfrmCalc), &frmCalc);
                 Application->CreateForm(__classid(TFormCuts), &FormCuts);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
