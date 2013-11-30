//
//  WDLMessages.h
//  Məssagəs
//
//  Created by William Lindmeier on 11/30/13.
//  Copyright (c) 2013 William Lindmeier. All rights reserved.
//

#pragma once

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

const static int kLocationSearchRadiusMeters = 35;
static NSString const * kNightlifeCategoryID = @"4d4b7105d754a06376d81259";

const static NSArray *GetSampleMessages()
{
    const static NSArray *SampleMessages = nil;
    if (!SampleMessages)
    {
        SampleMessages = @[
                           @"Good luck getting that all cat food off in the shower dumbass",
                           @"Showed up to family party blacked out and in a turkey costume. I'd say thanksgiving was a success.",
                           @"Woke up backwards on a recliner",
                           @"Well my grandma put the turkey in the oven for 4 hours and didn't have the oven on.",
                           @"But wait then while giving his drive thru order he goes in mid sentence, \"Hey baby it's Travis remember me?\"",
                           @"It's the 30 sec rule.... the worst that could happen is I could die",
                           @"We hooked up in his car and afterwards he cried. I think I need to find a new hookup...",
                           @"Campus is too small for this to keep happening",
                           @"I have just found the cubicle of sustenance. And I will rejoice at all the families that have not found this magic. This vodka cubicle of magic.",
                           @"I woke up with my wool blanket soaking wet on the dorm room floor, and my sweatshirt hanging on the shower door down the hall. So basically my camp-out-in-the-bathroom idea didn't turn out as planned",
                           @"I just found a piece of squished oatmeal cream pie in my armpit. So very sad.",
                           @"Panda onesie. Pizza. Netflix. Wrapped up like a burrito. Screw you guys and your cute relationships THIS IS WHAT INFINITE HAPPINESS TASTES LIKE",
                           @"She ran from her surprise party screaming \"I'm not ready for an intervention.\" Yeah, the girl has a problem.",
                           @"Apparently mr clean magic erasers don't clean blood off the ceiling",
                           @"I woke up hugging a box of cheerios that had \"wonder woman\" written in sharpie on it. So much for a sober night.",
                           @"well i mean, we just followed them into an alien and astronaut party. there was tin foil everywhere",
                           @"He had really great hair, but he told me he's been in a psych ward three times. I mean I know I'm a psych major, but that's too much.",
                           @"He threw me over his shoulder and carried me outside, all the while drinking from the bottle of rum he was holding, while my ex watched. I'm winning the break-up.",
                           @"I couldn't think of the word \"bath\" so instead I told him I was marinating in soapy water"                           
                           ];
    }
    return SampleMessages;
}

static NSString *GetRandomMessage()
{
    const NSArray *messages = GetSampleMessages();
    return messages[arc4random() % messages.count];
}