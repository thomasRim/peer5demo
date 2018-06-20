/*
 Copyright (c) 2012-2015, Pierre-Olivier Latour
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * The name of Pierre-Olivier Latour may not be used to endorse
 or promote products derived from this software without specific
 prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL PIERRE-OLIVIER LATOUR BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <TargetConditionals.h>

#import "Peer5WebServerRequest.h"
#import "Peer5WebServerResponse.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  The Peer5WebServerMatchBlock is called for every handler added to the
 *  Peer5WebServer whenever a new HTTP request has started (i.e. HTTP headers have
 *  been received). The block is passed the basic info for the request (HTTP method,
 *  URL, headers...) and must decide if it wants to handle it or not.
 *
 *  If the handler can handle the request, the block must return a new
 *  Peer5WebServerRequest instance created with the same basic info.
 *  Otherwise, it simply returns nil.
 */
typedef Peer5WebServerRequest* _Nullable (^Peer5WebServerMatchBlock)(NSString* requestMethod, NSURL* requestURL, NSDictionary* requestHeaders, NSString* urlPath, NSDictionary* urlQuery);

/**
 *  The Peer5WebServerProcessBlock is called after the HTTP request has been fully
 *  received (i.e. the entire HTTP body has been read). The block is passed the
 *  Peer5WebServerRequest created at the previous step by the Peer5WebServerMatchBlock.
 *
 *  The block must return a Peer5WebServerResponse or nil on error, which will
 *  result in a 500 HTTP status code returned to the client. It's however
 *  recommended to return a Peer5WebServerErrorResponse on error so more useful
 *  information can be returned to the client.
 */
typedef Peer5WebServerResponse* _Nullable (^Peer5WebServerProcessBlock)(__kindof Peer5WebServerRequest* request);

/**
 *  The Peer5WebServerAsynchronousProcessBlock works like the Peer5WebServerProcessBlock
 *  except the Peer5WebServerResponse can be returned to the server at a later time
 *  allowing for asynchronous generation of the response.
 *
 *  The block must eventually call "completionBlock" passing a Peer5WebServerResponse
 *  or nil on error, which will result in a 500 HTTP status code returned to the client.
 *  It's however recommended to return a Peer5WebServerErrorResponse on error so more
 *  useful information can be returned to the client.
 */
typedef void (^Peer5WebServerCompletionBlock)(Peer5WebServerResponse* _Nullable response);
typedef void (^Peer5WebServerAsyncProcessBlock)(__kindof Peer5WebServerRequest* request, Peer5WebServerCompletionBlock completionBlock);

/**
 *  The port used by the Peer5WebServer (NSNumber / NSUInteger).
 *
 *  The default value is 0 i.e. let the OS pick a random port.
 */
extern NSString* const Peer5WebServerOption_Port;

/**
 *  The Bonjour name used by the Peer5WebServer (NSString). If set to an empty string,
 *  the name will automatically take the value of the Peer5WebServerOption_ServerName
 *  option. If this option is set to nil, Bonjour will be disabled.
 *
 *  The default value is nil.
 */
extern NSString* const Peer5WebServerOption_BonjourName;

/**
 *  The Bonjour service type used by the Peer5WebServer (NSString).
 *
 *  The default value is "_http._tcp", the service type for HTTP web servers.
 */
extern NSString* const Peer5WebServerOption_BonjourType;

/**
 *  Request a port mapping in the NAT gateway (NSNumber / BOOL).
 *
 *  This uses the DNSService API under the hood which supports IPv4 mappings only.
 *
 *  The default value is NO.
 *
 *  @warning The external port set up by the NAT gateway may be different than
 *  the one used by the Peer5WebServer.
 */
extern NSString* const Peer5WebServerOption_RequestNATPortMapping;

/**
 *  Only accept HTTP requests coming from localhost i.e. not from the outside
 *  network (NSNumber / BOOL).
 *
 *  The default value is NO.
 *
 *  @warning Bonjour and NAT port mapping should be disabled if using this option
 *  since the server will not be reachable from the outside network anyway.
 */
extern NSString* const Peer5WebServerOption_BindToLocalhost;

/**
 *  The maximum number of incoming HTTP requests that can be queued waiting to
 *  be handled before new ones are dropped (NSNumber / NSUInteger).
 *
 *  The default value is 16.
 */
extern NSString* const Peer5WebServerOption_MaxPendingConnections;

/**
 *  The value for "Server" HTTP header used by the Peer5WebServer (NSString).
 *
 *  The default value is the Peer5WebServer class name.
 */
extern NSString* const Peer5WebServerOption_ServerName;

/**
 *  The authentication method used by the Peer5WebServer
 *  (one of "Peer5WebServerAuthenticationMethod_...").
 *
 *  The default value is nil i.e. authentication is disabled.
 */
extern NSString* const Peer5WebServerOption_AuthenticationMethod;

/**
 *  The authentication realm used by the Peer5WebServer (NSString).
 *
 *  The default value is the same as the Peer5WebServerOption_ServerName option.
 */
extern NSString* const Peer5WebServerOption_AuthenticationRealm;

/**
 *  The authentication accounts used by the Peer5WebServer
 *  (NSDictionary of username / password pairs).
 *
 *  The default value is nil i.e. no accounts.
 */
extern NSString* const Peer5WebServerOption_AuthenticationAccounts;

/**
 *  The class used by the Peer5WebServer when instantiating Peer5WebServerConnection
 *  (subclass of Peer5WebServerConnection).
 *
 *  The default value is the Peer5WebServerConnection class.
 */
extern NSString* const Peer5WebServerOption_ConnectionClass;

/**
 *  Allow the Peer5WebServer to pretend "HEAD" requests are actually "GET" ones
 *  and automatically discard the HTTP body of the response (NSNumber / BOOL).
 *
 *  The default value is YES.
 */
extern NSString* const Peer5WebServerOption_AutomaticallyMapHEADToGET;

/**
 *  The interval expressed in seconds used by the Peer5WebServer to decide how to
 *  coalesce calls to -webServerDidConnect: and -webServerDidDisconnect:
 *  (NSNumber / double). Coalescing will be disabled if the interval is <= 0.0.
 *
 *  The default value is 1.0 second.
 */
extern NSString* const Peer5WebServerOption_ConnectedStateCoalescingInterval;

/**
 *  Set the dispatch queue priority on which server connection will be 
 *  run (NSNumber / long).
 *
 *
 *  The default value is DISPATCH_QUEUE_PRIORITY_DEFAULT.
 */
extern NSString* const Peer5WebServerOption_DispatchQueuePriority;

#if TARGET_OS_IPHONE

/**
 *  Enables the Peer5WebServer to automatically suspend itself (as if -stop was
 *  called) when the iOS app goes into the background and the last
 *  Peer5WebServerConnection is closed, then resume itself (as if -start was called)
 *  when the iOS app comes back to the foreground (NSNumber / BOOL).
 *
 *  See the README.md file for more information about this option.
 *
 *  The default value is YES.
 *
 *  @warning The running property will be NO while the Peer5WebServer is suspended.
 */
extern NSString* const Peer5WebServerOption_AutomaticallySuspendInBackground;

#endif

/**
 *  HTTP Basic Authentication scheme (see https://tools.ietf.org/html/rfc2617).
 *
 *  @warning Use of this authentication scheme is not recommended as the
 *  passwords are sent in clear.
 */
extern NSString* const Peer5WebServerAuthenticationMethod_Basic;

/**
 *  HTTP Digest Access Authentication scheme (see https://tools.ietf.org/html/rfc2617).
 */
extern NSString* const Peer5WebServerAuthenticationMethod_DigestAccess;

@class Peer5WebServer;

/**
 *  Delegate methods for Peer5WebServer.
 *
 *  @warning These methods are always called on the main thread in a serialized way.
 */
@protocol Peer5WebServerDelegate <NSObject>
@optional

/**
 *  This method is called after the server has successfully started.
 */
- (void)webServerDidStart:(Peer5WebServer*)server;

/**
 *  This method is called after the Bonjour registration for the server has
 *  successfully completed.
 *
 *  Use the "bonjourServerURL" property to retrieve the Bonjour address of the
 *  server.
 */
- (void)webServerDidCompleteBonjourRegistration:(Peer5WebServer*)server;

/**
 *  This method is called after the NAT port mapping for the server has been
 *  updated.
 *
 *  Use the "publicServerURL" property to retrieve the public address of the
 *  server.
 */
- (void)webServerDidUpdateNATPortMapping:(Peer5WebServer*)server;

/**
 *  This method is called when the first Peer5WebServerConnection is opened by the
 *  server to serve a series of HTTP requests.
 *
 *  A series of HTTP requests is considered ongoing as long as new HTTP requests
 *  keep coming (and new Peer5WebServerConnection instances keep being opened),
 *  until before the last HTTP request has been responded to (and the
 *  corresponding last Peer5WebServerConnection closed).
 */
- (void)webServerDidConnect:(Peer5WebServer*)server;

/**
 *  This method is called when the last Peer5WebServerConnection is closed after
 *  the server has served a series of HTTP requests.
 *
 *  The Peer5WebServerOption_ConnectedStateCoalescingInterval option can be used
 *  to have the server wait some extra delay before considering that the series
 *  of HTTP requests has ended (in case there some latency between consecutive
 *  requests). This effectively coalesces the calls to -webServerDidConnect:
 *  and -webServerDidDisconnect:.
 */
- (void)webServerDidDisconnect:(Peer5WebServer*)server;

/**
 *  This method is called after the server has stopped.
 */
- (void)webServerDidStop:(Peer5WebServer*)server;

@end

/**
 *  The Peer5WebServer class listens for incoming HTTP requests on a given port,
 *  then passes each one to a "handler" capable of generating an HTTP response
 *  for it, which is then sent back to the client.
 *
 *  Peer5WebServer instances can be created and used from any thread but it's
 *  recommended to have the main thread's runloop be running so internal callbacks
 *  can be handled e.g. for Bonjour registration.
 *
 *  See the README.md file for more information about the architecture of Peer5WebServer.
 */
@interface Peer5WebServer : NSObject

/**
 *  Sets the delegate for the server.
 */
@property(nonatomic, weak, nullable) id<Peer5WebServerDelegate> delegate;

/**
 *  Returns YES if the server is currently running.
 */
@property(nonatomic, readonly, getter=isRunning) BOOL running;

/**
 *  Returns the port used by the server.
 *
 *  @warning This property is only valid if the server is running.
 */
@property(nonatomic, readonly) NSUInteger port;

/**
 *  Returns the Bonjour name used by the server.
 *
 *  @warning This property is only valid if the server is running and Bonjour
 *  registration has successfully completed, which can take up to a few seconds.
 */
@property(nonatomic, readonly, nullable) NSString* bonjourName;

/**
 *  Returns the Bonjour service type used by the server.
 *
 *  @warning This property is only valid if the server is running and Bonjour
 *  registration has successfully completed, which can take up to a few seconds.
 */
@property(nonatomic, readonly, nullable) NSString* bonjourType;

/**
 *  This method is the designated initializer for the class.
 */
- (instancetype)init;

/**
 *  Adds to the server a handler that generates responses synchronously when handling incoming HTTP requests.
 *
 *  Handlers are called in a LIFO queue, so if multiple handlers can potentially
 *  respond to a given request, the latest added one wins.
 *
 *  @warning Addling handlers while the server is running is not allowed.
 */
- (void)addHandlerWithMatchBlock:(Peer5WebServerMatchBlock)matchBlock processBlock:(Peer5WebServerProcessBlock)processBlock;

/**
 *  Adds to the server a handler that generates responses asynchronously when handling incoming HTTP requests.
 *
 *  Handlers are called in a LIFO queue, so if multiple handlers can potentially
 *  respond to a given request, the latest added one wins.
 *
 *  @warning Addling handlers while the server is running is not allowed.
 */
- (void)addHandlerWithMatchBlock:(Peer5WebServerMatchBlock)matchBlock asyncProcessBlock:(Peer5WebServerAsyncProcessBlock)processBlock;

/**
 *  Removes all handlers previously added to the server.
 *
 *  @warning Removing handlers while the server is running is not allowed.
 */
- (void)removeAllHandlers;

/**
 *  Starts the server with explicit options. This method is the designated way
 *  to start the server.
 *
 *  Returns NO if the server failed to start and sets "error" argument if not NULL.
 */
- (BOOL)startWithOptions:(nullable NSDictionary*)options error:(NSError** _Nullable)error;

/**
 *  Stops the server and prevents it to accepts new HTTP requests.
 *
 *  @warning Stopping the server does not abort Peer5WebServerConnection instances
 *  currently handling already received HTTP requests. These connections will
 *  continue to execute normally until completion.
 */
- (void)stop;

@end

@interface Peer5WebServer (Extensions)

/**
 *  Returns the server's URL.
 *
 *  @warning This property is only valid if the server is running.
 */
@property(nonatomic, readonly, nullable) NSURL* serverURL;

/**
 *  Returns the server's Bonjour URL.
 *
 *  @warning This property is only valid if the server is running and Bonjour
 *  registration has successfully completed, which can take up to a few seconds.
 *  Also be aware this property will not automatically update if the Bonjour hostname
 *  has been dynamically changed after the server started running (this should be rare).
 */
@property(nonatomic, readonly, nullable) NSURL* bonjourServerURL;

/**
 *  Returns the server's public URL.
 *
 *  @warning This property is only valid if the server is running and NAT port
 *  mapping is active.
 */
@property(nonatomic, readonly, nullable) NSURL* publicServerURL;

/**
 *  Starts the server on port 8080 (OS X & iOS Simulator) or port 80 (iOS)
 *  using the default Bonjour name.
 *
 *  Returns NO if the server failed to start.
 */
- (BOOL)start;

/**
 *  Starts the server on a given port and with a specific Bonjour name.
 *  Pass a nil Bonjour name to disable Bonjour entirely or an empty string to
 *  use the default name.
 *
 *  Returns NO if the server failed to start.
 */
- (BOOL)startWithPort:(NSUInteger)port bonjourName:(nullable NSString*)name;

#if !TARGET_OS_IPHONE

/**
 *  Runs the server synchronously using -startWithPort:bonjourName: until a
 *  SIGINT signal is received i.e. Ctrl-C. This method is intended to be used
 *  by command line tools.
 *
 *  Returns NO if the server failed to start.
 *
 *  @warning This method must be used from the main thread only.
 */
- (BOOL)runWithPort:(NSUInteger)port bonjourName:(nullable NSString*)name;

/**
 *  Runs the server synchronously using -startWithOptions: until a SIGTERM or
 *  SIGINT signal is received i.e. Ctrl-C in Terminal. This method is intended to
 *  be used by command line tools.
 *
 *  Returns NO if the server failed to start and sets "error" argument if not NULL.
 *
 *  @warning This method must be used from the main thread only.
 */
- (BOOL)runWithOptions:(nullable NSDictionary*)options error:(NSError** _Nullable)error;

#endif

@end

@interface Peer5WebServer (Handlers)

/**
 *  Adds a default handler to the server to handle all incoming HTTP requests
 *  with a given HTTP method and generate responses synchronously.
 */
- (void)addDefaultHandlerForMethod:(NSString*)method requestClass:(Class)aClass processBlock:(Peer5WebServerProcessBlock)block;

/**
 *  Adds a default handler to the server to handle all incoming HTTP requests
 *  with a given HTTP method and generate responses asynchronously.
 */
- (void)addDefaultHandlerForMethod:(NSString*)method requestClass:(Class)aClass asyncProcessBlock:(Peer5WebServerAsyncProcessBlock)block;

/**
 *  Adds a handler to the server to handle incoming HTTP requests with a given
 *  HTTP method and a specific case-insensitive path  and generate responses
 *  synchronously.
 */
- (void)addHandlerForMethod:(NSString*)method path:(NSString*)path requestClass:(Class)aClass processBlock:(Peer5WebServerProcessBlock)block;

/**
 *  Adds a handler to the server to handle incoming HTTP requests with a given
 *  HTTP method and a specific case-insensitive path and generate responses
 *  asynchronously.
 */
- (void)addHandlerForMethod:(NSString*)method path:(NSString*)path requestClass:(Class)aClass asyncProcessBlock:(Peer5WebServerAsyncProcessBlock)block;

/**
 *  Adds a handler to the server to handle incoming HTTP requests with a given
 *  HTTP method and a path matching a case-insensitive regular expression and
 *  generate responses synchronously.
 */
- (void)addHandlerForMethod:(NSString*)method pathRegex:(NSString*)regex requestClass:(Class)aClass processBlock:(Peer5WebServerProcessBlock)block;

/**
 *  Adds a handler to the server to handle incoming HTTP requests with a given
 *  HTTP method and a path matching a case-insensitive regular expression and
 *  generate responses asynchronously.
 */
- (void)addHandlerForMethod:(NSString*)method pathRegex:(NSString*)regex requestClass:(Class)aClass asyncProcessBlock:(Peer5WebServerAsyncProcessBlock)block;

@end

@interface Peer5WebServer (GETHandlers)

/**
 *  Adds a handler to the server to respond to incoming "GET" HTTP requests
 *  with a specific case-insensitive path with in-memory data.
 */
- (void)addGETHandlerForPath:(NSString*)path staticData:(NSData*)staticData contentType:(nullable NSString*)contentType cacheAge:(NSUInteger)cacheAge;

/**
 *  Adds a handler to the server to respond to incoming "GET" HTTP requests
 *  with a specific case-insensitive path with a file.
 */
- (void)addGETHandlerForPath:(NSString*)path filePath:(NSString*)filePath isAttachment:(BOOL)isAttachment cacheAge:(NSUInteger)cacheAge allowRangeRequests:(BOOL)allowRangeRequests;

/**
 *  Adds a handler to the server to respond to incoming "GET" HTTP requests
 *  with a case-insensitive path inside a base path with the corresponding file
 *  inside a local directory. If no local file matches the request path, a 401
 *  HTTP status code is returned to the client.
 *
 *  The "indexFilename" argument allows to specify an "index" file name to use
 *  when the request path corresponds to a directory.
 */
- (void)addGETHandlerForBasePath:(NSString*)basePath directoryPath:(NSString*)directoryPath indexFilename:(nullable NSString*)indexFilename cacheAge:(NSUInteger)cacheAge allowRangeRequests:(BOOL)allowRangeRequests;

@end

/**
 *  Peer5WebServer provides its own built-in logging facility which is used by
 *  default. It simply sends log messages to stderr assuming it is connected
 *  to a terminal type device.
 *
 *  Peer5WebServer is also compatible with a limited set of third-party logging
 *  facilities. If one of them is available at compile time, Peer5WebServer will
 *  automatically use it in place of the built-in one.
 *
 *  Currently supported third-party logging facilities are:
 *  - XLFacility (by the same author as Peer5WebServer): https://github.com/swisspol/XLFacility
 *  - CocoaLumberjack: https://github.com/CocoaLumberjack/CocoaLumberjack
 *
 *  For both the built-in logging facility and CocoaLumberjack, the default
 *  logging level is INFO (or DEBUG if the preprocessor constant "DEBUG"
 *  evaluates to non-zero at compile time).
 *
 *  It's possible to have Peer5WebServer use a custom logging facility by defining
 *  the "__Peer5WebServer_LOGGING_HEADER__" preprocessor constant in Xcode build
 *  settings to the name of a custom header file (escaped like \"MyLogging.h\").
 *  This header file must define the following set of macros:
 *
 *    GWS_LOG_DEBUG(...)
 *    GWS_LOG_VERBOSE(...)
 *    GWS_LOG_INFO(...)
 *    GWS_LOG_WARNING(...)
 *    GWS_LOG_ERROR(...)
 *
 *  IMPORTANT: These macros must behave like NSLog(). Furthermore the GWS_LOG_DEBUG()
 *  macro should not do anything unless the preprocessor constant "DEBUG" evaluates
 *  to non-zero.
 *
 *  The logging methods below send log messages to the same logging facility
 *  used by Peer5WebServer. They can be used for consistency wherever you interact
 *  with Peer5WebServer in your code (e.g. in the implementation of handlers).
 */
@interface Peer5WebServer (Logging)

/**
 *  Sets the log level of the logging facility below which log messages are discarded.
 *
 *  @warning The interpretation of the "level" argument depends on the logging
 *  facility used at compile time.
 *
 *  If using the built-in logging facility, the log levels are as follow:
 *  DEBUG = 0
 *  VERBOSE = 1
 *  INFO = 2
 *  WARNING = 3
 *  ERROR = 4
 */
+ (void)setLogLevel:(int)level;

/**
 *  Logs a message to the logging facility at the VERBOSE level.
 */
- (void)logVerbose:(NSString*)format, ... NS_FORMAT_FUNCTION(1, 2);

/**
 *  Logs a message to the logging facility at the INFO level.
 */
- (void)logInfo:(NSString*)format, ... NS_FORMAT_FUNCTION(1, 2);

/**
 *  Logs a message to the logging facility at the WARNING level.
 */
- (void)logWarning:(NSString*)format, ... NS_FORMAT_FUNCTION(1, 2);

/**
 *  Logs a message to the logging facility at the ERROR level.
 */
- (void)logError:(NSString*)format, ... NS_FORMAT_FUNCTION(1, 2);

@end

#ifdef __Peer5WebServer_ENABLE_TESTING__

@interface Peer5WebServer (Testing)

/**
 *  Activates recording of HTTP requests and responses which create files in the
 *  current directory containing the raw data for all requests and responses.
 *
 *  @warning The current directory must not contain any prior recording files.
 */
@property(nonatomic, getter=isRecordingEnabled) BOOL recordingEnabled;

/**
 *  Runs tests by playing back pre-recorded HTTP requests in the given directory
 *  and comparing the generated responses with the pre-recorded ones.
 *
 *  Returns the number of failed tests or -1 if server failed to start.
 */
- (NSInteger)runTestsWithOptions:(nullable NSDictionary*)options inDirectory:(NSString*)path;

@end

#endif

NS_ASSUME_NONNULL_END
