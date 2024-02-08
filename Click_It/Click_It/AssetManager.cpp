#include "AssetManager.h"

Engine::AssetManager::AssetManager() {}

Engine::AssetManager::~AssetManager() {}

void Engine::AssetManager::addTexture(int id, std::string& path, bool isRepeated) {
  auto texture = std::make_unique<sf::Texture>();
  if (texture->loadFromFile(path)) {
    texture->setRepeated(isRepeated);
    this->textures[id] = std::move(texture);
  }
}

void Engine::AssetManager::addFont(int id, const std::string& path) {
  auto font = std::make_unique<sf::Font>();
  if (font->loadFromFile(path)) {
    this->fonts[id] = std::move(font);
  }
}

const sf::Texture& Engine::AssetManager::getTexture(int id) const {
  // The id points to a place in the map to a unique pointer so we have to "get" the texture/font
  // Ademas se debe redeferenciar este puntero para obtener el objeto
  return *(this->textures.at(id).get());
  // TODO: Insertar una instrucción "return" aquí
}

const sf::Font& Engine::AssetManager::getFont(int id) const {
  return *(this->fonts.at(id).get());
  // TODO: Insertar una instrucción "return" aquí
}
