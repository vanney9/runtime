//
//  HCBase.m
//  objc
//
//  Created by vanney on 2017/6/9.
//
//

#import "HCBase.h"
#import "HCBeiTai.h"


void resolveImp(id self, SEL _cmd) {
    NSLog(@"vanney code log : resolved function");
}

@implementation HCBase

+ (BOOL)resolveInstanceMethod:(SEL)sel {
    if ([NSStringFromSelector(sel) isEqualToString:@"needResolve"]) {
        class_addMethod(self, @selector(needResolve), (IMP) resolveImp, "v@:");
        return YES;
    } else {
        return [[self superclass] resolveInstanceMethod:sel];
    }
}

- (id)forwardingTargetForSelector:(SEL)aSelector {
    if (aSelector == @selector(needForwardTarget)) {
        NSLog(@"vanney code log : forwarding Target start");
        HCBeiTai *beitai = [[HCBeiTai alloc] init];
        return beitai;
    } else {
        return [super forwardingTargetForSelector:aSelector];
    }
}

- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector {
    NSLog(@"vanney code log : selector is %@", NSStringFromSelector(aSelector));
    NSMethodSignature *methodSignature = [super methodSignatureForSelector:aSelector];
    if (!methodSignature) {
        NSLog(@"vanney code log : inside create method signature");
        methodSignature = [NSMethodSignature signatureWithObjCTypes:"v@:i"];
    }

    return methodSignature;
}

- (void)forwardInvocation:(NSInvocation *)anInvocation {
    NSLog(@"vanney code log : forwarding invocation selector is %@", NSStringFromSelector(anInvocation.selector));
    NSLog(@"vanney code log : invocation is %@, and method signature is %@", anInvocation, anInvocation.methodSignature);

    if (anInvocation.selector == @selector(needFinalForward)) {
        NSLog(@"vanney code log : inside forwarding");
        anInvocation.selector = NSSelectorFromString(@"beitaiForwarding:");
        int *a;
        *a = 99;
        [anInvocation setArgument:a atIndex:2];
        HCBeiTai *beiTai = [[HCBeiTai alloc] init];
        [anInvocation invokeWithTarget:beiTai];
    } else {
        NSLog(@"vanney code log : else forwarding");
        [super forwardInvocation:anInvocation];
    }

}

@end
