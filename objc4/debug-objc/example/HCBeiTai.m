//
//  HCBeiTai.m
//  objc
//
//  Created by vanney on 2017/6/9.
//
//

#import "HCBeiTai.h"

@implementation HCBeiTai

- (void)needForwardTarget {
    NSLog(@"bei tai 作用了");
}

- (void)beitaiForwarding:(int)index {
    NSLog(@"vanney code log : bei tai 终极forwarding起作用了 : index is %d", index);
}


@end
