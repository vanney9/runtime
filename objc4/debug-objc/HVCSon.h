//
//  HVCSon.h
//  objc
//
//  Created by vanney on 2017/5/22.
//
//

#import "HVCObject.h"

static const NSString *dataStr = @"wtf";

@interface HVCSon : HVCObject {
    NSInteger sonInt;
}

- (instancetype)initWithI:(int)i;

@property(nonatomic, strong) NSString *sonStr;

@end
