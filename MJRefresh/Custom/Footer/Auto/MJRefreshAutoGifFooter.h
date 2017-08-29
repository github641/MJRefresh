//
//  MJRefreshAutoGifFooter.h
//  MJRefreshExample
//
//  Created by MJ Lee on 15/4/24.
//  Copyright (c) 2015年 小码哥. All rights reserved.
//
// lzy170829注：整体不难理解，与header组非常相似，却没有header组复杂，只过了一下，特殊的点标注了一下
#import "MJRefreshAutoStateFooter.h"

@interface MJRefreshAutoGifFooter : MJRefreshAutoStateFooter
@property (weak, nonatomic, readonly) UIImageView *gifView;

/** 设置state状态下的动画图片images 动画持续时间duration*/
- (void)setImages:(NSArray *)images duration:(NSTimeInterval)duration forState:(MJRefreshState)state;
- (void)setImages:(NSArray *)images forState:(MJRefreshState)state;
@end
