#include "rkTiledImage.h"
#include <TMR/tmrImage.h>

namespace rk
{
  TiledImage::TiledImage() :
    m_height(0),
    m_width(0),
    m_sourcePath()
  {
  }

  TiledImage::TiledImage(const tmr::Image* tmrImage) :
    m_height(0),
    m_width(0),
    m_sourcePath()
  {
    if (tmrImage)
    {
      m_height = tmrImage->getHeight();
      m_width = tmrImage->getWidth();
      m_sourcePath = tmrImage->getSource();
    }
  }

  TiledImage::~TiledImage()
  {
  }
}