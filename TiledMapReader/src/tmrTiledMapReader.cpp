#include "TMR/tmrTiledMapReader.h"
#include "TMR/tmrJson.h"
#include "TMR/tmrTiledMapParser.h"

namespace tmr
{
  TiledMapReader::TiledMapReader() :
    m_parser(new TiledMapParser())
  {
  }

  TiledMapReader::~TiledMapReader()
  {
    delete m_parser;
  }

  TiledMap* TiledMapReader::readFromFile(const char* filePath)
  {
    Json json = Json::loadFromFile(filePath);
    return m_parser->parseFromJson(json);
  }
}