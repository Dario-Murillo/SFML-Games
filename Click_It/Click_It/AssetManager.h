#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Font.hpp"
#include <memory>
#include <map>


namespace Engine {
  class AssetManager {

  private:
    std::map<int, std::unique_ptr<sf::Texture>> textures;
    std::map<int, std::unique_ptr<sf::Font>> fonts;
  public:
    AssetManager();
    ~AssetManager();

    void addTexture(int id, std::string& path, bool isRepeated = false);
    void addFont(int id, const std::string& path);
    const sf::Texture& getTexture(int id) const;
    const sf::Font& getFont(int id) const;

  };
}



#endif // !ASSET_MANAGER_H
