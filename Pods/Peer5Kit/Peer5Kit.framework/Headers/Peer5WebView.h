@interface Peer5WebView : NSObject
- (void)startWithToken:(NSString*) token;
- (void)sendURL:(NSString *)url requestId:(NSNumber *)requestId port:(NSNumber *)port;
+ (NSString* )getVersion;
@property(readonly) BOOL ready;

@end
