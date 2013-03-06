#include "viewzi.h"

ViewZI::ViewZI(ZI *zi, const QRectF &rect)
    : QGraphicsRectItem(rect),
      m_zi(zi)
{

}
