//  代码地址: https://github.com/CoderMJLee/MJRefresh
//  代码地址: http://code4app.com/ios/%E5%BF%AB%E9%80%9F%E9%9B%86%E6%88%90%E4%B8%8B%E6%8B%89%E4%B8%8A%E6%8B%89%E5%88%B7%E6%96%B0/52326ce26803fabc46000000
//  MJRefreshHeader.h
//  MJRefreshExample
//
//  Created by MJ Lee on 15/3/4.
//  Copyright (c) 2015年 小码哥. All rights reserved.
//  下拉刷新控件:负责监控用户下拉的状态

/* lzy170901注:
 这个view，还没有任何的子视图。只是在这个视图中，处理整个容器的交互。
 
 - (void)scrollViewContentOffsetDidChange:(NSDictionary *)change

 这个监听sv的偏移值的回调方法中
 1、 计算了需要多少高度，设置到sv的上内边距，可以让刷新视图出现和消失
 2、定义了普通状态、刷新临界点，
 3、结合拖拽程度（sv.contentOffset.y）与当前state，处理状态转换与状态通知
 普通状态 <--> 刷新的临界点
 目前拖拽程度占整个拖拽的百分比。

 
  - (void)setState:(MJRefreshState)state
 根据不同的状态做不同的事情

 */

#import "MJRefreshComponent.h"

@interface MJRefreshHeader : MJRefreshComponent
/** 创建header */
+ (instancetype)headerWithRefreshingBlock:(MJRefreshComponentRefreshingBlock)refreshingBlock;
/** 创建header */
+ (instancetype)headerWithRefreshingTarget:(id)target refreshingAction:(SEL)action;

/** 这个key用来存储上一次下拉刷新成功的时间 */
@property (copy, nonatomic) NSString *lastUpdatedTimeKey;
/** 上一次下拉刷新成功的时间 */ // lzy170825注：这个时间存在ud里面
@property (strong, nonatomic, readonly) NSDate *lastUpdatedTime;

/** 忽略多少scrollView的contentInset的top */
@property (assign, nonatomic) CGFloat ignoredScrollViewContentInsetTop;
@end
