//
//  MJChiBaoZiHeader.h
//  MJRefreshExample
//
//  Created by MJ Lee on 15/6/12.
//  Copyright © 2015年 小码哥. All rights reserved.
//  吃包子效果的头部控件
/* lzy170828注:
 视图层级：
 MJRefreshGifHeaderView，
 子视图有：
 上半部分的操作提示文字，
 下半部分更新的时间，
 centerY在这两个label连接点的gifView
 
 
 设置state状态下的动画图片images 动画持续时间duration
- (void)setImages:(NSArray *)images duration:(NSTimeInterval)duration forState:(MJRefreshState)state;
 注意，暴露方法中，传入图片数组中，图片的高度，将决定MJRefreshGifHeaderView整个的高度
 */
#import "MJRefreshGifHeader.h"

@interface MJChiBaoZiHeader : MJRefreshGifHeader

@end
