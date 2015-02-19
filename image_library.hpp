#ifndef IMAGE_LIBRARY_HPP
#define IMAGE_LIBRARY_HPP



class ImageLibrary {
private:
	static std::unordered_map<std::string,Texture> mymap;
public:
	void init();
	Texture* getImage();
};

#endif