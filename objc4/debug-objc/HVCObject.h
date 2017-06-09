//
//  HVCObject.h
//  objc
//
//  Created by vanney on 2017/4/21.
//
//

#import <Foundation/Foundation.h>

@interface HVCObject : NSObject {
    NSInteger iInt;
    NSString *iStr;
}

@property (nonatomic, strong) NSString *pStr;

- (void)hello;
- (instancetype)initWithI:(int)i andS:(NSString *)s;
@end
