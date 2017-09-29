//
//  NSRunningApplication+Extension.m
//  ObjectiveC_Extension
//
//  Created by Vitor Marques de Miranda on 23/09/17.
//  Copyright © 2017 Vitor Marques de Miranda. All rights reserved.
//
//  References:
//  https://stackoverflow.com/questions/6160727/how-to-obtain-info-of-the-program-from-the-window-list-with-cgwindowlistcopywind
//  https://superuser.com/questions/902869/how-to-identify-which-process-is-running-which-window-in-mac-os-x
//

#import "NSRunningApplication+Extension.h"

@implementation NSRunningApplication (VMMRunningApplication)

+(NSArray<NSRunningApplication*>*)applicationsRunningFromInsideBundle:(NSString*)bundlePath
{
    NSMutableArray* list = [[NSMutableArray alloc] init];
    
    for (NSRunningApplication* runningApp in [[NSWorkspace sharedWorkspace] runningApplications])
    {
        NSString* binLocalPath = [[runningApp executableURL] path];
        
        if ([binLocalPath hasPrefix:bundlePath])
        {
            [list addObject:runningApp];
        }
    }
    
    return list;
}

-(NSArray<NSDictionary*>*)visibleWindows
{
    NSMutableArray* appWindows = [[NSMutableArray alloc] init];
    NSMutableArray* windows = (NSMutableArray *)CFBridgingRelease(CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly | kCGWindowListExcludeDesktopElements, kCGNullWindowID));
    
    for (NSDictionary *window in windows)
    {
        int ownerPid = [window[@"kCGWindowOwnerPID"] intValue];
        if (ownerPid == self.processIdentifier)
        {
            [appWindows addObject:window];
        }
    }
    
    return appWindows;
}

-(BOOL)isVisible
{
    return self.visibleWindows.count > 0;
}

-(NSArray*)windowsSizes
{
    return [self.visibleWindows valueForKey:@"kCGWindowBounds"];
}
-(BOOL)hasWindowWithSize:(NSSize)size
{
    for (NSDictionary *window in self.visibleWindows)
    {
        NSDictionary* windowBounds = window[@"kCGWindowBounds"];
        CGFloat windowHeight = [windowBounds[@"Height"] doubleValue];
        CGFloat windowWidth  = [windowBounds[@"Width"]  doubleValue];
        if (ABS(size.width - windowWidth) < 0.1 && ABS(size.height - windowHeight) < 0.1)
        {
            return true;
        }
    }
    
    return false;
}

-(void)bringWindowsToFront
{
    [self activateWithOptions:(NSApplicationActivateAllWindows | NSApplicationActivateIgnoringOtherApps)];
}

@end
