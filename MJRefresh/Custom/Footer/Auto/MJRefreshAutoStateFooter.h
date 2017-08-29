//
//  MJRefreshAutoStateFooter.h
//  MJRefreshExample
//
//  Created by MJ Lee on 15/6/13.
//  Copyright © 2015年 小码哥. All rights reserved.
//
/* lzy170829注:整体不难理解，与header组非常相似，却没有header组复杂，只过了一下，特殊的点标注了一下
 这个类只有一个显示状态的label。
 */
#import "MJRefreshAutoFooter.h"

@interface MJRefreshAutoStateFooter : MJRefreshAutoFooter
/** 文字距离左侧的距离 */
@property (assign, nonatomic) CGFloat labelLeftInset;
/** 显示刷新状态的label */
@property (weak, nonatomic, readonly) UILabel *stateLabel;

/** 设置state状态下的文字 */
- (void)setTitle:(NSString *)title forState:(MJRefreshState)state;

/** 隐藏刷新状态的文字 */
@property (assign, nonatomic, getter=isRefreshingTitleHidden) BOOL refreshingTitleHidden;
@end
