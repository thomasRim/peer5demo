NS_ASSUME_NONNULL_BEGIN
@interface Peer5Sdk : NSObject
- (NSURL*)streamURLForURL:(NSURL*)url NS_SWIFT_NAME(streamURL(forURL:));
- (instancetype)init __attribute__((unavailable("")));
- (instancetype)initWithToken:(NSString*)peer5Token NS_DESIGNATED_INITIALIZER NS_SWIFT_NAME(init(token:));
@end
NS_ASSUME_NONNULL_END
