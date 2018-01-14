#import "ABI25_0_0RNGestureHandlerState.h"
#import "ABI25_0_0RNGestureHandlerEvents.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <ReactABI25_0_0/ABI25_0_0RCTConvert.h>

#define VEC_LEN_SQ(pt) (pt.x * pt.x + pt.y * pt.y)
#define TEST_MIN_IF_NOT_NAN(value, limit) \
(!isnan(limit) && ((limit < 0 && value <= limit) || (limit >= 0 && value >= limit)))

#define TEST_MAX_IF_NOT_NAN(value, max) \
(!isnan(max) && ((max < 0 && value < max) || (max >= 0 && value > max)))

#define APPLY_PROP(recognizer, config, type, prop, propName) do { \
id value = config[propName]; \
if (value != nil) recognizer.prop = [ABI25_0_0RCTConvert type:value]; \
} while(0)

#define APPLY_FLOAT_PROP(prop) do { APPLY_PROP(recognizer, config, CGFloat, prop, @#prop); } while(0)
#define APPLY_INT_PROP(prop) do { APPLY_PROP(recognizer, config, NSInteger, prop, @#prop); } while(0)
#define APPLY_NAMED_INT_PROP(prop, propName) do { APPLY_PROP(recognizer, config, NSInteger, prop, propName); } while(0)

@protocol ABI25_0_0RNGestureHandlerEventEmitter

- (void)sendTouchEvent:(nonnull ABI25_0_0RNGestureHandlerEvent *)event;

- (void)sendStateChangeEvent:(nonnull ABI25_0_0RNGestureHandlerStateChange *)event;

@end


@protocol ABI25_0_0RNRootViewGestureRecognizerDelegate <UIGestureRecognizerDelegate>

- (void)gestureRecognizer:(nullable UIGestureRecognizer *)gestureRecognizer
    didActivateInRootView:(nullable UIView *)rootView;

@end


@interface ABI25_0_0RNGestureHandler : NSObject <UIGestureRecognizerDelegate> {

@protected UIGestureRecognizer *_recognizer;
@protected ABI25_0_0RNGestureHandlerState _lastState;

}

+ (nullable ABI25_0_0RNGestureHandler *)findGestureHandlerByRecognizer:(nonnull UIGestureRecognizer *)recognizer;

- (nonnull instancetype)initWithTag:(nonnull NSNumber *)tag;

@property (nonatomic, readonly, nonnull) NSNumber *tag;
@property (nonatomic, weak, nullable) id<ABI25_0_0RNGestureHandlerEventEmitter> emitter;
@property (nonatomic, readonly, nullable) UIGestureRecognizer *recognizer;
@property (nonatomic) BOOL enabled;
@property(nonatomic) BOOL shouldCancelWhenOutside;

- (void)bindToView:(nonnull UIView *)view;
- (void)unbindFromView;
- (void)configure:(nullable NSDictionary *)config NS_REQUIRES_SUPER;
- (void)handleGesture:(nonnull id)recognizer;
- (ABI25_0_0RNGestureHandlerState)state;
- (nullable ABI25_0_0RNGestureHandlerEventExtraData *)eventExtraData:(nonnull id)recognizer;

- (void)reset;
- (void)sendEventsInState:(ABI25_0_0RNGestureHandlerState)state
           forViewWithTag:(nonnull NSNumber *)ReactABI25_0_0Tag
            withExtraData:(ABI25_0_0RNGestureHandlerEventExtraData *)extraData;

@end

