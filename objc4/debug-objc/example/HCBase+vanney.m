//
//  HCBase+vanney.m
//  objc
//
//  Created by vanney on 2017/6/9.
//
//

#import "HCBase+vanney.h"

@implementation HCBase (vanney)

// for cui
- (void)setCui:(int)cui {
    objc_setAssociatedObject(self, "cui", @(cui), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (int)cui {
    return [objc_getAssociatedObject(self, "cui") intValue];
}


// for van
- (void)setVan:(NSString *)van {
    objc_setAssociatedObject(self, "van", van, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (NSString *)van {
    return objc_getAssociatedObject(self, "van");
}

@end
