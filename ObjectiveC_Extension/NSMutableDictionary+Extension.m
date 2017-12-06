//
//  NSExtensions.m
//  ObjectiveC_Extension
//
//  Created by Vitor Marques de Miranda on 22/07/16.
//  Copyright © 2016 Vitor Marques de Miranda. All rights reserved.
//

#import "NSMutableDictionary+Extension.h"

@implementation NSMutableDictionary (VMMMutableDictionary)

+(nullable instancetype)mutableDictionaryWithContentsOfFile:(nonnull NSString*)filePath
{
    NSMutableDictionary *dictionary;
    
    @try
    {
        dictionary = [[NSMutableDictionary alloc] initWithContentsOfFile:filePath];
    }
    @catch (NSException *exception)
    {
        return nil;
    }
    
    return dictionary;
}

@end

