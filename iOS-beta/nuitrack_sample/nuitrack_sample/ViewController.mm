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

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    _workInProccess = false;
    _performColor = false;

    NSString* version = [[[NSBundle bundleWithIdentifier:@"com.tdv.nuitrack"] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    self.labelVersionNumber.text = [NSString stringWithFormat:@"v%@", version];

    [AVCaptureDevice
        requestAccessForMediaType:AVMediaTypeVideo
        completionHandler:^(BOOL granted) {
                printf("CameraAccess: %s \n", (granted?"true":"false"));
            }
    ];

    _calbackReceiver = [[StructureCallbackReceiver alloc] init];
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

        // change/set config
        //Nuitrack::setConfigValue("ActivationKey", ""); // if you dont have any, then get free trial for tests
        //Nuitrack::setConfigValue("Network.ProxyUrl", ""); // if you use proxy, it might be necessary for activation

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
