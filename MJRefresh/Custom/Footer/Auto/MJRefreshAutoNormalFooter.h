//
//  MJRefreshAutoNormalFooter.h
//  MJRefreshExample
//
//  Created by MJ Lee on 15/4/24.
//  Copyright (c) 2015年 小码哥. All rights reserved.
//

/* lzy170829注:整体不难理解，与header组非常相似，却没有header组复杂，只过了一下，特殊的点标注了一下
 
 视图层级：
 1、刷新时：
 MJRefreshAutoNormalFooter：
 UILabel：『正在加载更多数据...』
 UIActivityIndicatorView：『转圈』
 2、点击footer或者，上拉到某个临界点，自动触发刷新
 3、继承自MJRefreshAutoStateFooter
 
 */

#import "MJRefreshAutoStateFooter.h"

@interface MJRefreshAutoNormalFooter : MJRefreshAutoStateFooter
/** 菊花的样式 */
@property (assign, nonatomic) UIActivityIndicatorViewStyle activityIndicatorViewStyle;
@end
