//
//  WDLAppDelegate.m
//  Bar Ghost
//
//  Created by William Lindmeier on 11/23/13.
//  Copyright (c) 2013 William Lindmeier. All rights reserved.
//

#import "WDLAppDelegate.h"
#import "WDLFSQManager.h"
#import "WDLLocationManager.h"
#import "WDLMessages.h"

typedef void (^BackgroundCompletionHandler)(UIBackgroundFetchResult);

@implementation WDLAppDelegate
{
    BOOL _didCheckVenueOnLocationUpdate;
    BackgroundCompletionHandler _backgroundCompletionHandler;
    int _numLocationAttempts;
}

#pragma mark - Application State

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Tell the OS that we wan't background fetches
    [[UIApplication sharedApplication] setMinimumBackgroundFetchInterval:UIApplicationBackgroundFetchIntervalMinimum];
    return YES;
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    [[WDLLocationManager sharedManager] stopLocationUpdates];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    [WDLLocationManager sharedManager].delegate = self;
    [[WDLLocationManager sharedManager] startLocationUpdates];
}

// Handle the FSq authentication callback
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation
{
    return [[WDLFSQManager sharedManager].foursquare handleOpenURL:url];
}

#pragma mark - Background request

-(void)application:(UIApplication *)application performFetchWithCompletionHandler:(BackgroundCompletionHandler)completionHandler
{
    [[UIApplication sharedApplication] cancelAllLocalNotifications];

    _didCheckVenueOnLocationUpdate = NO;
    _numLocationAttempts = 0;
    _backgroundCompletionHandler = ^(UIBackgroundFetchResult fetchResult)
    {
        // Wrap the response in another block that kills the location updates.
        [[WDLLocationManager sharedManager] stopLocationUpdates];
        completionHandler(fetchResult);
    };
    
    // Begin loc updates
    [WDLLocationManager sharedManager].delegate = self;
    [[WDLLocationManager sharedManager] startLocationUpdates];
}

#pragma mark - Foursquare

- (void)fsqAuthenticate
{
    WDLFSQManager *fsq = [WDLFSQManager sharedManager];
    if(![fsq isAuthenticated])
    {
        [fsq authenticateWithSuccess:^{
            NSLog(@"SUCCCESS authenticating");
        } error:^(NSDictionary *errorInfo) {
            NSLog(@"ERROR authenticating: %@", errorInfo);
        }];
    }
    else
    {
        NSLog(@"User is already authenticated");
    }
}

#pragma mark - Location

- (void)locationManager:(WDLLocationManager *)locManager updatedWithAccuracy:(float)accuracy
{    
    if ([UIApplication sharedApplication].applicationState == UIApplicationStateActive)
    {
        WDLFSQManager *fsman = [WDLFSQManager sharedManager];
        // Ask the user to login to FSq if they aren't already
        if(![fsman isAuthenticated])
        {
            [self fsqAuthenticate];
        }
    }
    else
    {
        NSTimeInterval timeRemaining = [UIApplication sharedApplication].backgroundTimeRemaining;
        _numLocationAttempts++;
        if (accuracy < 100)
        {
            if (!_didCheckVenueOnLocationUpdate)
            {
                _didCheckVenueOnLocationUpdate = YES;
                
                WDLFSQManager *fsq = [WDLFSQManager sharedManager];
                if([fsq isAuthenticated])
                {
                    [fsq searchNearbyVenuesWithParams:@{ @"intent" : @"checkin",
                                                         @"radius" : [NSString stringWithFormat:@"%i",
                                                                      kLocationSearchRadiusMeters],
                                                         @"categoryId" : kNightlifeCategoryID }
                                              success:^(NSArray *results)
                     {
                         BOOL isBar = NO;
                         NSString *barName = nil;
                         for(FSQVenue *v in results)
                         {
                             if (IsFourSquareCategoryABar(v.primaryCategoryID) && v.isVerified)
                             {
                                 if (!isBar)
                                 {
                                     barName = v.name;
                                 }
                                 isBar = YES;
                                 NSLog(@"Venue is a bar: %@", v);
                             }
                         }
                         if (isBar)
                         {
                             // Yep. Send a local notification
                             NSString *note = GetRandomMessage();
                             [self scheduleLocalNotificationMessage:note
                                                           fireDate:[NSDate date]];
                         }
                         
                         if (_backgroundCompletionHandler)
                         {
                             // Always say new data.
                             // We want the app to maintain a high background status
                             _backgroundCompletionHandler(UIBackgroundFetchResultNewData);
                         }
                     }
                        error:^(NSDictionary *errorInfo)
                     {
                         // Send error alert
#if DEBUG
                         NSString *note = [NSString stringWithFormat:@"ERROR: %@", errorInfo[NSLocalizedDescriptionKey]];
                         [self scheduleLocalNotificationMessage:note fireDate:[NSDate date]];
#endif
                         if (_backgroundCompletionHandler)
                         {
                             _backgroundCompletionHandler(UIBackgroundFetchResultFailed);
                         }
                         //...
                     }];
                }
            }
        }
        else if (_numLocationAttempts >= 5 ||
                 [UIApplication sharedApplication].backgroundTimeRemaining < 3.0f)
        {
#if DEBUG
            NSString *note = [NSString stringWithFormat:@"ERROR: Out of time. Loc attemts: %i accuracy: %f time remaining: %f",
                              _numLocationAttempts, accuracy, timeRemaining];
            [self scheduleLocalNotificationMessage:note fireDate:[NSDate date]];
#endif
            if (_backgroundCompletionHandler)
            {
                _backgroundCompletionHandler(UIBackgroundFetchResultFailed);
            }
        }
    }
}

- (void)scheduleLocalNotificationMessage:(NSString *)notificationString fireDate:(NSDate *)date
{
    UILocalNotification *localNotification = [[UILocalNotification alloc] init];
    localNotification.fireDate = date;
    localNotification.alertBody = notificationString;
    localNotification.soundName = UILocalNotificationDefaultSoundName;
    // Badge the app w/ a random number
    localNotification.applicationIconBadgeNumber = arc4random() % 10;
    [[UIApplication sharedApplication] scheduleLocalNotification:localNotification];
}

@end
