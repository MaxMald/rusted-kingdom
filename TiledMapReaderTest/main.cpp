#include <TMR/tmrTiledMapReader.h>
#include <TMR/tmrTileSetsEmbedder.h>

void main()
{
    tmr::TiledMapReader reader;
    tmr::TiledMap* map = reader.readFromFile(
      "F:/Repositories/MaxMald/rusted-kingdom/assets/maps/level-4.json"
    );

    tmr::tileSetsEmbedder::embedTileSets(
      *map,
      "F:/Repositories/MaxMald/rusted-kingdom/assets/maps/"
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