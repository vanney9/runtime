//
//  HVCSon.m
//  objc
//
//  Created by vanney on 2017/5/22.
//
//

#import "HVCSon.h"

@implementation HVCSon

- (instancetype)initWithI:(int)i {
    if (self = [super initWithI:8 andS:@"father"]) {
        self->sonInt = i;
    }
    
    return self;
}

- (void)hello {
    NSLog(@"sun hello %d", sonInt);
}

@end
