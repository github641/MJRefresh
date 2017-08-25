//
//  MJRefreshNormalHeader.m
//  MJRefreshExample
//
//  Created by MJ Lee on 15/4/24.
//  Copyright (c) 2015年 小码哥. All rights reserved.
//

#import "MJRefreshNormalHeader.h"
#import "NSBundle+MJRefresh.h"

@interface MJRefreshNormalHeader()
{
    // lzy170825注：居然使用了__unsafe_unretained
    __unsafe_unretained UIImageView *_arrowView;
}
// lzy170825注：这里用的weak的指示器圈
@property (weak, nonatomic) UIActivityIndicatorView *loadingView;
@end

@implementation MJRefreshNormalHeader
#pragma mark - 懒加载子控件

// lzy170825注：getter。arrowView在.h中是readonly的
- (UIImageView *)arrowView
{
    if (!_arrowView) {
        // lzy170825注：通过NSBundle+MJ...创建的static image，arrowView通过这个图片创建。
        UIImageView *arrowView = [[UIImageView alloc] initWithImage:[NSBundle mj_arrowImage]];
        [self addSubview:_arrowView = arrowView];
    }
    return _arrowView;
}

- (UIActivityIndicatorView *)loadingView
{
    if (!_loadingView) {
        UIActivityIndicatorView *loadingView = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:self.activityIndicatorViewStyle];
        loadingView.hidesWhenStopped = YES;
        // lzy170825注：赋值和添加到父视图，写在一行了。
        [self addSubview:_loadingView = loadingView];
    }
    return _loadingView;
}

#pragma mark - 公共方法
// lzy170825注：setter
- (void)setActivityIndicatorViewStyle:(UIActivityIndicatorViewStyle)activityIndicatorViewStyle
{
    _activityIndicatorViewStyle = activityIndicatorViewStyle;
    
    self.loadingView = nil;
    [self setNeedsLayout];
}

#pragma mark - 重写父类的方法
- (void)prepare
{
    [super prepare];
    
    self.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
}

- (void)placeSubviews
{
    [super placeSubviews];
    
    // 箭头的中心点
    CGFloat arrowCenterX = self.mj_w * 0.5;
    if (!self.stateLabel.hidden) {
        CGFloat stateWidth = self.stateLabel.mj_textWith;
        CGFloat timeWidth = 0.0;
        if (!self.lastUpdatedTimeLabel.hidden) {
            timeWidth = self.lastUpdatedTimeLabel.mj_textWith;
        }
        CGFloat textWidth = MAX(stateWidth, timeWidth);
        
        /* lzy注170825
        箭头x轴上中心点 = header宽度的一半 - 『时间』文字长度与『状态』文字长度两者中的较大值 + 与文字的间距
         */
        arrowCenterX -= textWidth / 2 + self.labelLeftInset;
    }
    
    /* lzy注170825
     箭头y轴上中心点 = header高度的一半 */
    CGFloat arrowCenterY = self.mj_h * 0.5;
    
    CGPoint arrowCenter = CGPointMake(arrowCenterX, arrowCenterY);
    
    // 箭头
    if (self.arrowView.constraints.count == 0) {
        self.arrowView.mj_size = self.arrowView.image.size;
        self.arrowView.center = arrowCenter;
    }
        
    // 圈圈
    if (self.loadingView.constraints.count == 0) {
        self.loadingView.center = arrowCenter;
    }
    
    self.arrowView.tintColor = self.stateLabel.textColor;
}
/* lzy注170825
 一赋值给xx.mjheader，就是插入到了父视图的子视图的index == 0的位置。
 文字状态，
 文字时间，
 指示箭头都是正常状态，只是视图被上面的视图盖住了。
 
    普通闲置状态
    MJRefreshStateIdle = 1,
 
    松开就可以进行刷新的状态
    MJRefreshStatePulling,
 
    正在刷新中的状态
    MJRefreshStateRefreshing,
 
    即将刷新的状态
    MJRefreshStateWillRefresh,
 
    所有数据加载完毕，没有更多的数据了
    MJRefreshStateNoMoreData
 */
- (void)setState:(MJRefreshState)state
{
    // lzy170825注：这个宏，确保新值不同于当前值，才进行处理
    /* lzy注170825
     #define MJRefreshCheckState \
     MJRefreshState oldState = self.state; \
     if (state == oldState) return; \
     [super setState:state];
     */
    MJRefreshCheckState
    
    // 根据状态做事情
    if (state == MJRefreshStateIdle) {
        // lzy170825注：空闲
        
        if (oldState == MJRefreshStateRefreshing) {
            // lzy170825注：空闲，前一个状态是『转圈』
            self.arrowView.transform = CGAffineTransformIdentity;
            // lzy170825注：动画0.4秒
            [UIView animateWithDuration:MJRefreshSlowAnimationDuration animations:^{
                // lzy170825注：指示器圈alpha从1->0
                self.loadingView.alpha = 0.0;
            } completion:^(BOOL finished) {
                // 如果执行完动画发现不是idle状态，就直接返回，进入其他状态
                if (self.state != MJRefreshStateIdle) return;
                
                self.loadingView.alpha = 1.0;
                [self.loadingView stopAnimating];
                self.arrowView.hidden = NO;
            }];
        } else {
            // lzy170825注：目前是空闲状态，前一个状态不是转圈
            [self.loadingView stopAnimating];// lzy170825注：指示器圈设置了        loadingView.hidesWhenStopped = YES;

            self.arrowView.hidden = NO;
            // lzy170825注：这个动画0.25s
            [UIView animateWithDuration:MJRefreshFastAnimationDuration animations:^{
                self.arrowView.transform = CGAffineTransformIdentity;
            }];
        }
        
    } else if (state == MJRefreshStatePulling) {
        // lzy170825注：拉伸中
        [self.loadingView stopAnimating];
        self.arrowView.hidden = NO;
        [UIView animateWithDuration:MJRefreshFastAnimationDuration animations:^{
            self.arrowView.transform = CGAffineTransformMakeRotation(0.000001 - M_PI);
        }];
    } else if (state == MJRefreshStateRefreshing) {
        // lzy170825注：『刷新状态』，应该转圈
        self.loadingView.alpha = 1.0; // 防止refreshing -> idle的动画完毕动作没有被执行
        [self.loadingView startAnimating];
        self.arrowView.hidden = YES;
    }
}
@end
