#ifndef CCOLORMAPJET_H
#define CCOLORMAPJET_H

#include <QtGui>

class CColormapJet
{
public:
  CColormapJet();
  QColor* getColor(int idx) { return m_clrFarbpalette[idx]; }
  int getMaxColor(void) { return nMaxColors; }
private:
  QColor* m_clrFarbpalette[1024];
  int nMaxColors;
};


#endif // CCOLORMAPJET_H
