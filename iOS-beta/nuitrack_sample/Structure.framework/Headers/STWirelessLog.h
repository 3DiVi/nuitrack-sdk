/* 
    This file is part of the Structure SDK.
    Copyright © 2019 Occipital, Inc. All rights reserved.
    http://structure.io
*/

#pragma once

#import <Structure/StructureBase.h>

#pragma mark STWirelessLog API

/** The STWirelessLog class is a wireless logging utility.

This class gives the ability to wirelessly send log messages to a remote console.

It is very useful when the sensor is occupying the lightning port.
*/
@interface STWirelessLog : NSObject

/**  Redirect the standard and error outputs to a TCP connection.

Messages sent to the `stdout` and `stderr` (such as `NSLog`, `std::cout`, `std::cerr`, `printf`) will be sent to the given IPv4 address on the specified port.

In order to receive these messages on a remote machine, you can, for instance, use the *netcat* command-line utility (available by default on Mac OS X). Simply run in a terminal: `nc -lk <port>`

@param ipv4Address The IPv4 address of the remote console.
@param port The port of the remote console.
@param error will contain detailed information if the provided options are incorrect.

@note If the connection fails, the returned error will be non-`nil` and no output will be transmitted.
@note Only one connection can be active.
*/
+ (void)broadcastLogsToWirelessConsoleAtAddress:(NSString *)ipv4Address usingPort:(int)port error:(NSError **)error;

@end
