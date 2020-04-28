//
//  ImageConversions.cpp
//  nuitrack_sample
//
//  Created by 3DiVi on 13.06.2019.
//  Copyright © 2019 3divi. All rights reserved.
//

#include "ImageConversions.h"

UIImage* ImageConversions::UIImageFromCVMatData(uint8_t* dt, int width, int height, int bits_per_component, int bits_per_pixel, int bytes_per_raw)
{
    NSData *data;
    CGColorSpaceRef colorSpace = nullptr;
    CGBitmapInfo bitmapInfo = 0;

    if(bits_per_pixel == bits_per_component && bits_per_component == 16)
    {
        data = [NSData dataWithBytes:dt length:bytes_per_raw*height];
        colorSpace = CGColorSpaceCreateDeviceGray();
        bitmapInfo = kCGImageAlphaNone | kCGImageByteOrder16Little;
    }
    else if (bits_per_pixel == bits_per_component * 3 && bytes_per_raw == bits_per_pixel*width/8 && bits_per_component == 8)
    {
        data = NSDataRGB2RGBA(dt, bytes_per_raw*height); // do BGR -> BRGA
        bits_per_pixel =  bits_per_component * 4;
        bytes_per_raw = bits_per_pixel * width / 8;
        colorSpace = CGColorSpaceCreateDeviceRGB();
        bitmapInfo =  kCGImageAlphaNoneSkipFirst | kCGImageByteOrder32Little; //BGRA -> ARGB -> RGB
    }
    else if (bits_per_pixel == bits_per_component * 4 && bits_per_component == 8)
    {
        data = [NSData dataWithBytes:dt length:bytes_per_raw*height];
        colorSpace = CGColorSpaceCreateDeviceRGB();
        bitmapInfo = kCGImageAlphaNoneSkipLast | kCGImageByteOrder32Little;
    }

    CGDataProviderRef provider = CGDataProviderCreateWithCFData((__bridge CFDataRef)data);

    // Creating CGImage from cv::Mat
    CGImageRef imageRef = CGImageCreate(
                                width,                      //width
                                height,                     //height
                                bits_per_component,         //bits per component
                                bits_per_pixel,             //bits per pixel
                                bytes_per_raw,              //bytesPerRow
                                colorSpace,                 //colorspace
                                bitmapInfo,                 // bitmap info
                                provider,                   //CGDataProviderRef
                                NULL,                       //decode
                                false,                      //should interpolate
                                kCGRenderingIntentDefault); //intent

    // Getting UIImage from CGImage
    UIImage *finalImage = [UIImage imageWithCGImage:imageRef];
    CGImageRelease(imageRef);
    CGDataProviderRelease(provider);
    CGColorSpaceRelease(colorSpace);

    return finalImage;
}

NSData* ImageConversions::UIImageToNSData(UIImage* image)
{
    CGColorSpaceRef colorSpace = CGImageGetColorSpace(image.CGImage);
    size_t numberOfComponents = CGColorSpaceGetNumberOfComponents(colorSpace);
    CGFloat cols = image.size.width;
    CGFloat rows = image.size.height;
    CGBitmapInfo bitmapInfo = kCGImageAlphaNoneSkipLast | kCGBitmapByteOrderDefault;
    int bytes_per_component = 1;

    if (numberOfComponents == 1)
    {
        bytes_per_component = 2;
        bitmapInfo = kCGImageAlphaNone | kCGImageByteOrder16Little;
    }

    int buffer_size = numberOfComponents*cols*rows* bytes_per_component;
    uint8_t* buffer = (uint8_t*)malloc(buffer_size);

    CGContextRef contextRef = CGBitmapContextCreate(
                                      buffer,                   // Pointer to backing data
                                      cols,                     // Width of bitmap
                                      rows,                     // Height of bitmap
                                      8*bytes_per_component,    // Bits per component
                                      cols*bytes_per_component, // Bytes per row
                                      colorSpace,               // Colorspace
                                      bitmapInfo);              // Bitmap info flags

    CGContextDrawImage(contextRef, CGRectMake(0, 0, cols, rows), image.CGImage);
    CGContextRelease(contextRef);
    NSData* result = [NSData dataWithBytes:buffer length:buffer_size];
    free(buffer);

    return result;
}

UIImage* ImageConversions::UIImageResize(UIImage* image, CGFloat new_width, CGFloat new_height)
{
    CGSize newSize;
    newSize.width = new_width;
    newSize.height = new_height;
    return UIImageResize(image, newSize);
}

UIImage* ImageConversions::UIImageResize(UIImage* image, CGSize newSize)
{
    //UIGraphicsBeginImageContext(newSize);
    // In next line, pass 0.0 to use the current device's pixel scaling factor (and thus account for Retina resolution).
    // Pass 1.0 to force exact pixel size.
    UIGraphicsBeginImageContextWithOptions(newSize, NO, 0.0);
    [image drawInRect:CGRectMake(0, 0, newSize.width, newSize.height)];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return newImage;
}

NSData* ImageConversions::NSDataRGB2RGBA(uint8_t* dt, int lenght)
{
    const int channels_number = 3;
    const int new_channels_number = 4;
    const int pixels_count = lenght/channels_number;
    uint8_t* updated_data = new uint8_t[pixels_count*new_channels_number];

    for (int i = 0; i < pixels_count; i++)
    {
        //copy all channels [R,G,B]
        for (int channel = 0; channel < channels_number; channel++)
            updated_data[i*new_channels_number + channel] = dt[i*channels_number + channel];
        //added A channel to the end;
        updated_data[i*new_channels_number + channels_number] = 255;
    }

    NSData* result = [NSData dataWithBytes:updated_data length:pixels_count*new_channels_number];
    delete updated_data;
    return result;
}
