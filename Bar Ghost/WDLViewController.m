//
//  WDLViewController.m
//  Bar Ghost
//
//  Created by William Lindmeier on 11/23/13.
//  Copyright (c) 2013 William Lindmeier. All rights reserved.
//

#import "WDLViewController.h"
#import "KeyMapping.h"
#import "WDLFSQManager.h"
#import "FSQVenue.h"
#import "WDLMessages.h"
#import "WDLAppDelegate.h"

@implementation WDLViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(appWillResignActive:)
                                                 name:UIApplicationWillResignActiveNotification
                                               object:nil];
}

- (void)appWillResignActive:(NSNotification *)notification
{
    [self updateMessageScreen];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [self updateMessageScreen];
}

const static int kNumMessageImages = 5;

- (void)updateMessageScreen
{
    // Randomize the message screenshot
    int imageNum = arc4random() % kNumMessageImages;
    NSString *imageName = [NSString stringWithFormat:@"message_%i", imageNum];
    self.imageViewMessage.image = [UIImage imageNamed:imageName];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

#pragma mark - IBActions

- (IBAction)buttonUpdatePressed:(id)sender
{
    self.labelStatus.text = @"Updating...";
    [self fsqSearchNearby];
}

#pragma mark - Foursquare

- (void)fsqSearchNearby
{
    WDLFSQManager *fsq = [WDLFSQManager sharedManager];
    if([fsq isAuthenticated])
    {
        [fsq searchNearbyVenuesWithParams:@{ @"intent" : @"checkin",
                                             @"radius" : [NSString stringWithFormat:@"%i",
                                                          kLocationSearchRadiusMeters],
                                             @"categoryId" : kNightlifeCategoryID }
                                  success:^(NSArray *results)
        {
            NSLog(@"Found %i nearby venues", (int)results.count);
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
                self.labelStatus.text = [NSString stringWithFormat:@"You are in a bar: %@\n",
                                         barName];
            }
            else
            {
                self.labelStatus.text = @"You are NOT in a bar.\n";
            }
        }
        error:^(NSDictionary *errorInfo)
        {
            NSLog(@"ERROR searching for venues: %@", errorInfo);
        }];
    }
    else
    {
        [(WDLAppDelegate *)[UIApplication sharedApplication].delegate fsqAuthenticate];
    }
}

@end
