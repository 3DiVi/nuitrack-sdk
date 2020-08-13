//
//  ViewController.mm
//  nuitrack_sample
//
//  Created by 3DiVi on 04.06.2019.
//  Copyright © 2019 3divi. All rights reserved.
//

#import "ViewController.h"
#import <AVFoundation/AVFoundation.h>

#include "ImageConversions.h"
#include "NuitrackModules.h"
#include "NuitrackDrawing.h"
#include "StructureCallbackReceiver.h"
#include <thread>

using namespace sample;

using namespace tdv::nuitrack;
using namespace tdv::nuitrack::device;

@interface ViewController ()
{
    StructureCallbackReceiver *_calbackReceiver;
    std::thread _background;
    bool _workInProccess;
    bool _performColor;
}

- (IBAction)mainButtonClick:(id)sender;
- (void)logMessage:(NSString *)format, ...;
- (void)update;
- (void)tryToActivateDevice;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    _workInProccess = false;
    _performColor = false;

    int version = Nuitrack::getVersion();
    self.labelVersionNumber.text = [NSString stringWithFormat:@"v%d.%d.%d",
                                        version / 10000,
                                        (version / 100) % 100,
                                        version % 100];

    [AVCaptureDevice
        requestAccessForMediaType:AVMediaTypeVideo
        completionHandler:^(BOOL granted) {
                printf("CameraAccess: %s \n", (granted?"true":"false"));
            }
    ];

    _calbackReceiver = [[StructureCallbackReceiver alloc] init];
}

- (void) tryToActivateDevice
{
    // only one connected device is possible for iOS
    printf("Try to select device\n");

    auto devices = Nuitrack::getDeviceList();

    if (!devices.empty())
    {
        printf("Devices:\n");
        for(int i = 0; i < devices.size(); i++)
           printf("    [%d] %s (%s): %s\n",
                i,
                devices[i]->getInfo(DeviceInfoType::SERIAL_NUMBER).c_str(),
                devices[i]->getInfo(DeviceInfoType::DEVICE_NAME).c_str(),
                (devices[i]->getActivationStatus() ? "ACTIVATED" : "NO-LICENSE"));

        int dev_index = 0; //choose first one (should be only one there)

        std::vector<std::string> title({"Depth", "Color"});
        for(int vm = 0; vm < StreamType::Count; vm++)
        {
            auto modes = devices[dev_index]->getAvailableVideoModes(static_cast<StreamType>(vm));
            printf(" %s\n", (modes.empty() ? "No " + title[vm] + " video modes." : title[vm] + " video modes:").c_str());

            if (modes.empty())
                continue;

            for(int i = 0; i < modes.size(); i++)
                printf("    [%d] %d x %d @ %d\n",
                    i,
                    modes[i].width,
                    modes[i].height,
                    modes[i].fps);

            int vm_index = 0; //set first video mode

            if(vm_index != -1)
                devices[dev_index]->setVideoMode(
                                                 static_cast<StreamType>(vm),
                                                 modes[vm_index]
                                                 );
        }

        //Nuitrack::setConfigValue("Network.ProxyUrl", "192.168.1.2:1234");
        std::string activationKey = "";

        if(activationKey.empty())
            printf("ActivationKey is empty\n");
        else
        {
            printf("Try to activate sensor\n");
            try {
                devices[dev_index]->activate(activationKey);
                bool activationStatus = devices[dev_index]->getActivationStatus();
                printf("Activation status: %s\n", (activationStatus ? "ACTIVATED" : "NO-LICENSE"));
            } catch(Exception &e) {
                printf("Activation Error: %s\n", e.what());
            }
        }

        Nuitrack::setDevice(devices[dev_index]);
    }
    else{
        printf("No device found\n");
    }
}

- (void) touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    if(_workInProccess)
        _performColor = !_performColor;
}

- (void)logMessage:(NSString *)format, ...
{
    va_list args;
    va_start(args, format);
    NSLogv(format, args);
    NSString *text = [[NSString alloc] initWithFormat:format arguments:args];
    dispatch_async(dispatch_get_main_queue(), [self, text](){
        self.labelError.text = text;
    });
    va_end(args);
}

- (IBAction)mainButtonClick:(id)sender
{
    if(_workInProccess)
        return;

    if(_background.joinable())
        _background.join();

    self.button.hidden = true;
    self.mainView.backgroundColor = UIColor.blackColor;
    self.labelError.text = @"";
    self.labelVersionTitle.hidden = true;
    self.labelVersionNumber.hidden = true;
    self.imageView.hidden = false;

    _workInProccess = true;
    _background = std::thread([self](){
        [self update];
        self->_workInProccess = false;
        dispatch_async(dispatch_get_main_queue(), [self](){
                self.imageView.hidden = true;
                self.labelVersionTitle.hidden = false;
                self.labelVersionNumber.hidden = false;
                self.button.hidden = false;
                self.mainView.backgroundColor = UIColor.whiteColor;
        });
    });
}

- (void)update
{
    try {
        // inintialize nuitrack
        Nuitrack::init();

        // activate device
        [self tryToActivateDevice];

        // inintialize nuitrack modules
        NuitrackModules::instance()->init();

        // start all modules
        Nuitrack::run();

        // main update cycle
        while(true)
        {
            try{
                NuitrackModules::instance()->waitForUpdate(SKELETON_TRACKER);
            } catch (const LicenseNotAcquiredException& e) {
                [self logMessage:@"Error: LicenseNotAcquiredException (ExceptionType: %d): %s", e.type(), e.what()];
                break;
            }

            if(!_performColor && !NuitrackModules::instance()->getDepthFrame())
                continue;

            if(_performColor && !NuitrackModules::instance()->getColorFrame())
                continue;

            // update images in main thread
            dispatch_sync(dispatch_get_main_queue(), [self](){
                UIImage* img;

                // get frame
                if(_performColor)
                {
                    auto color_frame = NuitrackModules::instance()->getColorFrame();
                    img = ImageConversions::UIImageFromCVMatData((uint8_t*)color_frame->getData(), color_frame->getCols(), color_frame->getRows(), 8, 8*3, color_frame->getCols()*3);
                }
                else{
                    auto depth_frame = NuitrackModules::instance()->getDepthFrame();
                    img = ImageConversions::UIImageFromCVMatData((uint8_t*)depth_frame->getData(), depth_frame->getCols(), depth_frame->getRows(), 8*2, 8*2, depth_frame->getCols()*2);
                }

                // drawing things on frame
                auto ctx = NuitrackDrawing::StartDrawing(img);
                if(!_performColor)
                {
                    NuitrackDrawing::IncreaseAllPixelsValue(ctx, 3);
                    NuitrackDrawing::DyeUsers(ctx);
                }
                NuitrackDrawing::DrawSkeletons(ctx);
                NuitrackDrawing::DrawHandState(ctx);
                //NuitrackDrawing::DrawNuitrackInfo(ctx); //actually only log right now
                self.imageView.image =  NuitrackDrawing::StopDrawing(ctx);
            });
        }

        // finish nuitrack
        Nuitrack::release();

    } catch (const std::exception& e) {
        [self logMessage:@"Error: %s", e.what()];
    }
}

@end
