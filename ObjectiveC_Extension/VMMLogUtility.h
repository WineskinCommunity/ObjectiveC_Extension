//
//  VMMLogUtility.h
//  ObjectiveC_Extension
//
//  Created by Vitor Marques de Miranda on 31/07/2017.
//  Copyright © 2017 Vitor Marques de Miranda. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifdef DEBUG
    #define NSDebugLog(FORMAT, ...) system([[NSString stringWithFormat:@"echo \"%@\" | tee -a ~/Desktop/debug.log", [[[[NSString stringWithFormat:FORMAT, ##__VA_ARGS__] stringByReplacingOccurrencesOfString:@"\"" withString:@"\\\""] stringByReplacingOccurrencesOfString:@"\n" withString:@"\\n"] stringByTrimmingCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@"\0"]]] UTF8String])
#else
    #define NSDebugLog(...)
#endif

void NSStackTraceLog(void);

// Source:
// https://gist.github.com/sfider/3072143

#define measureTime(__message) \
    for (CFAbsoluteTime startTime##__LINE__ = CFAbsoluteTimeGetCurrent(), endTime##__LINE__ = 0.0; endTime##__LINE__ == 0.0; \
    NSDebugLog(@"'%@' took %.6fs", (__message), (endTime##__LINE__ = CFAbsoluteTimeGetCurrent()) - startTime##__LINE__))

