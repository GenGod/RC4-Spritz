object Form1: TForm1
  Left = 440
  Top = 165
  BorderStyle = bsSingle
  Caption = 'RC4 - Spritz'
  ClientHeight = 416
  ClientWidth = 548
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Segoe UI Light'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  Visible = True
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 25
  object Label1: TLabel
    Left = 177
    Top = 23
    Width = 230
    Height = 25
    Caption = 'Open file to encrypt/decrypt'
  end
  object Label2: TLabel
    Left = 24
    Top = 71
    Width = 173
    Height = 25
    Caption = 'Enter you private key:'
  end
  object OpenButton: TButton
    Left = 24
    Top = 16
    Width = 129
    Height = 41
    Caption = 'Open File'
    TabOrder = 0
    OnClick = OpenButtonClick
  end
  object KeyEdit: TEdit
    Left = 24
    Top = 112
    Width = 489
    Height = 33
    TabOrder = 1
  end
  object TestButton: TButton
    Left = 216
    Top = 159
    Width = 75
    Height = 44
    Caption = 'Start'
    TabOrder = 2
    OnClick = TestButtonClick
  end
  object LogMemo: TMemo
    Left = 2
    Top = 223
    Width = 538
    Height = 185
    Lines.Strings = (
      'LogMemo')
    ScrollBars = ssBoth
    TabOrder = 3
  end
  object OpenDialog1: TOpenDialog
  end
end
