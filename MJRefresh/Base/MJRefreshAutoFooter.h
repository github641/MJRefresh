//
//  MJRefreshAutoFooter.h
//  MJRefreshExample
//
//  Created by MJ Lee on 15/4/24.
//  Copyright (c) 2015年 小码哥. All rights reserved.
//
/* lzy170904注:
 常规的下拉刷新、上拉刷新的交互：
 拖拽到刷新view完全出现在屏幕上行，松手之后便会刷新。
 
 下拉刷新 没有自动刷新，只有正常的交互惯例：
 1、刷新view有固定的高度，与屏幕等宽。x在左上角为0，
 y：
 表象：隐藏在sv正常状态看不到的上部，当sv垂直可bounce的时候，下拉可以渐渐看到刷新view
 内部：综合计算刷新view的高度、判断当前sv.contentOffset、sv.contentInset，确定的y
 2、只有下拉到刷新view正好完全可见时或完全可见，用户是否还在拖拽的状态，决定是否触发刷新
 
 
 所谓footer自动刷新，与常规的下拉刷新、上拉刷新的交互不同：
 1、自动刷新footer实例，计算y类比下拉刷新
 2、设置完y之后，还在，- (void)willMoveToSuperview:(UIView *)newSuperview设置了sv的contentInset.bottom，使得正常往上拖动的内容，不需要sv bounce的情况下，就能让刷新view可见
 3、默认当刷新view正好（可以设置出现百分之x时就触发）完全出现在屏幕上时，自动触发刷新（不结合用户是否还在拖拽的状态）
 
 于是，可能有这样的情况，部分展示或者接近完全展示 %x的footer，而没有触发刷新。
 */
#import "MJRefreshFooter.h"

@interface MJRefreshAutoFooter : MJRefreshFooter
/** 是否自动刷新(默认为YES) */
/* lzy170904注:
 - (void)scrollViewContentOffsetDidChange:(NSDictionary *)change回调都会通过先通过这个属性过滤
 */
@property (assign, nonatomic, getter=isAutomaticallyRefresh) BOOL automaticallyRefresh;

/** 当底部控件出现多少时就自动刷新(默认为1.0，也就是底部控件完全出现时，才会自动刷新) */
@property (assign, nonatomic) CGFloat appearencePercentTriggerAutoRefresh MJRefreshDeprecated("请使用triggerAutomaticallyRefreshPercent属性");

/** 当底部控件出现多少时就自动刷新(默认为1.0，也就是底部控件完全出现时，才会自动刷新) */
@property (assign, nonatomic) CGFloat triggerAutomaticallyRefreshPercent;
@end
