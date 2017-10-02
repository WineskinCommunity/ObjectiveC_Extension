//
//  NSComputerInformation.h
//  ObjectiveC_Extension
//
//  Created by Vitor Marques de Miranda on 22/02/17.
//  Copyright © 2017 Vitor Marques de Miranda. All rights reserved.
//

#ifndef NSComputerInformation_Class
#define NSComputerInformation_Class

#define IS_SYSTEM_MAC_OS_10_7_OR_SUPERIOR   [NSComputerInformation isSystemMacOsEqualOrSuperiorTo:@"10.7"]   // Lion
#define IS_SYSTEM_MAC_OS_10_8_OR_SUPERIOR   [NSComputerInformation isSystemMacOsEqualOrSuperiorTo:@"10.8"]   // Mountain Lion
#define IS_SYSTEM_MAC_OS_10_9_OR_SUPERIOR   [NSComputerInformation isSystemMacOsEqualOrSuperiorTo:@"10.9"]   // Mavericks
#define IS_SYSTEM_MAC_OS_10_10_OR_SUPERIOR  [NSComputerInformation isSystemMacOsEqualOrSuperiorTo:@"10.10"]  // Yosemite
#define IS_SYSTEM_MAC_OS_10_11_OR_SUPERIOR  [NSComputerInformation isSystemMacOsEqualOrSuperiorTo:@"10.11"]  // El Capitan
#define IS_SYSTEM_MAC_OS_10_12_OR_SUPERIOR  [NSComputerInformation isSystemMacOsEqualOrSuperiorTo:@"10.12"]  // Sierra
#define IS_SYSTEM_MAC_OS_10_13_OR_SUPERIOR  [NSComputerInformation isSystemMacOsEqualOrSuperiorTo:@"10.13"]  // High Sierra

#define IS_WEBVIEW_LEGACY_COMPATIBLE_WITH_YOUTUBE_HTML5    IS_SYSTEM_MAC_OS_10_10_OR_SUPERIOR

#import <Foundation/Foundation.h>

@interface NSComputerInformation : NSObject

+(NSDictionary*)graphicCardDictionary;
+(NSString*)graphicCardModel;
+(NSString*)graphicCardType;

+(NSString*)graphicCardDeviceID;
+(NSString*)graphicCardVendorID;
+(NSString*)graphicCardMemorySize;

+(NSString*)macOsVersion;
+(BOOL)isSystemMacOsEqualOrSuperiorTo:(NSString*)version;

+(BOOL)isUserStaffGroupMember;

@end

#endif
