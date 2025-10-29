#include "TMR/tmrTiledMapReader.h"
#include "TMR/tmrJson.h"
#include "TMR/tmrTiledMapParser.h"

namespace tmr
{
  TileMapReader::TileMapReader() :
    m_parser(new TiledMapParser())
  {
  }

  TileMapReader::~TileMapReader()
  {
    delete m_parser;
  }

  TiledMap* TileMapReader::readFromFile(const char* filePath)
  {
    Json json = Json::loadFromFile(filePath);
    return m_parser->parseFromJson(json);
  }
}