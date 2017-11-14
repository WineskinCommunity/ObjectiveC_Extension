//
//  NSTask+Extension.m
//  ObjectiveC_Extension
//
//  Created by Vitor Marques de Miranda on 22/02/17.
//  Copyright © 2017 Vitor Marques de Miranda. All rights reserved.
//

#import "NSTask+Extension.h"

#import "NSAlert+Extension.h"
#import "NSThread+Extension.h"
#import "NSFileManager+Extension.h"

#import "VMMLogUtility.h"

@implementation NSTask (VMMTask)

static NSMutableDictionary* binaryPaths;

+(NSString*)runCommand:(NSArray<NSString*>*)programAndFlags
{
    return [self runCommand:programAndFlags atRunPath:nil];
}
+(NSString*)runCommand:(NSArray<NSString*>*)programAndFlags atRunPath:(NSString*)path
{
    return [self runCommand:programAndFlags atRunPath:path andWait:YES];
}
+(NSString*)runCommand:(NSArray<NSString*>*)programAndFlags atRunPath:(NSString*)path andWait:(BOOL)shouldWait
{
    NSArray* flags = [programAndFlags objectsAtIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(1, programAndFlags.count - 1)]];
    return [self runProgram:programAndFlags.firstObject withFlags:flags atRunPath:path andWaiting:shouldWait];
}

+(void)runAsynchronousCommand:(NSArray<NSString*>*)programAndFlags
{
    [self runCommand:programAndFlags atRunPath:nil andWait:NO];
}

+(NSString*)runProgram:(NSString*)program withFlags:(NSArray<NSString*>*)flags
{
    return [self runProgram:program withFlags:flags atRunPath:nil andWaiting:YES];
}
+(NSString*)runProgram:(NSString*)program withFlags:(NSArray<NSString*>*)flags outputEncoding:(NSStringEncoding)encoding
{
    return [self runProgram:program withFlags:flags atRunPath:nil withEnvironment:nil
                 andWaiting:YES forTimeInterval:0 outputEncoding:encoding];
}
+(NSString*)runProgram:(NSString*)program withFlags:(NSArray<NSString*>*)flags atRunPath:(NSString*)path andWaiting:(BOOL)wait
{
    return [self runProgram:program withFlags:flags atRunPath:path withEnvironment:nil
                 andWaiting:wait forTimeInterval:0 outputEncoding:NSUTF8StringEncoding];
}
+(NSString*)runProgram:(NSString*)program withFlags:(NSArray<NSString*>*)flags withEnvironment:(NSDictionary*)env
{
    return [self runProgram:program withFlags:flags atRunPath:@"/" withEnvironment:env
                 andWaiting:YES forTimeInterval:0 outputEncoding:NSUTF8StringEncoding];
}
+(NSString*)runProgram:(NSString*)program withFlags:(NSArray<NSString*>*)flags waitingForTimeInterval:(unsigned int)timeout
{
    return [self runProgram:program withFlags:flags atRunPath:@"/" withEnvironment:nil
                 andWaiting:YES forTimeInterval:timeout outputEncoding:NSUTF8StringEncoding];
}

+(NSString*)runProgram:(NSString*)program withFlags:(NSArray<NSString*>*)flags atRunPath:(NSString*)path withEnvironment:(NSDictionary*)env andWaiting:(BOOL)wait forTimeInterval:(unsigned int)timeout outputEncoding:(NSStringEncoding)encoding
{
    if (program && ![program hasPrefix:@"/"])
    {
        NSString* newProgramPath = [self getPathOfProgram:program];
        
        if (!newProgramPath)
        {
            [NSAlert showAlertOfType:NSAlertTypeError
                         withMessage:[NSString stringWithFormat:NSLocalizedString(@"Path for %@ not found.",nil), program]];
            return @"";
        }
        
        program = newProgramPath;
    }
    
#ifdef DEBUG
    if (path && flags)        NSDebugLog(@"Running %@ at path %@ with flags %@",program,path,[flags componentsJoinedByString:@" "]);
    else if (path && !flags)  NSDebugLog(@"Running %@ at path %@",program,path);
    else if (!path && flags)  NSDebugLog(@"Running %@ with flags %@",program,[flags componentsJoinedByString:@" "]);
    else if (!path && !flags) NSDebugLog(@"Running %@",program);
#endif
    
    if (path && ![path hasSuffix:@"/"]) path = [path stringByAppendingString:@"/"];
    
    if (![[NSFileManager defaultManager] fileExistsAtPath:program])
    {
        [NSAlert showAlertOfType:NSAlertTypeError
                     withMessage:[NSString stringWithFormat:NSLocalizedString(@"File %@ not found.",nil), program]];
        return @"";
    }
    
    if (![[NSFileManager defaultManager] isExecutableFileAtPath:program])
    {
        [NSAlert showAlertOfType:NSAlertTypeError
                     withMessage:[NSString stringWithFormat:NSLocalizedString(@"File %@ not runnable.",nil), program]];
        return @"";
    }
    
    if (path && ![[NSFileManager defaultManager] directoryExistsAtPath:path])
    {
        [NSAlert showAlertOfType:NSAlertTypeError
                     withMessage:[NSString stringWithFormat:NSLocalizedString(@"Directory %@ does not exists.",nil), path]];
        return @"";
    }
    
    @autoreleasepool
    {
        @try
        {
            NSTask *server = [NSTask new];
            [server setLaunchPath:program];
            if (path)  [server setCurrentDirectoryPath:path];
            if (flags) [server setArguments:flags];
            if (env)   [server setEnvironment:env];
            
            NSFileHandle *errorFileHandle = [NSFileHandle fileHandleWithNullDevice];
            [server setStandardError:errorFileHandle];
            
            if (!wait)
            {
                [server setStandardInput:[NSPipe pipe]];
                [server launch];
                
                NSDebugLog(@"Instruction finished");
                return @"";
            }
            
            NSPipe *outputPipe = [NSPipe pipe];
            [server setStandardInput:[NSPipe pipe]];
            [server setStandardOutput:outputPipe];
            [server launch];
            
            if (timeout == 0)
            {
                [server waitUntilExit];
            }
            else
            {
                __block NSCondition* lock = [[NSCondition alloc] init];
                
                [NSThread dispatchQueueWithName:"wait-until-task-exit" priority:DISPATCH_QUEUE_PRIORITY_DEFAULT concurrent:NO withBlock:^
                {
                    [server waitUntilExit];
                    
                    @synchronized (lock)
                    {
                        if (lock) [lock signal];
                    }
                }];
                
                [NSThread dispatchQueueWithName:"wait-five-seconds-to-kill-task" priority:DISPATCH_QUEUE_PRIORITY_DEFAULT concurrent:NO withBlock:^
                {
                    [NSThread sleepForTimeInterval:timeout];
                    
                    @synchronized (lock)
                    {
                        if (lock)
                        {
                            [lock signal];
                            [server terminate];
                        }
                    }
                }];
                
                [lock lock];
                [lock wait];
                [lock unlock];
                lock = nil;
            }
            
            NSFileHandle *file = [outputPipe fileHandleForReading];
            NSData *outputData = [file readDataToEndOfFile];
            [file closeFile];
            
            NSDebugLog(@"Instruction finished");
            return [[NSString alloc] initWithData:outputData encoding:encoding];
        }
        @catch (NSException* exception)
        {
            // Sometimes (very rarely) the app might fail to retrieve the output of a command; with that, your app won't stop
            NSDebugLog(@"Failed to retrieve instruction output");
            return @"";
        }
    }
}

+(NSString*)getPathOfProgram:(NSString*)programName
{
    if (!programName) return nil;
    if (binaryPaths && binaryPaths[programName]) return binaryPaths[programName];
    
    NSString* programPath;
    
    @autoreleasepool
    {
        if (!binaryPaths) binaryPaths = [[NSMutableDictionary alloc] init];
        
        programPath = [self runCommand:@[@"/usr/bin/type", @"-a", programName]];
        if (!programPath) return nil;
        
        programPath = [[programPath componentsSeparatedByString:@" "] lastObject];
        if (programPath.length == 0) return nil;
        
        programPath = [programPath substringToIndex:programPath.length-1];
    }
    
    if (programPath) binaryPaths[programName] = programPath;
    return programPath;
}

@end

