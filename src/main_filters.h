//---------------------------------------------------------------------------

#ifndef main_filtersH
#define main_filtersH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include <ActnCtrls.hpp>
#include <ActnMan.hpp>
#include <ToolWin.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TEdit *m11;
        TEdit *m12;
        TEdit *m13;
        TEdit *m21;
        TEdit *m22;
        TEdit *m23;
        TEdit *m31;
        TEdit *m32;
        TEdit *m33;
        TEdit *div;
        TImage *Image2;
        TButton *filter;
        TButton *load;
        TOpenDialog *openDialog;
        TButton *Button1;
        TProgressBar *ProgressBar1;
        TButton *Button2;
        TButton *noise;
        TEdit *num;
        TMainMenu *MainMenu1;
        TMenuItem *Filters1;
        TMenuItem *Rectangle1;
        TMenuItem *Gauss1;
        TMenuItem *Sobel1;
        TMenuItem *Laplace1;
        TMenuItem *Sobel2;
        TMenuItem *Laplace2;
        TMenuItem *BasicHighPass1;

        void __fastcall loadClick(TObject *Sender);
        void __fastcall filterClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall noiseClick(TObject *Sender);
        void __fastcall Rectangle1Click(TObject *Sender);
        void __fastcall Gauss1Click(TObject *Sender);
        void __fastcall Sobel1Click(TObject *Sender);
        void __fastcall Laplace1Click(TObject *Sender);
        void __fastcall Sobel2Click(TObject *Sender);
        void __fastcall Laplace2Click(TObject *Sender);
        void __fastcall BasicHighPass1Click(TObject *Sender);

private:	// User declarations
        void multiply(float matrix[3][3], int x, int y);

public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
