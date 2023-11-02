inline
ColorU8_sRGB_Alpha ImageRGBA::get_pixel( Index aX, Index aY ) const
{
	assert( aX < mWidth && aY < mHeight ); // Leave this at the top of the function.
	
 	int pixelIndex = get_linear_index(aX, aY);

	float red = mData[pixelIndex];
	float green = mData[pixelIndex + 1];
	float blue = mData[pixelIndex + 2];
	float opacity = mData[pixelIndex + 3];

	return { red, green, blue, opacity };
}

inline
auto ImageRGBA::get_width() const noexcept -> Index
{
	return mWidth;
}
inline
auto ImageRGBA::get_height() const noexcept -> Index
{
	return mHeight;
}

inline
std::uint8_t* ImageRGBA::get_image_ptr() noexcept
{
	return mData;
}
inline
std::uint8_t const* ImageRGBA::get_image_ptr() const noexcept
{
	return mData;
}

inline
ImageRGBA::Index ImageRGBA::get_linear_index( Index aX, Index aY ) const noexcept
{
	// Find pixel location within 1D array
	Index pixelLocation = ((aY * mWidth) + aX) * 4;

	return pixelLocation; 
}
