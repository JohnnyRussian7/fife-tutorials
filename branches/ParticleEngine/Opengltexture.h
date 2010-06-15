
class Image;

class OpenglTexture
{
public:
	OpenglTexture(Image* image);
	~OpenglTexture();

	unsigned int GetTextureId() const;
	void Upload();

private:
	unsigned int m_textureId;
	Image* m_image;
};