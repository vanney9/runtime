//
//  HCBase.h
//  objc
//
//  Created by vanney on 2017/6/9.
//
//

#import "runtime.h"
#import <Foundation/Foundation.h>

@interface HCBase : NSObject

//@property (nonatomic, strong) NSString *curry;
//@property (nonatomic, copy) NSString *kd;
//@property (nonatomic, assign) int kt;

- (void)needResolve;

- (void)needForwardTarget;

- (void)needFinalForward;

@end
