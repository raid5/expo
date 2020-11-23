#import "ABI40_0_0REANode.h"

@interface ABI40_0_0REAPropsNode : ABI40_0_0REANode <ABI40_0_0REAFinalNode>

- (void)connectToView:(NSNumber *_Nonnull)viewTag
             viewName:(NSString *_Nonnull)viewName;

- (void)disconnectFromView:(NSNumber *_Nonnull)viewTag;

@end

