//
//  WDLAppDelegate.h
//  Bar Ghost
//
//  Created by William Lindmeier on 11/23/13.
//  Copyright (c) 2013 William Lindmeier. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "WDLLocationManager.h"

@interface WDLAppDelegate : UIResponder <UIApplicationDelegate, WDLLocationManagerDelegate>

- (void)fsqAuthenticate;

@property (strong, nonatomic) UIWindow *window;

@end
