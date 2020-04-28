//
//  ImageConversions.hpp
//  nuitrack_sample
//
//  Created by 3DiVi on 13.06.2019.
//  Copyright © 2019 3divi. All rights reserved.
//

#ifndef ImageConversions_hpp
#define ImageConversions_hpp

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

class ImageConversions
{
public:
    static UIImage* UIImageFromCVMatData(uint8_t* dt, int width, int height, int bits_per_component, int bits_per_pixel, int bytes_per_raw);
    static UIImage* UIImageResize(UIImage* image, CGFloat new_width, CGFloat new_height);
    static UIImage* UIImageResize(UIImage* image, CGSize newSize);
    static NSData* UIImageToNSData(UIImage* image);

private:
    static NSData* NSDataRGB2RGBA(uint8_t* dt, int lenght);
};

#endif /* ImageConversions_hpp */
