//
//  MJRefreshBackStateFooter.h
//  MJRefreshExample
//
//  Created by MJ Lee on 15/6/13.
//  Copyright © 2015年 小码哥. All rights reserved.
//
/* lzy170829注:
 MJRefreshBackFooter
 是这组『Back』的共同父类。
 
 这是使用最广泛的，也是最经典的 上拉刷新 动作：
 1拖动上拉tableView:出现指向正上方的箭头，文字『上拉可以加载更多...』，此时松手，tableView会回弹到正常状态
 2上拉到某个临界点：箭头指向做动画指向正下方，文字『松开立即加载更多...』，此时松手，触发刷新：箭头位置被{转圈指示器}替换、文字『正在加载更多的数据...』
 3箭头指向正下方，把拖动的力度降低，幅度变小，又回到状态1
 
 MJRefreshBackGifFooter
 MJRefreshBackNormalFooter
 MJRefreshBackStateFooter
 这三个类的定制，和header组非常相似，类比就好了。
 
 */
#import "MJRefreshBackFooter.h"

@interface MJRefreshBackStateFooter : MJRefreshBackFooter
/** 文字距离圈圈、箭头的距离 */
@property (assign, nonatomic) CGFloat labelLeftInset;
/** 显示刷新状态的label */
@property (weak, nonatomic, readonly) UILabel *stateLabel;
/** 设置state状态下的文字 */
- (void)setTitle:(NSString *)title forState:(MJRefreshState)state;

/** 获取state状态下的title */
- (NSString *)titleForState:(MJRefreshState)state;
@end
