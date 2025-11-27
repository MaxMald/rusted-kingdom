#include "TMR/tmrGridDataLayerXmlLoader.h"

#include <vector>
#include <string>
#include <sstream>
#include <cstdint>
#include <algorithm>

#include "TMR/tmrGridDataLayer.h"
#include "TMR/tmrData.h"
#include "TMR/tinyxml2.h"
#include "TMR/tmrPropertiesXmlLoader.h"

using namespace tinyxml2;

namespace tmr
{
  namespace gridDataLayerXmlLoader
  {
    std::vector<int32_t> parseCsvData(const char* csvText)
    {
      std::vector<int32_t> tiles;
      std::stringstream ss(csvText);
      std::string item;
      while (std::getline(ss, item, ',')) {
        // Remove leading/trailing whitespace
        item.erase(0, item.find_first_not_of(" \t\n\r"));
        item.erase(item.find_last_not_of(" \t\n\r") + 1);
        if (!item.empty()) {
          tiles.push_back(static_cast<int32_t>(std::stoi(item)));
        }
      }
      return tiles;
    }

    GridDataLayer* parseLayerFromXmlElement(XMLElement* layerElement)
    {
      if (layerElement == nullptr)
        return nullptr;

      int32_t id = layerElement->IntAttribute("id", 0);
      const char* name = layerElement->Attribute("name");
      int32_t width = layerElement->IntAttribute("width", 0);
      int32_t height = layerElement->IntAttribute("height", 0);
      Data* data = parseDataFromXmlElement(
        layerElement->FirstChildElement("data")
      );

      if (!data)
        return nullptr;

      Properties* properties = propertiesXmlLoader::loadProperties(
        layerElement->FirstChildElement("properties")
      );

      return new GridDataLayer(id, name, properties, width, height, data);
    }

    GridDataLayer** parseLayerArrayFromXmlElement(
      XMLElement* layersParentElement,
      size_t& outLayerCount
    )
    {
      if (!layersParentElement)
      {
        outLayerCount = 0;
        return nullptr;
      }

      outLayerCount = static_cast<size_t>(
        layersParentElement->ChildElementCount("layer")
      );

      if (outLayerCount == 0)
        return nullptr;

      GridDataLayer** layers = new GridDataLayer * [outLayerCount];

      size_t index = 0;
      XMLElement* layerIterator = layersParentElement->FirstChildElement("layer");
      while (layerIterator)
      {
        layers[index] = parseLayerFromXmlElement(layerIterator);
        layerIterator = layerIterator->NextSiblingElement("layer");
        index++;
      }

      return layers;
    }

    Data* parseDataFromXmlElement(XMLElement* dataElement)
    {
      if (dataElement == nullptr)
        return nullptr;

      const char* csvText = dataElement->GetText();
      if (!csvText)
        return nullptr;

      std::vector<int32_t> tiles = parseCsvData(csvText);
      if (tiles.empty())
        return nullptr;

      int32_t* dataArray = new int32_t[tiles.size()];
      std::copy(tiles.begin(), tiles.end(), dataArray);

      return new Data(dataArray, static_cast<size_t>(tiles.size()));
    }
  }
}