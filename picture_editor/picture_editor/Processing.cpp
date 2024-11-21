#include "Processing.h"
#include "Image.h"
#include <math.h>
#include <algorithm>

namespace processing
{
	void converTogrey(Image& image)
	{
		for (auto i = 0; i < image.getSize(); ++i)
		{
			int average = 0;
			for (auto& channel : image[i].channels)
				average += channel;

			average /= 3;

			for (auto channelIdx = 0; channelIdx < 3; ++channelIdx)
				image[i].channels[channelIdx] = static_cast<uint8>(average);
		}
	}
	void convertToBinary(Image& image, const uint8& threshold)
	{
		for (auto i = 0; i < image.getSize(); ++i)
		{
			int average = 0;
			for (auto& channel : image[i].channels)
				channel = channel > threshold ? std::numeric_limits<uint8>::max() : 0;
		}
	}
	void fill(Image& image, const Rgb& fillColor)
	{
		for (auto i = 0; i < image.getSize(); ++i)
		{
			image[i] = fillColor;
		}

	}

	void zoom(Image& image, float zoomFactor, const Rgb& fillColor)
	{
		Point midPoint(image.getWidth() / 2, image.getHeight() / 2);
		zoom(image, zoomFactor, midPoint, fillColor);
	}

	void zoom(Image& image, float zoomFactor, const Point& origin, const Rgb& fillColor)
	{
		Image src = image;
		Image& dest = image;

		for (int row = 0; row < image.getHeight(); ++row)
		{
			for (int col = 0; col < image.getWidth(); ++col)
			{
				Point destinationCoord(col, row);
				Point sourceCoord = origin + (destinationCoord - origin) * zoomFactor;
				if (src.isInside(sourceCoord.y, sourceCoord.x))
					dest.getPixel(destinationCoord.y, destinationCoord.x) = src.getPixel(sourceCoord.y, sourceCoord.x);
				else
					dest.getPixel(destinationCoord.y, destinationCoord.x) = fillColor;
			}
		}
	}
	float degToRad(float angleInDegree)
	{
		return (angleInDegree * 3.14159f) / 180;
	}

	void rotation(Image& image, float angleInDegree, const Point& center, const Rgb& fillColor)
	{
		Image src = image;
		Image& dest = image;



		for (int row = 0; row < image.getHeight(); ++row)
		{
			for (int col = 0; col < image.getWidth(); ++col)
			{
				float cosa = cos(-degToRad(angleInDegree));
				float sina = sin(-degToRad(angleInDegree));

				Point Msrc(col, row);
				Msrc = Msrc - center;

				Point Mdest(Msrc.x * cosa - Msrc.y * sina,
					Msrc.x * sina + Msrc.y * cosa);

				Mdest = Mdest + center;


				Point destinationCoord(col, row);

				if (src.isInside(Mdest.y, Mdest.x))
					dest.getPixel(destinationCoord.y, destinationCoord.x) = src.getPixel(Mdest.y, Mdest.x);
				else
					dest.getPixel(destinationCoord.y, destinationCoord.x) = fillColor;
			}
		}

	}
	void rotation(Image& image, float angleInDegree, const Rgb& fillColor)
	{
		Point midPoint(image.getWidth() / 2, image.getHeight() / 2);
		rotation(image, angleInDegree, midPoint, fillColor);
	}

	void stretchHistogram(Image& image)
	{
		Rgb max;
		Rgb min;

		const auto absoluteMax = std::numeric_limits<uint8>::max();
		const auto absoluteMin = std::numeric_limits<uint8>::min();

		for (auto channelIdx = 0; channelIdx < Rgb::channels_count; ++channelIdx)
		{
			max.channels[channelIdx] = absoluteMin;
			min.channels[channelIdx] = absoluteMax;
		}

		for (auto i = 0; i < image.getSize(); ++i)
		{
			for (auto channelIdx = 0; channelIdx < Rgb::channels_count; ++channelIdx)
			{
				if (max.channels[channelIdx] < image[i].channels[channelIdx])
					max.channels[channelIdx] = image[i].channels[channelIdx];

				if (min.channels[channelIdx] > image[i].channels[channelIdx])
					min.channels[channelIdx] = image[i].channels[channelIdx];
			}
		}
		for (auto i = 0; i < image.getSize(); ++i)
		{
			for (auto channelIdx = 0; channelIdx < Rgb::channels_count; ++channelIdx)
			{
				const int numerator = absoluteMax * (image[i].channels[channelIdx] - min.channels[channelIdx]);
				image[i].channels[channelIdx] = static_cast<uint8>(numerator / (max.channels[channelIdx] - min.channels[channelIdx]));
			}
		}
	}
}

