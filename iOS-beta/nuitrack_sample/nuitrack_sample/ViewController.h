//
//  ViewController.h
//  nuitrack_sample
//
//  Created by 3DiVi on 04.07.2019.
//  Copyright © 2019 3divi. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

@property (strong, nonatomic) IBOutlet UIView *mainView;
@property (weak, nonatomic) IBOutlet UILabel *labelError;
@property (weak, nonatomic) IBOutlet UILabel *labelVersionTitle;
@property (weak, nonatomic) IBOutlet UILabel *labelVersionNumber;
@property (weak, nonatomic) IBOutlet UIImageView *imageView;
@property (weak, nonatomic) IBOutlet UIButton *button;

@end
