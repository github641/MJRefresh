//  代码地址: https://github.com/CoderMJLee/MJRefresh
//  代码地址: http://code4app.com/ios/%E5%BF%AB%E9%80%9F%E9%9B%86%E6%88%90%E4%B8%8B%E6%8B%89%E4%B8%8A%E6%8B%89%E5%88%B7%E6%96%B0/52326ce26803fabc46000000
#import <UIKit/UIKit.h>
#import <objc/message.h>

// 弱引用
#define MJWeakSelf __weak typeof(self) weakSelf = self;

// 日志输出
#ifdef DEBUG
#define MJRefreshLog(...) NSLog(__VA_ARGS__)
#else
#define MJRefreshLog(...)
#endif

/* lzy170830注:
 这个提示API过期的宏。没有找到很好的解释4个2_0的文章。
 
 
 NS_AVAILABLE_IOS(5_0) 这个方法可以在iOS5.0及以后的版本中使用，如果在比5.0更老的版本中调用这个方法，就会引起崩溃。
 
 NS_DEPRECATED_IOS(2_0, 6_0)这个宏中有两个版本号。前面一个表明了这个方法被引入时的iOS版本，后面一个表明它被废弃时的iOS版本。被废弃并不是指这个方法就不存在了，只是意味着我们应当开始考虑将相关代码迁移到新的API上去了。
 
 NS_AVAILABLE(10_8, 6_0)这个宏告诉我们这方法分别随Mac OS 10.8和iOS 6.0被引入。
 
 NS_DEPRECATED(10_0, 10_6, 2_0, 4_0)这个方法随Mac OS 10.0和iOS 2.0被引入，在Mac OS 10.6和iOS 4.0后被废弃。
 
 NS_CLASS_AVAILABLE(10_11, 9_0)这个类分别随Mac OS 10.11和iOS9.0被引入。
 
 NS_ENUM_AVAILABLE(10_11, 9_0)这个枚举分别随Mac OS 10.11和iOS9.0被引入。
 
 作者：定州吴彦祖
 链接：http://www.jianshu.com/p/92a6e8606338
 來源：简书
 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 
 
 版权归作者所有，任何形式转载请联系作者。
 作者：Joe（来自豆瓣）
 来源：https://www.douban.com/note/577377985/
 宏NS_DEPRECATED是定义在NSObjcRuntime.h文件中，其具体定义如下。
 
 #define NS_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, ...) CF_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep, __VA_ARGS__)
 
 一般紧接在function的后面，用来标记该function被弃用，将来可能会被移除。但被弃用，并不是不能继续使用该function，在该方法被真正移除之前，仍然是可用的。不过使用后，编译器会产生一个关于方法被弃用的告警。
 
 其中
 1. CF_DEPRECATED，引用自 #include <CoreFoundation/CFAvailability.h>。
 2. _macIntro，指定方法首次引入的MAC OSX 系统版本，
 _macDep，指定方法首次弃用的MAC OSX 系统版本，
 _iosIntro，指定方法首次引入的iOS系统版本，
 _iosDep，指定方法首次弃用的iOS系统版本。
 ...，其他的参数。一般都是对该方法弃用的文本注解，比如弃用的原因，比如替代的方法。
 

 */

// 过期提醒
#define MJRefreshDeprecated(instead) NS_DEPRECATED(2_0, 2_0, 2_0, 2_0, instead)

    /* TODO: #待完成#
     学习了runtime才看得明白一些
     */
// 运行时objc_msgSend
#define MJRefreshMsgSend(...) ((void (*)(void *, SEL, UIView *))objc_msgSend)(__VA_ARGS__)
#define MJRefreshMsgTarget(target) (__bridge void *)(target)

// RGB颜色
#define MJRefreshColor(r, g, b) [UIColor colorWithRed:(r)/255.0 green:(g)/255.0 blue:(b)/255.0 alpha:1.0]

// 文字颜色
#define MJRefreshLabelTextColor MJRefreshColor(90, 90, 90)

// 字体大小
#define MJRefreshLabelFont [UIFont boldSystemFontOfSize:14]

// 常量
UIKIT_EXTERN const CGFloat MJRefreshLabelLeftInset;
UIKIT_EXTERN const CGFloat MJRefreshHeaderHeight;
UIKIT_EXTERN const CGFloat MJRefreshFooterHeight;
UIKIT_EXTERN const CGFloat MJRefreshFastAnimationDuration;
UIKIT_EXTERN const CGFloat MJRefreshSlowAnimationDuration;

UIKIT_EXTERN NSString *const MJRefreshKeyPathContentOffset;
UIKIT_EXTERN NSString *const MJRefreshKeyPathContentSize;
UIKIT_EXTERN NSString *const MJRefreshKeyPathContentInset;
UIKIT_EXTERN NSString *const MJRefreshKeyPathPanState;

UIKIT_EXTERN NSString *const MJRefreshHeaderLastUpdatedTimeKey;

UIKIT_EXTERN NSString *const MJRefreshHeaderIdleText;
UIKIT_EXTERN NSString *const MJRefreshHeaderPullingText;
UIKIT_EXTERN NSString *const MJRefreshHeaderRefreshingText;

UIKIT_EXTERN NSString *const MJRefreshAutoFooterIdleText;
UIKIT_EXTERN NSString *const MJRefreshAutoFooterRefreshingText;
UIKIT_EXTERN NSString *const MJRefreshAutoFooterNoMoreDataText;

UIKIT_EXTERN NSString *const MJRefreshBackFooterIdleText;
UIKIT_EXTERN NSString *const MJRefreshBackFooterPullingText;
UIKIT_EXTERN NSString *const MJRefreshBackFooterRefreshingText;
UIKIT_EXTERN NSString *const MJRefreshBackFooterNoMoreDataText;

UIKIT_EXTERN NSString *const MJRefreshHeaderLastTimeText;
UIKIT_EXTERN NSString *const MJRefreshHeaderDateTodayText;
UIKIT_EXTERN NSString *const MJRefreshHeaderNoneLastDateText;

// 状态检查
#define MJRefreshCheckState \
MJRefreshState oldState = self.state; \
if (state == oldState) return; \
[super setState:state];
