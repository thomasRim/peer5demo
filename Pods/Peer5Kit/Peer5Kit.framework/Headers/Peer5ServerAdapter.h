@interface Peer5ServerAdapter : NSObject
- (void)start;
- (instancetype)initWithToken:(NSString*) peer5Token;
- (instancetype)init __attribute__((unavailable("")));
- (NSString*)createProxyUrl:(NSString*) from;
@end

