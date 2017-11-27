//
//  VMMDeviceObserver.h
//  ObjectiveC_Extension
//
//  Created by Vitor Marques de Miranda on 09/08/17.
//  Copyright © 2017 Vitor Marques de Miranda. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <IOKit/hid/IOHIDManager.h>
#import <IOKit/hid/IOHIDKeys.h>
#include <IOKit/usb/IOUSBLib.h>

#define VMMDeviceObserverTypesKeyboard  @[@(kHIDUsage_GD_Keyboard), @(kHIDUsage_GD_Keypad)]

@protocol VMMDeviceObserverManagementDelegate
@property (nonatomic) IOHIDManagerRef hidManager;
@end

@protocol VMMDeviceObserverConnectionDelegate
-(void)observedConnectionOfDevice:(IOHIDDeviceRef)device;
-(void)observedRemovalOfDevice:(IOHIDDeviceRef)device;
@end

@protocol VMMDeviceObserverActionDelegate
-(void)observedEventWithName:(CFStringRef)name cookie:(IOHIDElementCookie)event usage:(uint32_t)usage value:(CFIndex)value device:(IOHIDDeviceRef)device;
@end


@interface VMMDeviceObserver : NSObject

+(instancetype)sharedObserver;
-(void)observeDevicesOfTypes:(NSArray<NSNumber*>*)types forDelegate:(id<VMMDeviceObserverManagementDelegate>)actionDelegate;
-(void)stopObservingForDelegate:(id<VMMDeviceObserverManagementDelegate>)actionDelegate;

@end
