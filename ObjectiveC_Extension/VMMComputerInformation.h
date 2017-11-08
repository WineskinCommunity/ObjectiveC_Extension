//
//  VMMComputerInformation.h
//  ObjectiveC_Extension
//
//  Created by Vitor Marques de Miranda on 22/02/17.
//  Copyright © 2017 Vitor Marques de Miranda. All rights reserved.
//

#ifndef VMMComputerInformation_Class
#define VMMComputerInformation_Class

#define IS_SYSTEM_MAC_OS_10_7_OR_SUPERIOR   [VMMComputerInformation isSystemMacOsEqualOrSuperiorTo:@"10.7"]   // Lion
#define IS_SYSTEM_MAC_OS_10_8_OR_SUPERIOR   [VMMComputerInformation isSystemMacOsEqualOrSuperiorTo:@"10.8"]   // Mountain Lion
#define IS_SYSTEM_MAC_OS_10_9_OR_SUPERIOR   [VMMComputerInformation isSystemMacOsEqualOrSuperiorTo:@"10.9"]   // Mavericks
#define IS_SYSTEM_MAC_OS_10_10_OR_SUPERIOR  [VMMComputerInformation isSystemMacOsEqualOrSuperiorTo:@"10.10"]  // Yosemite
#define IS_SYSTEM_MAC_OS_10_11_OR_SUPERIOR  [VMMComputerInformation isSystemMacOsEqualOrSuperiorTo:@"10.11"]  // El Capitan
#define IS_SYSTEM_MAC_OS_10_12_OR_SUPERIOR  [VMMComputerInformation isSystemMacOsEqualOrSuperiorTo:@"10.12"]  // Sierra
#define IS_SYSTEM_MAC_OS_10_13_OR_SUPERIOR  [VMMComputerInformation isSystemMacOsEqualOrSuperiorTo:@"10.13"]  // High Sierra

#define IsClassAvailable(X)   (NSClassFromString(X) != nil)
#define IsWKWebViewAvailable  IsClassAvailable(@"WKWebView")

#import <Foundation/Foundation.h>

@interface VMMComputerInformation : NSObject

+(NSDictionary*)graphicCardDictionary;
+(NSString*)graphicCardName;
+(NSString*)graphicCardType;

+(NSString*)graphicCardDeviceID;
+(NSString*)graphicCardVendorID;
+(NSString*)graphicCardMemorySize;

+(NSString*)macOsVersion;
+(BOOL)isSystemMacOsEqualOrSuperiorTo:(NSString*)version;

+(NSString*)macOsBuildVersion;

+(BOOL)isUserStaffGroupMember;

@end

#endif
