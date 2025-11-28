#include "rkViewController.h"

namespace rk
{
  ViewController::ViewController(const String& name) :
    m_view(),
    m_name(name)
  {
  }

  ViewController::ViewController(const String& name, const View& view) :
    m_view(view),
    m_name(name)
  {
  }

  ViewController::~ViewController()
  {
  }

  const String& ViewController::getName() const
  {
    return m_name;
  }

  void ViewController::setView(const View& view)
  {
    m_view = view;
  }

  const View& ViewController::getView() const
  {
    return m_view;
  }
}