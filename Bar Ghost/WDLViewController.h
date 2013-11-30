//
//  WDLViewController.h
//  Bar Ghost
//
//  Created by William Lindmeier on 11/23/13.
//  Copyright (c) 2013 William Lindmeier. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface WDLViewController : UIViewController

@property (nonatomic, strong) IBOutlet UILabel *labelStatus;
@property (nonatomic, strong) IBOutlet UIImageView *imageViewMessage;

- (IBAction)buttonUpdatePressed:(id)sender;

@end
