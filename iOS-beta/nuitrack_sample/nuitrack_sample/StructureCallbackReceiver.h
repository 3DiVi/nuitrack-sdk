//
//  StructureCallbackReceiver.hpp
//  nuitrack_sample
//
//  Created by 3DiVi on 04.10.2019.
//  Copyright © 2019 3divi. All rights reserved.
//

#ifndef StructureCallbackReceiver_hpp
#define StructureCallbackReceiver_hpp

#import <Structure/Structure.h>
#include <stdio.h>

/*
 Here's an example to get callback data while Nuitrack gets it.
 You can apply the STSensorControllerDelegate to your ViewController to get data right there.
 */

@interface StructureCallbackReceiver : NSObject<STSensorControllerDelegate>

@end

#endif /* StructureCallbackReceiver_hpp */
