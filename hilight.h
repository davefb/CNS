//
// hilight - various graphical hilighting tools
//
// Copyright (C) 1998 by Microsoft Corporation.  All rights reserved.
//


class HilightRectangle
{
public:

    virtual ~HilightRectangle() { }

    virtual void    SetLocation( const RECT & rc ) = 0;
    virtual void    SetVisible( BOOL bVisible ) = 0;

    virtual void    SetColor( COLORREF color ) = 0;
    virtual void    SetWidth( int width ) = 0;
    virtual void    SetGapWidth( int gap ) = 0;
};

HilightRectangle * CreateHilightRectangle();



class HilightText
{
public:

    virtual ~HilightText() { }

    virtual void    SetFont( HFONT hFont ) = 0;
    virtual void    SetLocation( RECT rc ) = 0;
    virtual void    SetVisible( BOOL bVisible ) = 0;
    virtual void    SetText( LPCTSTR pText ) = 0;

    virtual void    SetTextColor( COLORREF color ) = 0;
    virtual void    SetBkColor( COLORREF color ) = 0;
};

HilightText * CreateHilightText();




class HilightCaret
{
public:

    virtual ~HilightCaret() { }

    virtual void    SetLocation( const RECT & rc ) = 0;
    virtual void    SetVisible( BOOL bVisible ) = 0;

    virtual void    SetColor( COLORREF color ) = 0;

    enum {

        // Basic style bits...
        STYLE_TOP_LEFT      =   0x0001,
        STYLE_TOP_RIGHT     =   0x0002,
        STYLE_BOTTOM_LEFT   =   0x0004,
        STYLE_BOTTOM_RIGHT  =   0x0008,

        // Orientation (Horiz. not yet supported.)
        STYLE_VERT          =   0x0000,
        STYLE_HORIZ         =   0x0010,

        // Handy constants - combine with an orientation...
        STYLE_FULL          =   0x000F,
        STYLE_LEFTONLY      =   0x0005,
        STYLE_RIGHTONLY     =   0x000A,
        STYLE_TOPONLY       =   0x0003,
        STYLE_BOTTOMONLY    =   0x000C,
    };

    virtual void    SetStyle( DWORD dwStyle ) = 0;
};

HilightCaret * CreateHilightCaret();

