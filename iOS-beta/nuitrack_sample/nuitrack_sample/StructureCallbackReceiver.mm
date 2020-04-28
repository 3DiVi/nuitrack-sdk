//
//  StructureCallbackReceiver.cpp
//  nuitrack_sample
//
//  Created by 3DiVi on 04.10.2019.
//  Copyright © 2019 3divi. All rights reserved.
//

#include "StructureCallbackReceiver.h"
#include <nuitrack/capi/IOS_StructureCallbackProvider_CAPI.h>

@interface StructureCallbackReceiver()
{
    STSensorController *_sensorController;
}

-(id)init;
-(void)dispose;

@end

/*
 We can use STSensorController with Nuitrack, because it is singleton instance.
 The only difference is you should use "StructureCallbackProvider_addDelegate" instead of "sensorController.delegate".
 So you can get the same data that Nuitrack gets from Structure SDK.
 */


@implementation StructureCallbackReceiver

-(id)init
{
    self = [super init];

    _sensorController = [STSensorController sharedController];
    // instead of _sensorController.delegate = self;
    StructureCallbackProvider_addDelegate((uint64_t)self);
    auto result = [_sensorController initializeSensorConnection];

    if(result == STSensorControllerInitStatusSuccess)
        NSLog(@"[LOG][StructureCallbackReceiver] init STSensorControllerInitStatusSuccess \n");
    else if(result == STSensorControllerInitStatusOpenFailed)
        NSLog(@"[LOG][StructureCallbackReceiver] init STSensorControllerInitStatusOpenFailed \n");
    else if(result == STSensorControllerInitStatusSensorNotFound)
        NSLog(@"[LOG][StructureCallbackReceiver] init STSensorControllerInitStatusSensorNotFound \n");
    else if(result == STSensorControllerInitStatusAppInBackground)
        NSLog(@"[LOG][StructureCallbackReceiver] init STSensorControllerInitStatusAppInBackground \n");
    else if(result == STSensorControllerInitStatusSensorIsWakingUp)
        NSLog(@"[LOG][StructureCallbackReceiver] init STSensorControllerInitStatusSensorIsWakingUp \n");
    else if(result == STSensorControllerInitStatusAlreadyInitialized)
        NSLog(@"[LOG][StructureCallbackReceiver] init STSensorControllerInitStatusAlreadyInitialized \n");

    return self;
}

-(void)dispose
{
    _sensorController = nil;
    StructureCallbackProvider_addDelegate((uint64_t)self);
}

#pragma mark - Structure Callbacks

- (void)sensorDidConnect
{
    NSLog(@"[LOG][StructureCallbackReceiver] sensorDidConnect\n");
}

- (void)sensorDidDisconnect
{
    NSLog(@"[LOG][StructureCallbackReceiver] sensorDidDisconnect \n");
}

- (void)sensorDidStopStreaming:(STSensorControllerDidStopStreamingReason)reason
{
    NSLog(@"[LOG][StructureCallbackReceiver] sensorDidStopStreaming \n");
}

- (void)sensorDidLeaveLowPowerMode
{
    NSLog(@"[LOG][StructureCallbackReceiver] sensorDidLeaveLowPowerMode \n");
}

- (void)sensorBatteryNeedsCharging
{
    NSLog(@"[LOG][StructureCallbackReceiver] sensorBatteryNeedsCharging \n");
}

- (void)sensorDidOutputDepthFrame:(STDepthFrame *)depthFrame
{
    //NSLog(@"[LOG][StructureCallbackReceiver] sensorDidOutputDepthFrame \n");
}

- (void)sensorDidOutputSynchronizedDepthFrame:(STDepthFrame *)depthFrame colorFrame:(STColorFrame *)colorFrame
{
    //NSLog(@"LOG][StructureCallbackReceiver] sensorDidOutputSynchronizedDepthFrame \n");
}

@end
