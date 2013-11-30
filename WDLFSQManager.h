//
//  WDLFSQManager.h
//  BlimpCam
//
//  Created by William Lindmeier on 3/17/13.
//  Copyright (c) 2013 William Lindmeier. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BZFoursquare.h"
#import "FSQVenue.h"

static BOOL IsFourSquareCategoryABar(NSString *categoryID)
{
    static NSArray *barCategories = nil;
    if (!barCategories)
    {
        barCategories = @[@"4d4b7105d754a06376d81259",
                          @"4bf58dd8d48988d116941735",
                          @"4bf58dd8d48988d117941735",
                          @"50327c8591d4c4b30a586d5d",
                          @"4bf58dd8d48988d11e941735",
                          @"4bf58dd8d48988d118941735",
                          @"4bf58dd8d48988d1d8941735",
                          @"4bf58dd8d48988d119941735",
                          @"4bf58dd8d48988d1d5941735",
                          @"4bf58dd8d48988d120941735",
                          @"4bf58dd8d48988d121941735",
                          @"4bf58dd8d48988d11f941735",
                          @"4bf58dd8d48988d11a941735",
                          @"4bf58dd8d48988d11b941735",
                          @"4bf58dd8d48988d11c941735",
                          @"4bf58dd8d48988d1d4941735",
                          @"4bf58dd8d48988d11d941735",
                          @"4bf58dd8d48988d1d6941735",
                          @"4bf58dd8d48988d122941735",
                          @"4bf58dd8d48988d123941735"];
    }
    return [barCategories indexOfObject:categoryID] != NSNotFound;
}

typedef void(^FSQSuccessBlock)(void);
typedef void(^FSQErrorBlock)(NSDictionary *errorInfo);

@interface WDLFSQManager : NSObject <
BZFoursquareRequestDelegate,
BZFoursquareSessionDelegate
>

@property(nonatomic,readwrite,strong) BZFoursquare *foursquare;

- (void)searchNearbyVenuesWithParams:(NSDictionary *)searchParams
                             success:(void (^)(NSArray * results))successCallback
                               error:(FSQErrorBlock)errorCallback;

- (void)checkinToVenue:(FSQVenue *)venue
               success:(void (^)(NSDictionary *response))successCallback
                 error:(FSQErrorBlock)errorCallback;

- (void)uploadPhoto:(UIImage *)photo
            toVenue:(FSQVenue *)venue
            success:(void (^)(NSDictionary *response))successCallback
              error:(FSQErrorBlock)errorCallback;

- (BOOL)isAuthenticated;

- (void)authenticateWithSuccess:(void (^)(void))successCallback
                          error:(FSQErrorBlock)errorCallback;

- (void)logout;

+ (WDLFSQManager *)sharedManager;

@end
