#include"Texture.h"

Texture::Texture(const char* fname, GLenum filterMode, bool mipmap) {
   config.filterMode = filterMode;
   config.mipmap = mipmap;
   GLuint ID = LoadTextureFromFile(fname, config.filterMode, config.mipmap);
   textureData.ID = ID;
}

void Texture::activate(GLuint bank) {
	glBindTexture(GL_TEXTURE_2D, bank);
}

void Texture::destroy() {
	DestroyTexture(textureData.ID);
}
