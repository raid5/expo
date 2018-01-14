/**
 * Copyright (c) 2015-present, Horcrux.
 * All rights reserved.
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "ABI25_0_0RNSVGRectManager.h"

#import "ABI25_0_0RNSVGRect.h"
#import "ABI25_0_0RCTConvert+RNSVG.h"

@implementation ABI25_0_0RNSVGRectManager

ABI25_0_0RCT_EXPORT_MODULE()

- (ABI25_0_0RNSVGRenderable *)node
{
  return [ABI25_0_0RNSVGRect new];
}

ABI25_0_0RCT_EXPORT_VIEW_PROPERTY(x, NSString)
ABI25_0_0RCT_EXPORT_VIEW_PROPERTY(y, NSString)
ABI25_0_0RCT_EXPORT_VIEW_PROPERTY(width, NSString)
ABI25_0_0RCT_EXPORT_VIEW_PROPERTY(height, NSString)
ABI25_0_0RCT_EXPORT_VIEW_PROPERTY(rx, NSString)
ABI25_0_0RCT_EXPORT_VIEW_PROPERTY(ry, NSString)

@end
