//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <string.h>
#include <stdlib.h>

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
TBitmap *tmp;
TRect copy_r;
//---------------------------------------------------------------------------

bool  Line = false;
int xo, yo;
int x_copy=0, y_copy=0;
bool Lastic = false;
bool copy = true;
int x=40,y=150;
int w=300,h=280;
float dx=w/30,dy=h/28;

__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
		  tmp=new TBitmap();
           tmp->Width=Image1->Width;
tmp->Height= Image1->Height;
          Button1Click(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
  tmp->Assign(Image1->Picture);
  Image1->Canvas->MoveTo(X,Y);

  Memo1->Lines->Add("MoveTo "+IntToStr(X)+" "+  IntToStr(Y));
  xo=X;
  yo=Y;
  if(sbKarandash->Down)
	Line=true;
  if(sbLastic->Down)
	Lastic=true;
  if(sbPipetka->Down)
   {
	   if(Button==mbLeft)
		{
		   Shape1->Brush->Color=Image1->Canvas->Pixels[X][Y];
			Memo1->Lines->Add("Pen "+IntToStr(Image1->Canvas->Pixels[X][Y]));
		}
	   if(Button==mbRight)
		 {
		  Shape2->Brush->Color=Image1->Canvas->Pixels[X][Y];
		   Memo1->Lines->Add("Brush "+IntToStr(Image1->Canvas->Pixels[X][Y]));
		 }
   }

  if(sbZalivka->Down)
   {
	  if(!CheckBox1->Checked)
		Image1->Canvas->FloodFill(X,Y,Image1->Canvas->Pen->Color,fsBorder);
	  else
		Image1->Canvas->FloodFill(X,Y,Image1->Canvas->Pixels[X][Y],fsSurface);
   }

  if(sbText->Down)
   {
	   Panel2->Visible=true;
	   Edit1->Top=Y+Image1->Top;
	   Edit1->Left=X+Image1->Left;
	   Edit1->Text="";
	   Edit1->Visible=true;
   }



}
//---------------------------------------------------------------------------
void __fastcall TForm2::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{   if(sbKarandash->Down&&Line)
	{
	 Image1->Canvas->LineTo(X,Y);
	   Memo1->Lines->Add("LineTo "+IntToStr(Image1->Canvas->Pixels[X][Y]));
	}
	if(sbLastic->Down&&Lastic)
	{
	 Image1->Canvas->Pen->Color=clWhite;
	 Image1->Canvas->Brush->Color=clWhite;
	 Image1->Canvas->Ellipse(X,Y,X+15,Y+15);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{    if(sbLine->Down)
		{
			 Image1->Canvas->LineTo(X,Y);
			 Memo1->Lines->Add("LineTo "+IntToStr(X)+" "+  IntToStr(Y));
        }



	 if(sbElipse->Down)
	   Image1->Canvas->Ellipse(xo,yo,X,Y);
	 if(sbLastic->Down)
	   {
		 Image1->Canvas->Pen->Color=Shape1->Brush->Color;
		Image1->Canvas->Brush->Color=Shape2->Brush->Color;
	   }
	 if(sbVidilenie->Down&&copy)
	  {
		  Image1->Canvas->DrawFocusRect(Rect(xo,yo,X,Y));
		  copy_r.init(xo,yo,X,Y);
	  }

	  if(sbVidilenie->Down)
	   {
		   x_copy=X;
		   y_copy=Y;
	   }
	 if(sbKvadrat->Down)
	   Image1->Canvas->Rectangle(xo,yo,X,Y);
	 if(sbTreugolnik->Down)
		{

	   TPoint points[4];
points[0] = Point(xo,yo);
points[1] = Point(xo+50,yo+50);
points[2] = Point(X,Y);
points[3] = Point(xo,yo);

Image1->Canvas->Polyline(points, 3);
		}
	 Lastic = false;
	 Line = false;

}
//---------------------------------------------------------------------------
void __fastcall TForm2::ColorBox1Change(TObject *Sender)
{
Image1->Canvas->Pen->Color=ColorBox1->Selected;
Shape1->Brush->Color=ColorBox1->Selected;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::SpinEdit1Change(TObject *Sender)
{
Image1->Canvas->Pen->Width=SpinEdit1->Value;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ComboBox1Change(TObject *Sender)
{
//Image1->Canvas->Pen->Style=ComboBox1->ItemIndex;
switch( ComboBox1->ItemIndex)
{
  case 0: Image1->Canvas->Pen->Style=psSolid;break;
  case 1:  Image1->Canvas->Pen->Style=psDash;break;
  case 2:  Image1->Canvas->Pen->Style=psDot;break;
  case 3:  Image1->Canvas->Pen->Style=psDashDot;break;
  case 4:  Image1->Canvas->Pen->Style=psDashDotDot;break;
  case 5:  Image1->Canvas->Pen->Style=psClear;break;
}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Shape2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
       if(ColorDialog1->Execute())
  Shape2->Brush->Color=ColorDialog1->Color;
  Image1->Canvas->Brush->Color=Shape2->Brush->Color;


}
//---------------------------------------------------------------------------
void __fastcall TForm2::ComboBox2Change(TObject *Sender)
{
	 switch( ComboBox2->ItemIndex)
{
	case 0: Image1->Canvas->Brush->Style=bsSolid;break;
	case 1: Image1->Canvas->Brush->Style=bsClear;break;
	case 2: Image1->Canvas->Brush->Style=bsHorizontal;break;
	case 3: Image1->Canvas->Brush->Style=bsVertical;break;
	case 4: Image1->Canvas->Brush->Style=bsFDiagonal;break;
	case 5: Image1->Canvas->Brush->Style=bsBDiagonal;break;
	case 6: Image1->Canvas->Brush->Style=bsCross;break;
	case 7: Image1->Canvas->Brush->Style=bsDiagCross;break;

}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Save1Click(TObject *Sender)
{
 if(SaveDialog1->Execute())
  Image1->Picture->SaveToFile(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Save2Click(TObject *Sender)
{
 if(OpenDialog1->Execute())
  Image1->Picture->LoadFromFile(OpenDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::CheckBox1Click(TObject *Sender)
{
 if( CheckBox1->Checked)
   CheckBox1->Caption="fsSurface";
 else
   CheckBox1->Caption="fsBorder";
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	 Image1->Canvas->Pen->Color=clWhite;
	 Image1->Canvas->Brush->Color=clWhite;
	 Image1->Canvas->FillRect(Rect(0,0,Image1->Width,Image1->Height));
	 Image1->Canvas->Pen->Color=Shape1->Brush->Color;
	 Image1->Canvas->Brush->Color=Shape2->Brush->Color;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Edit1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
 if(Key==13)
  {
	  Panel2->Visible=false;
	  Image1->Canvas->Brush->Style=bsClear;
	  Image1->Canvas->Font=Label1->Font;
	  Image1->Canvas->TextOutW(	xo,yo,Edit1->Text);
	  Image1->Canvas->Brush->Color=Shape2->Brush->Color;
	  Edit1->Visible=false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender)
{
  if(FontDialog1->Execute())
    Label1->Font=FontDialog1->Font;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::sbTextClick(TObject *Sender)
{
  Panel2->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Edit3Click(TObject *Sender)
{
Image1->Canvas->Draw(0,0,tmp);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Copy2Click(TObject *Sender)
{ if(!copy)
  Image1->Canvas->CopyRect(Rect( x_copy,y_copy,x_copy+copy_r.Width(), y_copy+copy_r.Height()), Image1->Canvas, copy_r);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Copy1Click(TObject *Sender)
{
	copy=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button3Click(TObject *Sender)
{
Image1->Canvas->Brush->Color=clGray;
Image1->Canvas->Pen->Color=clBlack;
Image1->Canvas->Rectangle(x+4*dx,y+7*dy,x+20*dx,y+28*dy);
Image1->Canvas->MoveTo(x+4*dx,y+7.1*dy);
Image1->Canvas->LineTo(x+2*dx,y+5*dy);
Image1->Canvas->MoveTo(x+20*dx,y+7*dy);
Image1->Canvas->LineTo(x+21.5*dx,y+5*dy);
Image1->Canvas->Rectangle(x+2*dx,y+5.2*dy,x+21.5*dx,y+3*dy);
Image1->Canvas->Brush->Color=(TColor)(clGray);
Image1->Canvas->FloodFill(x+8*dx,y+6*dy,clBlack,fsBorder);
Image1->Canvas->Rectangle(x+2*dx,y+3*dy,x+4.8*dx,y+dy);
Image1->Canvas->Rectangle(x+8*dx,y+3*dy,x+10.8*dx,y+dy);
Image1->Canvas->Rectangle(x+14*dx,y+3*dy,x+16.8*dx,y+dy);
Image1->Canvas->Rectangle(x+20*dx,y+3*dy,x+21.5*dx,y+dy);
Image1->Canvas->Brush->Color=(TColor)(18,245,50);
Image1->Canvas->Rectangle(x+18*dx,y+3*dy,x+18.4*dx,y-3*dy);
Image1->Canvas->MoveTo(x+18.4*dx,y-3*dy);
Image1->Canvas->LineTo(x+20.8*dx,y-dy);
Image1->Canvas->MoveTo(x+20.8*dx,y-dy);
Image1->Canvas->LineTo(x+18*dx,y+dy);
Image1->Canvas->Brush->Color=clRed;
Image1->Canvas->FloodFill(x+20.2*dx,y-dy,clBlack,fsBorder);
Image1->Canvas->Brush->Color=(TColor)(clGray);
Image1->Canvas->Brush->Color=(TColor)(18,100,35);
Image1->Canvas->RoundRect(x+12*dx,y+13*dy,x+16*dx,y+15*dy,10,10);
Image1->Canvas->RoundRect(x+6*dx,y+25*dy,x+9.6*dx,y+23*dy,10,10);
Image1->Canvas->RoundRect(x+8*dx,y+9*dy,x+10.8*dx,y+10.5*dy,10,10);
Image1->Canvas->RoundRect(x+14*dx,y+16*dy,x+16.2*dx,y+17.5*dy,10,10);
Image1->Canvas->Brush->Color=(TColor)(100,1000,70);
Image1->Canvas->RoundRect(x+12*dx,y+20*dy,x+19*dx,y+28*dy,30,30);
Image1->Canvas->MoveTo(x+13.5*dx,y+20*dy);
Image1->Canvas->LineTo(x+13.5*dx,y+28*dy);
Image1->Canvas->MoveTo(x+15.5*dx,y+20*dy);
Image1->Canvas->LineTo(x+15.5*dx,y+28*dy);
Image1->Canvas->MoveTo(x+17.5*dx,y+20*dy);
Image1->Canvas->LineTo(x+17.5*dx,y+28*dy);
Panel3->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button10Click(TObject *Sender)
{
Panel3->Visible=false;
Image1->Canvas->Pen->Color=Shape1->Brush->Color;
	 Image1->Canvas->Brush->Color=Shape2->Brush->Color;

}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button4Click(TObject *Sender)
{
y-=5;
Button1Click(Sender);
Button3Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button5Click(TObject *Sender)
{
x+=5;
Button1Click(Sender);
Button3Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button6Click(TObject *Sender)
{
x-=5;
Button1Click(Sender);
Button3Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button7Click(TObject *Sender)
{
 y+=5;
Button1Click(Sender);
Button3Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button8Click(TObject *Sender)
{
dx*=1.2;
dy*=1.2;
Button1Click(Sender);
Button3Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button9Click(TObject *Sender)
{
dx/=1.2;
dy/=1.2;
Button1Click(Sender);
Button3Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Savevector2Click(TObject *Sender)
{
if(OpenDialog1->Execute())
   {
	  Memo1->Lines->LoadFromFile(OpenDialog1->FileName);
	  for(int i = 0; i <  Memo1->Lines->Count; i++)
		{
			AnsiString s  =Memo1->Lines->Strings[i];
			 AnsiString s1= s.SubString(i,s.Pos(' ')-1);
			 s.Delete(1,s.Pos(' '));
			 if(s1=="MoveTo")
			  {
				  int x =StrToInt(s.SubString(i,s.Pos(' ')-1));
				  s.Delete(1,s.Pos(' '));
				  int y= StrToInt(s);
				  Image1->Canvas->MoveTo(x,y);
			  }
			 if(s1=="LineTo")
			  {
				  int x =StrToInt(s.SubString(i,s.Pos(' ')-1));
				  s.Delete(1,s.Pos(' '));
				  int y= StrToInt(s);
				  Image1->Canvas->LineTo(x,y);
              }
        }
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Savevector1Click(TObject *Sender)
{
	 if(SaveDialog1->Execute())
   {
	  Memo1->Lines->SaveToFile(SaveDialog1->FileName);
   }
}
//---------------------------------------------------------------------------
