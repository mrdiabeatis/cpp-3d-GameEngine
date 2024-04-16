#include "TextureLoader.h"

GLuint LoadTextureFromFile(const char* fname, GLenum filterMode, bool mipmap) {
	// load texture into a byte array
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(fname, &widthImg, &heightImg, &numColCh, 0);

	// create texture object and load image to the active texture slot
	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	if (mipmap)
		glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	
	return texture;
}

void DestroyTexture(GLuint ID) {
	glDeleteTextures(1, &ID);
}