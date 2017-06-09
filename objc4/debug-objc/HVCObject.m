//
//  HVCObject.m
//  objc
//
//  Created by vanney on 2017/4/21.
//
//

#import "HVCObject.h"

@implementation HVCObject

- (instancetype)initWithI:(int)i andS:(NSString *)s {
    if (self = [super init]) {
        self->iInt = i;
        self->iStr = s;
    }
    
    return self;
}

- (void)hello {
    NSLog(@"Hello");
}

- (void)p_hi {
    NSLog(@"hi");
}

@end
