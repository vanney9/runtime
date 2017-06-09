//
//  main.m
//  debug-objc
//
//  Created by vanney on 2017/4/17.
//
//

#import "runtime.h"
#import <Foundation/Foundation.h>
#import "HCSon.h"

// getter
void setSb(id self, SEL _cmd, NSString *value) {
    objc_setAssociatedObject(self, "sb", value, OBJC_ASSOCIATION_COPY_NONATOMIC);
}

// setter
NSString *sb(id self, SEL _cmd) {
    return objc_getAssociatedObject(self, "sb");
}


// custom getter && setter

void customSetter(id self, SEL _cmd, id value) {
    NSString *propertyStr = NSStringFromSelector(_cmd);
    // divide set
    NSString *realProperty = [propertyStr substringFromIndex:3];
    realProperty = [realProperty substringToIndex:realProperty.length - 1];
    realProperty = [realProperty lowercaseString];
    //const NSString *key = [realProperty copy];
    objc_setAssociatedObject(self, NSSelectorFromString(realProperty), value, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    //objc_setAssociatedObject(self, "sb", value, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

id customGetter(id self, SEL _cmd) {
    id result = objc_getAssociatedObject(self, _cmd);
    //id result = objc_getAssociatedObject(self, "sb");
    return result;
}


int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSLog(@"vanney code log : %p", [HCBase class]);

        // print property
//        int count;
//        objc_property_t *properties = class_copyPropertyList([HCBase class], &count);
//        for (int i = 0; i < count; ++i) {
//            objc_property_t curProperty = properties[i];
//            printf("property name is %s and attributes is %s\n", property_getName(curProperty), property_getAttributes(curProperty));
//        }


        // runtime add property
        objc_property_attribute_t attribute1 = {"T", @encode(NSString *)};
        objc_property_attribute_t attribute2 = {"N", ""};
        objc_property_attribute_t attribute3 = {"&", ""};
        objc_property_attribute_t attribute[] = {attribute1, attribute2, attribute3};
        class_addProperty([HCBase class], "sb", attribute, 3);

        // add property getter and setter
        //class_addMethod([HCBase class], @selector(sb), (IMP) sb, "@@:");
        class_addMethod([HCBase class], NSSelectorFromString(@"sb"), (IMP) customGetter, "@@:");
        //class_addMethod([HCBase class], @selector(setSb:), (IMP) setSb, "v@:@");
        class_addMethod([HCBase class], NSSelectorFromString(@"setSb:"), (IMP) customSetter, "v@:@");

        

        // new HCBase and set && printf sb
        HCBase *baseOBJ = [[HCBase alloc] init];
        //[baseOBJ performSelector:@selector(setSb:) withObject:@"sb"];
        [baseOBJ performSelector:NSSelectorFromString(@"setSb:") withObject:@"sb"];
        //NSLog(@"vanney code log : new property is %@", [baseOBJ performSelector:@selector(sb)]);
        NSLog(@"vanney code log : new property is %@", [baseOBJ performSelector:NSSelectorFromString(@"sb")]);


        // resolve

        // print method
        int methodCount;
        Method *methodList = class_copyMethodList([HCBase class], &methodCount);
        for (int j = 0; j < methodCount; ++j) {
            Method curMethod = methodList[j];
            printf("before HCBase method name is %s, and type encoding is %s\n", method_getName(curMethod), method_getTypeEncoding(curMethod));
        }
        
        int methodCountS;
        Method *methodListS = class_copyMethodList([HCSon class], &methodCountS);
        for (int j = 0; j < methodCountS; ++j) {
            Method curMethod = methodListS[j];
            printf("before HCSon method name is %s, and type encoding is %s\n", method_getName(curMethod), method_getTypeEncoding(curMethod));
        }
        
        HCSon *son = [[HCSon alloc] init];
        //[baseOBJ needResolve];
        [son needResolve];

        Method *newMethodList = class_copyMethodList([HCBase class], &methodCount);
        for (int j = 0; j < methodCount; ++j) {
            Method curMethod = newMethodList[j];
            printf("new HCBase method name is %s, and type encoding is %s\n", method_getName(curMethod), method_getTypeEncoding(curMethod));
        }
        
        Method *newMethodListS = class_copyMethodList([HCSon class], &methodCountS);
        for (int j = 0; j < methodCountS; ++j) {
            Method curMethod = newMethodListS[j];
            printf("new HCSon method name is %s, and type encoding is %s\n", method_getName(curMethod), method_getTypeEncoding(curMethod));
        }
        
        
        // forwardingTarget
        [baseOBJ needForwardTarget];
        
        // final forwarding
        [baseOBJ needFinalForward];
    }
    return 0;
}
