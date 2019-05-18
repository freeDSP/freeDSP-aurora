#include "ccolormap.h"

CColormapJet::CColormapJet()
{
  // Jet-colormap erstellen
  int idx = 0;
  for(int i=0; i<128; i++)
  {
    m_clrFarbpalette[idx] = (QColor*)new QColor(0,0,128+i);
    idx++;
  }
  for(int i=0; i<256; i++)
  {
    m_clrFarbpalette[idx] = (QColor*)new QColor(0,i,255);
    idx++;
  }
  for(int i=0; i<256; i++)
  {
    m_clrFarbpalette[idx] = (QColor*)new QColor(i,255,255-i);
    idx++;
  }
  for(int i=0; i<256; i++)
  {
    m_clrFarbpalette[idx] = (QColor*)new QColor(255,255-i,0);
    idx++;
  }
  for(int i=0; i<128; i++)
  {
    m_clrFarbpalette[idx] = (QColor*)new QColor(255-i,0,0);
    idx++;
  }
  nMaxColors=1024;
}
