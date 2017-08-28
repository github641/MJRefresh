//
//  MJRefreshNormalHeader.h
//  MJRefreshExample
//
//  Created by MJ Lee on 15/4/24.
//  Copyright (c) 2015年 小码哥. All rights reserved.
//
/* lzy170828注:
 视图层级：
 MJRefreshNormalHeaderView，
 子视图有：
 上半部分的操作提示文字，
 下半部分更新的时间，
 centerY在这两个label连接点的UIActivityIndicatorView或者arrowImageView
 
 */

#import "MJRefreshStateHeader.h"

@interface MJRefreshNormalHeader : MJRefreshStateHeader

// lzy170825注：正好一个箭头，一个指示器圈，是状态显示的显示

@property (weak, nonatomic, readonly) UIImageView *arrowView;
/** 菊花的样式 */
@property (assign, nonatomic) UIActivityIndicatorViewStyle activityIndicatorViewStyle;
@end
