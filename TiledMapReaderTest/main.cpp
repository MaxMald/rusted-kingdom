#include <TMR/tmrTiledMapLoader.h>
#include <TMR/tmrTiledMap.h>

void main()
{
    tmr::TiledMap* map = tmr::tiledMapLoader::loadFromFile(
      "F:/Repositories/MaxMald/rusted-kingdom/assets/maps/level-5.tmx"
    );

    if (map)
    {
        // Successfully loaded the map
        // Perform operations with the map here
        // Clean up
        delete map;
    }

    return;
}